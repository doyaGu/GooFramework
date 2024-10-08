#pragma once

class UString
{
public:
	UString();
	UString(const wchar_t *str);
	UString(const char *utf8);
	UString(const UString &ustr);
	~UString();

	static UString format(const char *utf8format, ...);

	int length() const;

	const char *toUtf8() const;
	int fromUtf8(const char *utf8);

	const wchar_t *wc_str() const; // WARNING: may return NULL for empty strings
	UString substr(int offset, int charCount = -1) const;
	int findChar(wchar_t ch, int start = 0, bool respectEscapeChars = false) const;
	int findChar(const UString &str, int start = 0, bool respectEscapeChars = false) const;
	int find(const UString &str, int start = 0) const;
	void append(const UString &str);
	void insert(int offset, const UString &str);
	void insert(int offset, wchar_t ch);
	void erase(int offset, int count);
	void clear();
	bool isAsciiOnly();
	void collapseEscapes();
	UString trim();

	float toFloat() const;
	void fromFloat(float f);

	// operators:
	wchar_t operator[](int index) const;
	UString &operator=(const UString &ustr);
	bool operator==(const UString &ustr) const;
	bool operator!=(const UString &ustr) const;
	bool operator<(const UString &ustr) const;

private:
	int decode(const char *utf8, wchar_t *unicode);
	int encode(const wchar_t *unicode, int length, char *utf8, bool *isAsciiOnly) const;
	wchar_t getCodePoint(const char *utf8, int offset, int numBytes, unsigned char firstByteMask);
	void getUtf8(wchar_t ch, char *utf8, int numBytes, int firstByteValue) const;
	void updateUtf8();

private:
	wchar_t *mUnicode;
	char *mUtf8;
	int mLength;
	bool mIsAsciiOnly;
};