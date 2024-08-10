from typing import List, Tuple, Optional

import idaapi
import idc
import ida_bytes
import ida_name
import ida_funcs
import ida_segment
import idautils
import pyperclip

# Define masks for flags in __vmi_class_type_info
NON_DIAMOND_REPEAT_MASK = 1
DIAMOND_SHAPED_MASK = 2

# Define masks for offset flags in __base_class_type_info
VIRTUAL_MASK = 1
PUBLIC_MASK = 2
OFFSET_SHIFT = 8

CLASS_TYPE_INFO = 0
SI_CLASS_TYPE_INFO = 1
VMI_CLASS_TYPE_INFO = 2

ACTION_DUMP = "classdumper:dump"
ACTION_COPY_VTABLE = "classdumper:copyvtable"
ACTION_PASTE_VTABLE = "classdumper:pastevtable"


def output_lines(lines: List[str], filename: str) -> None:
    """
    Output the lines to a specified file.

    Args:
        lines (List[str]): The lines to write to the file.
        filename (str): The name of the file to write to.
    """
    if filename.find("::") != -1:
        filename = filename.replace("::", "_")

    with open(filename, "w", encoding="utf-8") as f:
        for line in lines:
            f.write(line + "\n")


def get_pointer_size() -> int:
    """
    Get the size of a pointer on the current platform (4 bytes for 32-bit, 8 bytes for 64-bit).

    Returns:
        int: The size of a pointer in bytes.
    """
    return 8 if idaapi.get_inf_structure().is_64bit() else 4


def get_strlit(ea: int) -> Optional[bytes]:
    """
    Retrieve the string literal contents at the specified address.

    Args:
        ea (int): The address from which to retrieve the string literal.

    Returns:
        Optional[bytes]: The string literal contents at the given address, or None if not found.
    """
    return ida_bytes.get_strlit_contents(ea, -1, idc.STRTYPE_C)


def get_string(ea: int) -> str:
    """
    Retrieve a null-terminated string from the specified address.

    Args:
        ea (int): The address to read the string from.

    Returns:
        str: The retrieved string.
    """
    strlit = get_strlit(ea)
    return strlit.decode("utf-8") if strlit is not None else ""


def get_function_name(ea: int) -> str:
    """
    Retrieve the function name at the given address.

    Args:
        ea (int): The address to get the function name from.

    Returns:
        str: The function name.
    """
    return idc.get_func_name(ea)


def set_function_name(ea: int, name: str) -> bool:
    """
    Set the name of a function at the specified address.

    Parameters:
        ea (int): The effective address of the function to rename.
        name (str): The new name to assign to the function.

    Returns:
        bool: True if the function name was successfully set, False otherwise.
    """
    return idc.set_name(ea, name, idc.SN_CHECK)


def get_real_function_ea(ea: int) -> int:
    """
    Retrieve the function name at the given address.

    Args:
        ea (int): The address to get the function name from.

    Returns:
        str: The function name.
    """

    if idc.is_code(idc.get_full_flags(ea)) and idc.print_insn_mnem(ea) == "jmp":
        real_ea = idc.get_operand_value(ea, 0)
    elif idc.is_data(idc.get_full_flags(ea)):
        real_ea = read_pointer(ea)
    else:
        real_ea = ea

    return real_ea


def demangle_name(mangled_name: str) -> str:
    """
    Demangle a name to get the human-readable form.

    Args:
        mangled_name (str): The mangled name to demangle.

    Returns:
        str: The demangled name, or the original name if demangling fails.
    """
    if str is None or str == "":
        return ""

    if idaapi.get_inf_structure().cc.id == idc.COMP_GNU:
        if mangled_name.startswith("___"):
            return mangled_name
        if not mangled_name.startswith("__Z"):
            mangled_name = "__Z" + mangled_name

    demangled_name = ida_name.demangle_name(mangled_name, ida_name.DQT_COMPILER)
    return demangled_name if demangled_name is not None else mangled_name


def read_pointer(ea: int) -> int:
    """
    Read a pointer-sized value from the given address.

    Args:
        ea (int): The address to read from.

    Returns:
        int: The pointer-sized value.
    """
    size = get_pointer_size()
    if size == 8:
        return ida_bytes.get_qword(ea)
    else:
        return ida_bytes.get_dword(ea)


def is_valid_pointer(ea: int) -> bool:
    """
    Check if the specified address contains a valid pointer.

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address contains a valid pointer, False otherwise.
    """
    if ea == idc.BADADDR:
        return False
    value = read_pointer(ea)
    seg = ida_segment.getseg(value)
    return seg is not None


def is_valid_function_ea(ea: int) -> bool:
    """
    Check if the specified address is a valid function pointer.

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address is a valid function pointer, False otherwise.
    """
    func = ida_funcs.get_func(ea)
    if func is None:
        seg = ida_segment.getseg(ea)
        if seg is not None and idaapi.get_segm_class(seg) == "XTRN":
            return True
    else:
        return True
    return False


def is_typeinfo(ea: int) -> bool:
    """
    Check if the specified address is a typeinfo structure.

    A typeinfo structure typically contains:
    - A pointer to a vtable for typeinfo
    - A pointer to a type name

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address is a typeinfo structure, False otherwise.
    """
    # Check if vtable pointer points to a vtable for typeinfo
    # We assume the vtable for typeinfo has a known pattern or known address
    vtable_name = ida_name.get_ea_name(ea, ida_name.GN_DEMANGLED)
    if "typeinfo" in vtable_name:
        return True

    # Read vtable pointer
    if not is_valid_pointer(ea):
        return False

    # Read name pointer
    name_ptr = ea + get_pointer_size()
    if not is_valid_pointer(name_ptr):
        return False

    # Validate the name pointer
    type_name = get_string(read_pointer(name_ptr))
    if len(type_name) == 0:
        return False

    return True


def is_vtable_entry(ea: int) -> bool:
    """
    Check if the specified address is a valid vtable entry.

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address is a valid vtable entry, False otherwise.
    """
    if is_valid_pointer(ea):
        ptr = read_pointer(ea)
        return is_valid_function_ea(ptr)
    return False


def parse_vtable_entries(vtblptr: int, count: int = -1) -> List[Tuple[int, int]]:
    """
    Parse the vtable to retrieve function pointers.

    Args:
        vtblptr (int): The address of the vtable.
        count (int): The number of entries to parse (default is -1 for all entries).

    Returns:
        List[Tuple[int, int]]: A list of tuples containing the vtable entry address and function pointer.
    """
    pointer_size = get_pointer_size()
    vtable_entries = []

    if count == -1:
        i = 0
        while True:
            entry = read_pointer(vtblptr + i * pointer_size)
            if is_vtable_entry(vtblptr + i * pointer_size):
                vtable_entries.append((vtblptr + i * pointer_size, entry))
            else:
                break
            i += 1
    else:
        for i in range(count):
            entry = read_pointer(vtblptr + i * pointer_size)
            if is_vtable_entry(vtblptr + i * pointer_size):
                vtable_entries.append((vtblptr + i * pointer_size, entry))
            else:
                break

    return vtable_entries


def get_class_name(type_info_ea: int, demangle: bool = True) -> str:
    """
    Retrieve the class name from the __class_type_info structure.

    Args:
        type_info_ea (int): The address of the __class_type_info structure.
        demangle (bool): Whether to demangle the class name (default is True).

    Returns:
        str: The class name.
    """
    name_pointer = read_pointer(type_info_ea + get_pointer_size())
    name = get_string(name_pointer)
    if not demangle:
        return name
    else:
        return demangle_name(name)


def is_si_class_type_info(type_info_ea: int) -> bool:
    """
    Check if the given address points to a __si_class_type_info structure.

    Args:
        type_info_ea (int): The address to check.

    Returns:
        bool: True if the address points to a __si_class_type_info structure, False otherwise.
    """
    if not is_typeinfo(type_info_ea):
        return False

    si_class_type_info_offset = 16 if idaapi.get_inf_structure().is_64bit() else 8

    base_type_pointer = read_pointer(type_info_ea + si_class_type_info_offset)
    return is_typeinfo(base_type_pointer)


def is_vmi_class_type_info(type_info_ea: int) -> bool:
    """
    Check if the given address points to a __vmi_class_type_info structure.

    Args:
        type_info_ea (int): The address to check.

    Returns:
        bool: True if the address points to a __vmi_class_type_info structure, False otherwise.
    """
    if not is_typeinfo(type_info_ea):
        return False

    if idaapi.get_inf_structure().is_64bit():
        vmi_class_type_info_offset = 16
        flags = ida_bytes.get_dword(type_info_ea + vmi_class_type_info_offset)
        base_count = ida_bytes.get_dword(type_info_ea + vmi_class_type_info_offset + 4)
        return flags >> 2 == 0 and base_count != 0
    else:
        vmi_class_type_info_offset = 8
        flags = ida_bytes.get_word(type_info_ea + vmi_class_type_info_offset)
        base_count = ida_bytes.get_word(type_info_ea + vmi_class_type_info_offset + 4)
        return flags >> 2 == 0 and base_count != 0


def identify_rtti_type(type_info_ea: int) -> int:
    """
    Identify the RTTI type of the structure at the given address.

    Args:
        type_info_ea (int): The address to check.

    Returns:
        int: The RTTI type (CLASS_TYPE_INFO, SI_CLASS_TYPE_INFO, or VMI_CLASS_TYPE_INFO).
    """
    if is_si_class_type_info(type_info_ea):
        return SI_CLASS_TYPE_INFO
    elif is_vmi_class_type_info(type_info_ea):
        return VMI_CLASS_TYPE_INFO
    else:
        return CLASS_TYPE_INFO


def parse_si_class_type_info(type_info_ea: int) -> int:
    """
    Parse the __si_class_type_info structure to retrieve the base class information.

    Args:
        type_info_ea (int): The address of the __si_class_type_info structure.

    Returns:
        int: The address of the base class typeinfo structure.
    """
    si_class_type_info_offset = 16 if idaapi.get_inf_structure().is_64bit() else 8
    return read_pointer(type_info_ea + si_class_type_info_offset)


def get_base_class_info(base_info_ea: int) -> Tuple[int, int]:
    """
    Retrieve the base class type information from the __base_class_type_info structure.

    Args:
        base_info_ea (int): The address of the __base_class_type_info structure.

    Returns:
        tuple: A tuple containing the base type pointer and the offset_flags.
    """
    base_type_pointer = read_pointer(base_info_ea)
    pointer_size = get_pointer_size()
    if pointer_size == 8:
        offset_flags = ida_bytes.get_qword(base_info_ea + pointer_size)
    else:
        offset_flags = ida_bytes.get_dword(base_info_ea + pointer_size)
    return base_type_pointer, offset_flags


def parse_offset_flags(offset_flags: int) -> Tuple[int, int]:
    """
    Parse the __offset_flags to extract the signed offset and flags.

    Args:
        offset_flags (int): The offset_flags value to parse.

    Returns:
        tuple: A tuple containing the offset and the flags.
    """
    flags = offset_flags & 0xFF
    offset = offset_flags >> OFFSET_SHIFT

    # Convert offset to signed if necessary
    # Check if the sign bit is set (for 64-bit signed)
    if offset & (1 << (64 - OFFSET_SHIFT - 1)):
        offset -= (1 << (64 - OFFSET_SHIFT))

    return offset, flags


def parse_vmi_class_type_info(type_info_ea: int) -> Tuple[int, list]:
    """
    Parse the __vmi_class_type_info structure to retrieve base class information.

    Args:
        type_info_ea (int): The address of the __vmi_class_type_info structure.

    Returns:
        tuple: A tuple containing the flags and a list of base class information (base class name, offset, flags).
    """
    pointer_size = get_pointer_size()
    vmi_class_type_info_offset = 16 if idaapi.get_inf_structure().is_64bit() else 8

    if pointer_size == 8:
        flags = ida_bytes.get_dword(type_info_ea + vmi_class_type_info_offset)
    else:
        flags = ida_bytes.get_word(type_info_ea + vmi_class_type_info_offset)

    if pointer_size == 8:
        base_count = ida_bytes.get_dword(type_info_ea + vmi_class_type_info_offset + 4)
    else:
        base_count = ida_bytes.get_word(type_info_ea + vmi_class_type_info_offset + 2)

    vmi_class_base_info_offset = vmi_class_type_info_offset + pointer_size
    base_info_array = type_info_ea + vmi_class_base_info_offset

    base_classes = []
    for i in range(base_count):
        base_info_ea = base_info_array + i * (2 * pointer_size)
        base_type_pointer, offset_flags = get_base_class_info(base_info_ea)
        base_name = get_class_name(base_type_pointer)
        offset, base_flags = parse_offset_flags(offset_flags)
        base_classes.append((base_name, offset, base_flags))

    return flags, base_classes


def is_marked_as_itanium_vtable(ea: int) -> bool:
    """
    Check if the specified address is a vtable by examining its name.

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address is a vtable, False otherwise.
    """
    name = ida_name.get_ea_name(ea)
    if name == "" or not name.startswith("__ZTV"):
        return False
    return True


def is_marked_as_itanium_typeinfo(ea: int) -> bool:
    """
    Check if the specified address is a typeinfo structure by examining its name.

    Args:
        ea (int): The address to check.

    Returns:
        bool: True if the address is a typeinfo structure, False otherwise.
    """
    name = ida_name.get_ea_name(ea)
    if name == "" or not name.startswith("__ZTI"):
        return False
    return True


def generate_class_declaration(name: str, methods: List[str], base_classes: List[Tuple[str, int, int]], size: int = 0) -> List[str]:
    """
    Generate a C++ class declaration from the class name, methods, and optionally base classes and size.

    Args:
        name (str): The name of the class.
        methods (List[str]): A list of method names.
        base_classes (List[Tuple[str, int, int]]): A list of base classes with their information.
        size (int): The size of the class (default is 0).

    Returns:
        List[str]: The lines of the class declaration.
    """
    lines = []
    if len(base_classes) == 0:
        lines.append(f"class {name} {{")
    elif len(base_classes) == 1:
        lines.append(f"class {name} : public {base_classes[0][0]} {{")
    else:
        parents = []
        for base in base_classes:
            parent = "virtual " if base[2] == VIRTUAL_MASK else ""
            if base[2] == PUBLIC_MASK:
                parent += "public "
            parent += base[0]
            parents.append(parent)

        parent_list = ", ".join(parents)
        lines.append(f"class {name} : {parent_list} {{")

    lines.append("public:")
    offset = 0
    for method in methods:
        if method == "___cxa_pure_virtual":
            decl = f"    virtual void* pure_virtual_{offset:x}();"
        elif method.endswith("D1Ev"):
            decl = f"    virtual ~{name}();"
        elif method.endswith("D0Ev"):
            continue
        else:
            method_name = demangle_name(method)
            decl = f"    virtual void* {method_name};"
            if decl.endswith("const;"):
                decl = decl.replace("const;", " /* const */;")
            decl = decl.replace("(void)", "()")

        lines.append(decl)
        offset += get_pointer_size()

    if size != 0:
        lines.append("public:")
        for offset in range(get_pointer_size(), size, get_pointer_size()):
            decl = f"    void* field_{offset:x};"
            lines.append(decl)

    lines.append("};")
    return lines


def dump_class_info_from_vtblptr(ea: int) -> Tuple[str, List[Tuple[str, int, int]], List[str]]:
    """
    Dump the class information from the vtable pointer at the specified address.

    Args:
        ea (int): The address of the vtable.

    Returns:
        Tuple[str, List[Tuple[str, int, int]], List[str]]: The class name, base classes, and methods.
    """
    # vtable_name = ida_name.get_ea_name(ea, ida_name.GN_DEMANGLED)
    # if "vtable" not in vtable_name:
    #     return []
    # class_name = vtable_name.split("'")[1]

    pointer_size = get_pointer_size()

    type_info_ea = read_pointer(ea - pointer_size)
    if not is_typeinfo(type_info_ea):
        return "", [], []

    class_name = get_class_name(type_info_ea)

    rtti_type = identify_rtti_type(type_info_ea)
    if rtti_type == SI_CLASS_TYPE_INFO:
        base_type_info = parse_si_class_type_info(type_info_ea)
        base_class_name = get_class_name(base_type_info)
        flags = 0
        base_classes = [(base_class_name, 0, 0)]
    elif rtti_type == VMI_CLASS_TYPE_INFO:
        flags, base_classes = parse_vmi_class_type_info(type_info_ea)
    else:
        flags = 0
        base_classes = []

    entries = parse_vtable_entries(ea)

    methods = []
    for entry in entries:
        func_name = ida_name.get_ea_name(entry[1])
        if func_name.startswith("__ZN") or func_name == "___cxa_pure_virtual":
            methods.append(func_name)
        else:
            break

    return class_name, base_classes, methods


def dump_class_from_constructor(ctor_ea: int) -> bool:
    """
    Dump the class information starting from a constructor function.

    Args:
        ea (int): The address of the constructor function.

    Returns:
        bool: True if the class was successfully dumped, False otherwise.
    """
    func = ida_funcs.get_func(ctor_ea)
    if func is None:
        return False

    vtblptrs = []
    for addr in idautils.FuncItems(func.start_ea):
        if idc.is_code(idc.get_full_flags(addr)) and idc.print_insn_mnem(addr) == "lea":
            value = idc.get_operand_value(addr, 1)
            seg = ida_segment.getseg(value)
            if seg is not None:
                vtblptrs.append(value)

    for vtblptr in vtblptrs:
        class_name, base_classes, methods = dump_class_info_from_vtblptr(
            vtblptr)
        if class_name != "":
            lines = generate_class_declaration(class_name, methods, base_classes)
            lines.insert(0, "#pragma once\n")
            output_lines(lines, f"{class_name}.h")

    return True


def dump_class(ea: int = idc.BADADDR) -> bool:
    """
    Dump the class information from the specified address.

    Args:
        ea (int): The address to start dumping from (default is the current screen address).

    Returns:
        bool: True if the class was successfully dumped, False otherwise.
    """
    if ea == idc.BADADDR:
        ea = idc.get_screen_ea()
    seg = ida_segment.getseg(ea)
    if seg is None:
        return False

    if seg.perm & idaapi.SEGPERM_EXEC != 0:
        dump_class_from_constructor(ea)
    else:
        class_name, base_classes, methods = dump_class_info_from_vtblptr(ea)
        if class_name != "":
            lines = generate_class_declaration(class_name, methods, base_classes)
            lines.insert(0, "#pragma once\n")
            output_lines(lines, f"{class_name}.h")

    return True


def dump_vtable_entries(ea_start: int, ea_end: int, demangle: bool = False, pair: bool = False) -> List[str]:
    """
    Generate a list of function names (or address-name pairs) for the specified address range.

    Args:
        ea_start (int): The starting address of the range.
        ea_end (int): The ending address of the range.
        demangle (bool): Whether to demangle the names (default is False).
        pair (bool): Whether to return a list of (address, name) tuples (default is False).

    Returns:
        Union[List[str], List[Tuple[int, str]]]: A list of function names if `pair` is False,
        or a list of (address, name) tuples if `pair` is True.
    """
    entries = []
    for ea in range(ea_start, ea_end, get_pointer_size()):
        func_ea = read_pointer(ea)
        if not is_valid_function_ea(func_ea):
            break
        func_name = ida_name.get_ea_name(func_ea)
        if demangle:
            func_name = demangle_name(func_name)
        if pair:
            entries.append(f"{func_ea}:{func_name}")
        else:
            entries.append(func_name)
    return entries


def rename_vtable_entries(ea: int, names: List[str]) -> List[str]:
    """
    Rename vtable entries based on the provided list of names.

    Args:
        ea (int): The address of the vtable.
        names (List[str]): The list of new function names.

    Returns:
        List[str]: A list of old function names that were replaced.
    """
    if not is_vtable_entry(ea) or names is None:
        return []

    pointer_size = get_pointer_size()
    i = 0
    old_names = []
    for name in names:
        if name.endswith("D0Ev"):
            continue
        func_ea = read_pointer(ea + i * pointer_size)
        i += 1
        if not is_valid_function_ea(func_ea):
            continue
        func_ea = get_real_function_ea(func_ea)
        if func_ea == idc.BADADDR:
            continue
        func_name = ida_name.get_ea_name(func_ea)
        if func_name not in ["_purecall", "___cxa_pure_virtual"]:
            set_function_name(func_ea, name)
        old_names.append(func_name)

    return old_names


def copy_vtable_entries(ea_start: int = idc.BADADDR, ea_end: int = idc.BADADDR) -> bool:
    """
    Copy vtable entries from the specified address range to the clipboard.

    Args:
        ea_start (int): The starting address of the range (default is the current selection start).
        ea_end (int): The ending address of the range (default is the current selection end).

    Returns:
        bool: True if the entries were successfully copied, False otherwise.
    """
    if ea_start == idc.BADADDR or ea_end == idc.BADADDR:
        ea_start = idc.read_selection_start()
        ea_end = idc.read_selection_end()

    entries = dump_vtable_entries(ea_start, ea_end)
    if len(entries) != 0:
        pyperclip.copy("\n".join(entries))
        return True
    return False


def paste_vtable_entries(ea: int = idc.BADADDR) -> bool:
    """
    Paste vtable entries from the clipboard and rename the functions at the specified address.

    Args:
        ea (int): The address of the vtable (default is the current screen address).

    Returns:
        bool: True if the entries were successfully pasted, False otherwise.
    """
    if ea == idc.BADADDR:
        ea = idc.get_screen_ea()

    if not is_vtable_entry(ea):
        return False

    text = pyperclip.paste()
    if text is None or len(text) == 0:
        return False

    names = text.split("\n")
    old_names = rename_vtable_entries(ea, names)
    if len(old_names) == 0:
        return False

    pyperclip.copy("\n".join(old_names))
    return True


class menu_action_handler_t(idaapi.action_handler_t):
    """
    Action handler for menu actions
    """

    def __init__(self, action: str):
        idaapi.action_handler_t.__init__(self)
        self.action = action

    def activate(self, ctx) -> int:
        # Handle the action activation.
        if self.action == ACTION_DUMP:
            if dump_class(ctx.cur_ea):
                return 1
            else:
                print("No class dumped.")
                return 0
        elif self.action == ACTION_COPY_VTABLE:
            if copy_vtable_entries(ctx.cur_ea):
                return 1
            else:
                print("Failed to copy vtable")
                return 0
        elif self.action == ACTION_PASTE_VTABLE:
            if paste_vtable_entries(ctx.cur_ea):
                return 1
            else:
                print("Failed to paste vtable")
                return 0
        return 1

    def update(self, ctx) -> int:
        # This method is called to update the action's state.
        # Return idaapi.AST_ENABLE_ALWAYS to keep the action enabled.
        return idaapi.AST_ENABLE_ALWAYS


class UI_Hook(idaapi.UI_Hooks):
    """
    UI hook for attaching actions to the context menu.
    """

    def __init__(self):
        idaapi.UI_Hooks.__init__(self)

    def finish_populating_widget_popup(self, widget, popup_handle, ctx) -> None:
        # Populate the widget's context menu.
        widget_type = idaapi.get_widget_type(widget)

        if widget_type == idaapi.BWN_DISASM:
            t0, t1, view = idaapi.twinpos_t(), idaapi.twinpos_t(), idaapi.get_current_viewer()
            if idaapi.read_selection(view, t0, t1) or idc.get_item_size(idc.get_screen_ea()) > 1:
                idaapi.attach_action_to_popup(widget, popup_handle, ACTION_DUMP, None)
                idaapi.attach_action_to_popup(widget, popup_handle, ACTION_COPY_VTABLE, None)
                idaapi.attach_action_to_popup(widget, popup_handle, ACTION_PASTE_VTABLE, None)


class class_dumper_t(idaapi.plugin_t):
    """
    Main plugin class for class dumping.
    """
    flags = 0
    comment = "Dump class infomations"
    help = ""
    wanted_name = "ClassDumper"
    wanted_hotkey = ""

    def __init__(self):
        self.registered_actions = []
        self.ui_hook = None

    def init(self) -> int:
        # Initialize the plugin.
        print("ClassDumper plugin has been loaded.")
        # Register menu actions
        menu_actions = (
            idaapi.action_desc_t(ACTION_DUMP, "Dump class", menu_action_handler_t(ACTION_DUMP), "Ctrl+Shift+D"),
            idaapi.action_desc_t(ACTION_COPY_VTABLE, "Copy vtable", menu_action_handler_t(ACTION_COPY_VTABLE), "Ctrl+Shift+C"),
            idaapi.action_desc_t(ACTION_PASTE_VTABLE, "Paste vtable", menu_action_handler_t(ACTION_PASTE_VTABLE), "Ctrl+Shift+V"),
        )
        for action in menu_actions:
            idaapi.register_action(action)
            self.registered_actions.append(action.name)

        # Add ui hook
        self.ui_hook = UI_Hook()
        self.ui_hook.hook()

        return idaapi.PLUGIN_KEEP

    def run(self, arg: int) -> None:
        # Run the plugin.
        pass

    def term(self) -> None:
        # Terminate the plugin.
        for action in self.registered_actions:
            idaapi.unregister_action(action)


def PLUGIN_ENTRY() -> class_dumper_t:
    # Plugin entry point.
    return class_dumper_t()
