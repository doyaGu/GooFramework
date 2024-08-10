#pragma once

#include <string>
#include <iostream>

#include "SDL2Environment.h"
#include "bgfx/bgfx.h"
#include "Rect.h"
#include "Vec2.h"
#include "Color.h"
#include "Image.h"
#include "SpriteVertex.h"
#include "TriStrip.h"
#include "UniformColorShader.h"
#include "GraphicsCurvedPoint.h"
#include "GraphicsMultiCurvedPoint.h"
#include "GraphicsPreRenderJob.h"
#include "GraphicsRenderResolution.h"
#include "GraphicsProjectionType.h"
#include "SceneObject.h"
#include "Camera.h"
#include "FontStyle.h"
#include "UString.h"
#include "GraphicsState.h"

class Graphics {
public:
    // Constructs a Graphics object with specified parameters.
    Graphics(std::string const& name, int width, int height, SDL2Environment::UIScaleMode scaleMode, float scaleFactor, bool enableVSync, int colorDepth, std::string const& resourcePath, std::string const& shaderPath, bool useMipMaps, bool enableBloom, bool enableScissor);

    virtual ~Graphics();

    // Initializes the graphics system.
    bool initialize();

    // Initializes shaders for rendering.
    bool initializeShaders();

    // Initializes resources needed for rendering.
    bool renderInitResources();

    // De-initializes rendering resources.
    void renderDeinitResources();

    // Resets the graphics state to default.
    void resetState();

    // Resets the render resolution to its default settings.
    void resetRenderResolution();

    // Resets the rendering system.
    void renderReset();

    // Updates the window size based on current settings.
    void updateWindowSize();

    // Updates frame buffers used in rendering.
    void updateFrameBuffers();

    // Creates a window with specified dimensions and properties.
    bool createWindow(int width, int height, bool fullscreen);

    // Destroys the current window.
    void destroyWindow();

    // Begins rendering a new scene.
    void beginScene();

    // Ends the current scene rendering.
    void endScene();

    // Toggles between different screen modes.
    void doScreenModeToggle();

    // Resets the current scene with specified parameters.
    void resetScene(int resetMode);

    // Frees resources allocated for the render resolution.
    void freeRenderResolution();

    // Retrieves the default image used by the graphics system.
    Image* getDefaultImage();

    // Retrieves a white image used by the graphics system.
    Image* getWhiteImage();

    // Renders a full-screen quad using the specified texture.
    void renderFullScreenQuad(bgfx::TextureHandle textureHandle);

    // Sets the current frame buffer for rendering.
    void setCurrentFrameBuffer(int frameBufferId, bool clearBuffer, int clearColor, bool clearDepth, bool enableStencil);

    // Begins rendering in full-screen mode.
    void beginFullScreenView();

    // Ends full-screen mode rendering.
    void endFullScreenView();

    // Generates a view projection matrix with specified parameters.
    void generateViewProjectionMatrix(int width, int height, float (&matrix)[4][4], bool orthographic, float *offsetMatrix[4]);

    // Renders a full-screen quad using a specified shader.
    void fullScreenQuadForShader(bgfx::ProgramHandle programHandle, ulong long renderState, uint textureUnit);

    // Handles an SDL event.
    void onEvent(SDL_Event const* event);

    // Draws an image with various options.
    void drawImage(Image *image);

    // Draws a line between two points.
    void drawLine(float x1, float y1, float x2, float y2);

    // Draws a circle with specified parameters.
    void drawCircle(Vec2 center, float radius, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bgfx::UniformHandle uniformHandle);

    // Draws a filled rectangle.
    void drawFilledRect(Rect const& rect, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bgfx::UniformHandle uniformHandle);

    // Draws a circle outline.
    void drawLineCircle(Vec2 center, float radius, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bgfx::UniformHandle uniformHandle);

    // Draws a half-circle.
    void drawHalfCircle(Vec2 center, float radius, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bgfx::UniformHandle uniformHandle);

    // Draws a thick line with specified parameters.
    void drawThickLine(Vec2 *points, int pointCount, float thickness, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bgfx::UniformHandle uniformHandle);

    // Draws a dynamic mesh with various options.
    void drawDynamicMesh(void const* vertices, int vertexCount, void const* indices, int indexCount, bgfx::VertexLayout const& layout, bgfx::ProgramHandle const& program, ulong long renderState, int depth, bool cullFace, uint textureUnit, Graphics::State *state);

    // Submits the current draw call.
    void submitDraw(ushort viewId, bgfx::ProgramHandle programHandle);

    // Renders the current frame.
    void renderFrame();

    // Pushes the current transformation matrix onto the stack.
    void pushTransform();

    // Pops the top transformation matrix from the stack.
    void popTransform();

    // Scales the current transformation matrix.
    void scale(float scaleX, float scaleY);

    // Rotates the current transformation matrix.
    void rotate(float angle);

    // Translates the current transformation matrix.
    void translate(Vec2 const& translation);

    // Sets the current drawing color.
    void setColor(Color const& color);

    // Retrieves the current drawing color.
    Color getColor();

    // Sets the current alpha transparency level.
    void setAlpha(float alpha);

    // Retrieves the current transformation matrix.
    float[4][4] getTransform();

    // Retrieves the current render state.
    void getCurrentRenderState(Graphics::State *state);

    // Sets the Z-depth value for rendering.
    void setZ(float zValue);

    // Retrieves the current Z-depth value.
    float getZ();

    // Pushes the current graphics state onto the stack.
    void pushState(bool pushAll);

    // Pops the top graphics state from the stack.
    void popState();

    // Sets the texture to be used for rendering.
    void setTexture(Image *image, uint textureUnit);

    // Sets an additional texture for rendering.
    void setAdditionalTexture(Image *image);

    // Loads a shader from the specified path.
    bgfx::ShaderHandle loadShader(char const* shaderPath, bool isVertexShader, bool compileShader);

    // Reloads all currently loaded shaders.
    void reloadShaders();

    // Unloads all currently loaded shaders.
    void unloadShaders();

    // Sets up the default shader to the specified encoder.
    void setupDefaultShaderToEncoder(bgfx::Encoder *encoder, Graphics::State &state, float (*transformMatrix)[4]);

    // Converts a screen space vector to resolution base space.
    Vec2 screenToResolutionBaseSpace(Vec2 const& screenSpaceVec);

    // Converts a resolution base space vector to screen space.
    Vec2 resolutionBaseToScreenSpace(Vec2 const& resolutionBaseVec);

    // Sets the clear color for rendering.
    void setClearColor(uint clearColor);

    // Retrieves the current aspect ratio of the screen.
    float getAspectRatio();

    // Dumps information about the graphics system to an output stream.
    void dumpInfo(std::ostream &outputStream);

    // Toggles the tablet mode for rendering.
    void ToggleTabletMode();

    // Draws debug information around a scene object.
    void debugDrawSceneObjectBoundary(SceneObject &sceneObject);

    // Sets the path where video capture files will be saved.
    void setVideoCapturePath(char const* path);

    // Locks or unlocks rendering operations.
    void lockRender(bool lock);

    // Enables or disables video capture.
    void enableCapture(bool capture, bool saveToFile);

    // Checks if video capture is enabled.
    bool isCaptureEnabled();

    // Sets the frame rate for video capture.
    void setCaptureFrameRate(float frameRate);

    // Retrieves the current frame rate for video capture.
    float getCaptureFrameRate();

    // Checks if the current draw submission is valid.
    bool isSubmitValid();

    // Dispatches a compute shader with the specified parameters.
    void dispatch(ushort viewId, bgfx::ProgramHandle programHandle, uint numGroupsX, uint numGroupsY, uint numGroupsZ);

    // Dispatches a compute shader with indirect parameters.
    void dispatchIndirect(ushort viewId, bgfx::ProgramHandle programHandle, bgfx::IndirectBufferHandle indirectBufferHandle, ushort start, ushort num);

    // Draws a mesh using an encoder with specified parameters.
    void drawMeshToEncoder(bgfx::Encoder *encoder, int vertexCount, Graphics::State &state, bgfx::VertexBufferHandle vertexBufferHandle, int vertexOffset, bgfx::IndexBufferHandle indexBufferHandle, int indexOffset, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, ulong long renderState, bool cullFace, uint textureUnit, uint scissorIndex = 0);

    // Draws a dynamic mesh using an encoder with specified parameters.
    void drawDynamicMeshToEncoder(bgfx::Encoder *encoder, int vertexCount, Graphics::State &state, void const* vertices, int vertexStride, void const* indices, int indexStride, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, ulong long renderState, bool cullFace, uint textureUnit);


    // Sets the Z-function used for depth testing.
    void setZFunction(Graphics::CompareFunc compareFunc);

    // Retrieves the current blending type.
    BlendingType::Enum getBlendingType();

    // Sets the blending type for rendering.
    void setBlendingType(BlendingType::Enum blendingType);

    // Checks if alpha writing is enabled.
    bool isWriteAlphaEnabled();

    // Enables or disables alpha writing.
    void setWriteAlphaEnabled(bool enabled);

    // Checks if color writing is enabled.
    bool isWriteColorEnabled();

    // Enables or disables color writing.
    void setWriteColorEnabled(bool enabled);

    // Sets the type of sprite shader to use.
    void setSpriteShaderType(SpriteShader::Type::Enum shaderType);

    // Sets the index for the sprite shader define.
    void setSpriteShaderDefineIndex(uint index);

    // Retrieves the current sprite shader define index.
    uint getSpriteShaderDefineIndex();

    // Retrieves the current sprite shader settings.
    SpriteShaderSettings getSpriteShaderSettings();

    // Sets the clip rectangle for the sprite shader.
    void setSpriteShaderClipRectangle(Rect const& clipRect);

    // Sets a pre-callback function for the sprite shader.
    void setSpriteShaderPreCallback(void (*preCallback)(Graphics*, void*), void *userData);

    // Sets a callback function for the sprite shader.
    void setSpriteShaderCallback(void (*callback)(Graphics*, void*), void *userData);

    // Sets the bloom factor for the sprite shader.
    void setSpriteShaderBloomFactor(float bloomFactor);

    // Enables or disables the use of MipMaps for sprites.
    void setSpriteUseMipMaps(bool useMipMaps);

    // Sets the scissor rectangle for rendering.
    void setDrawScissor(int x, int y, int width, int height);

    // Sets the scissor rectangle for rendering in resolution base coordinates.
    void setDrawScissorInResolutionBase(int x, int y, int width, int height);

    // Retrieves the current draw scissor rectangle.
    Rect getDrawScissorRect();

    // Resets the view scissor to the default state.
    void resetViewScissor();

    // Sets the view scissor rectangle for the current view.
    void setViewScissor(int x, int y, int width, int height);

    // Enables or disables alpha testing.
    void setAlphaTestEnabled(bool enabled);

    // Checks if alpha testing is enabled.
    bool isAlphaTestEnabled();

    // Sets the reference value for alpha testing.
    void setAlphaReferenceValue(int referenceValue);

    // Sets the comparison function for alpha testing.
    void setAlphaFunction(Graphics::CompareFunc compareFunc);

    // Draws a triangle strip with specified parameters.
    void drawTriStrip(TriStrip *triStrip, bool filled, Image *image);

    // Draws a triangle fan with the specified sprite vertices.
    void drawTriFan(SpriteVertex const* vertices, int vertexCount);

    // Draws dynamic sprite vertices with specified parameters.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, ushort *indices, int indexCount, bgfx::TextureHandle textureHandle, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices with specified parameters, without indices.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, bgfx::TextureHandle textureHandle, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices using image-based textures.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, ushort *indices, int indexCount, Image *image, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices using image-based textures, without indices.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, Image *image, ulong long renderState, uint textureUnit);

    // Draws text on the screen with specified parameters.
    void drawText(Vec2 const& position, UString const& text, FontStyle const& fontStyle, Color const& color, float scale);

    // Retrieves the current UI scale factor.
    float getUIScaleFactor();

    // Sets the scale factor for game rendering.
    void setGameRenderScaleFactor(float scaleFactor);

    // Retrieves the current game rendering scale factor.
    float getGameRenderScaleFactor();

    // Enables or disables rendering scale with upscaler.
    void setGameRenderScaleWithUpscaler(bool enabled);

    // Checks if rendering scale with upscaler is enabled.
    bool getGameRenderScaleWithUpscaler();

    // Retrieves the resolution base scale factor.
    float getResolutionBaseScale();

    // Retrieves the inverse of the resolution base scale factor.
    float getResolutionBaseOneOverScale();

    // Retrieves the width of the resolution base.
    int getResolutionBaseWidth();

    // Retrieves the height of the resolution base.
    int getResolutionBaseHeight();

    // Retrieves the width of the window's resolution base.
    int getWindowResolutionBaseWidth();

    // Retrieves the height of the window's resolution base.
    int getWindowResolutionBaseHeight();

    // Retrieves the current aspect ratio of the screen.
    float getAspectRatio();

    // Sets the clear Z-depth value for rendering.
    void setClearZ(float clearZ);

    // Sets the clear color for rendering.
    void setClearColor(uint clearColor);

    // Generates a camera-to-screen transformation matrix.
    void generateCameraToScreenTransform(Camera *camera, float (*viewMatrix)[4], float (*projectionMatrix)[4], bool orthographic);

    // Blits a thumbnail to the screen.
    void blitThumbnail();

    // Blits a texture with a shader to the screen with specified parameters.
    void blitWithShader(int x, int y, int width, int height, bgfx::UniformHandle uniformHandle, bgfx::UniformHandle secondaryUniformHandle, bgfx::TextureHandle textureHandle, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, bool flipY, Rect const& sourceRect, Rect const* destinationRect, Color const& color, float (*viewMatrix)[4], float (*projectionMatrix)[4], uint renderState);

    // Splits the current frame buffer view with specified dimensions.
    void splitCurrentFrameBufferView(int x, int y, int width, int height);

    // Reads the back buffer of the thumbnail texture.
    void readThumbnailTextureBack();

    // Checks if the thumbnail is ready for use.
    bool isThumbnailReady();

    // Saves the current thumbnail to a file.
    void saveThumbnail(char const* filePath);

    // Clears the current thumbnail.
    void clearThumbnail();

    // Adds a pre-render job to the graphics pipeline.
    void addPreRenderJob(GraphicsPreRenderJob preRenderJob);

    // Enables or disables batching for rendering.
    void enableBatching(bool enabled);

    // Checks if batching is enabled for rendering.
    bool isBatchingEnabled();

    // Merges the current frame buffer view with the specified view.
    void mergeCurrentFrameBufferView();

    // Reserves a specified number of frame buffer views.
    void reserveFrameBufferViews(int viewCount);

    // Sets a custom frame buffer view for rendering.
    void setCustomFrameBufferView(int viewId);

    // Sets up the render resolution based on the specified resolution type.
    void setupRenderResolution(GraphicsRenderResolution::Enum resolutionType);

    // Renders the scene at the specified render resolution.
    void renderRenderResolution(bgfx::TextureHandle textureHandle);

    // Sets the availability of stencil operations.
    void setStencilAvailable(bool available);

    // Checks if stencil operations are available.
    bool isStencilAvailable();

    // Enables or disables stencil operations.
    void setStencilEnabled(bool enabled);

    // Sets the stencil flags for rendering.
    void setStencilFlags(uint flags);

    // Retrieves the index of the first available frame buffer.
    int getIndexOfFirstAvailableFrameBuffer();

    // Sets up the frame buffer view with specified parameters.
    void setupFrameBufferView(int x, int y, int width, int height, int clearColor, int clearDepth, int clearStencil, int renderState);

    // Sets the frame buffer view for the current rendering context.
    void setViewFrameBuffer(int viewId, bgfx::FrameBufferHandle frameBufferHandle);

    // Retrieves the current projection type.
    GraphicsProjectionType::Enum getProjectionType();

    // Sets the projection type for the graphics system.
    void setProjectionType(GraphicsProjectionType::Enum projectionType);

    // Sets the vertical synchronization (VSync) setting.
    void setVSync(int vsyncSetting);

    // Sets a custom projection matrix for rendering.
    void setCustomProjectionMatrix(float (&customMatrix)[4][4]);

    // Sets the resolution base projection matrix with the specified offset.
    void setResolutionBaseProjectionWithOffset(float (*projectionMatrix)[4]);

    // Creates a shader from the specified source code.
    bgfx::ShaderHandle createShader(char const* shaderSource, bool isVertexShader, bool compileShader);

    // Locks or unlocks rendering operations.
    void lockRender(bool lock);

    // Sets up the default shader to the specified encoder.
    void setupDefaultShaderToEncoder(bgfx::Encoder *encoder, Graphics::State &state, float (*transformMatrix)[4]);

 // Toggles the screen mode between windowed and full-screen.
    void ToggleScreenMode();

    // Checks if the graphics system is in windowed mode.
    bool IsWindowedMode();

    // Reloads shaders from the default shader directory.
    void loadShaders();

    // Sets the frame rate for video capture.
    void setCaptureFrameRate(float frameRate);

    // Retrieves the current frame rate for video capture.
    float getCaptureFrameRate();

    // Retrieves the platform-specific screen scaling factor.
    float getPlatformScreenScalingFactor(float width, float height);

    // Queries and updates window information based on the current platform.
    void queryWindowInfoPlatform();

    // Resets the rendering system based on platform-specific settings.
    void renderResetPlatform();

    // Renders initialization steps before the main rendering process.
    void renderPreInit();

    // Renders post-initialization steps after the main rendering process.
    void renderPostInit();

    // Frees resources allocated for the render resolution.
    void freeRenderResolution();

    // Sets the texture to the specified graphics state.
    void setTextureToState(Graphics::State &state, bgfx::TextureHandle textureHandle, uint textureUnit, bgfx::TextureHandle additionalHandle);

    // Sets an additional texture to the specified graphics state.
    void setAdditionalTextureToState(Graphics::State &state, bgfx::TextureHandle textureHandle);

    // Sets an additional texture for the graphics system.
    void setAdditionalTexture(bgfx::TextureHandle textureHandle);

    // Draws debug information around the specified scene object.
    void debugDrawSceneObjectBoundary(SceneObject &sceneObject);

    // Sets the path where video capture files will be saved.
    void setVideoCapturePath(char const* path);

    // Checks if video capture is enabled.
    bool isCaptureEnabled();

    // Enables or disables video capture.
    void enableCapture(bool capture, bool saveToFile);

    // Unloads all currently loaded shaders.
    void unloadShaders();

    // Retrieves the index of the first available frame buffer.
    int getIndexOfFirstAvailableFrameBuffer(void);

    // Sets a custom frame buffer view for rendering.
    void setCustomFrameBufferView(int viewId);

    // Merges the current frame buffer view with the specified view.
    void mergeCurrentFrameBufferView(void);

    // Reserves a specified number of frame buffer views.
    void reserveFrameBufferViews(int viewCount);

    // Creates a frame buffer with specified parameters.
    void createFrameBuffer(Image *image, bool useMipMaps, int width, int height, bgfx::TextureHandle textureHandle, bgfx::TextureHandle depthTextureHandle, bgfx::TextureFormat::Enum format, ulong long renderState, bool enableStencil, float clearZ);

    // Resets the render resolution to default settings.
    void resetRenderResolution(void);

    // Creates a default frame buffer with specified parameters.
    void createDefaultFrameBuffer(int bufferId);

    // Destroys all frame buffers currently allocated.
    void destroyFrameBuffers(void);

    // Destroys the specified frame buffer.
    void destroyFrameBuffer(int frameBufferId);

    // Destroys all shaders currently loaded in the graphics system.
    void destroyShaders(void);

    // Draws a triangle strip with specified parameters.
    void drawTriStrip(TriStrip *triStrip, bool filled, Image *image);

    // Draws a triangle fan with the specified sprite vertices.
    void drawTriFan(SpriteVertex const* vertices, int vertexCount);

    // Draws dynamic sprite vertices with specified parameters.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, ushort *indices, int indexCount, bgfx::TextureHandle textureHandle, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices with specified parameters, without indices.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, bgfx::TextureHandle textureHandle, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices using image-based textures.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, ushort *indices, int indexCount, Image *image, ulong long renderState, uint textureUnit);

    // Draws dynamic sprite vertices using image-based textures, without indices.
    void drawDynamicSpriteVertices(SpriteVertex const* vertices, int vertexCount, Image *image, ulong long renderState, uint textureUnit);

    // Checks if the current draw submission is valid.
    bool isSubmitValid(void);

    // Dispatches a compute shader with the specified parameters.
    void dispatch(ushort viewId, bgfx::ProgramHandle programHandle, uint numGroupsX, uint numGroupsY, uint numGroupsZ);

    // Dispatches a compute shader with indirect parameters.
    void dispatchIndirect(ushort viewId, bgfx::ProgramHandle programHandle, bgfx::IndirectBufferHandle indirectBufferHandle, ushort start, ushort num);

    // Draws a mesh using an encoder with specified parameters.
    void drawMeshToEncoder(bgfx::Encoder *encoder, int vertexCount, Graphics::State &state, bgfx::VertexBufferHandle vertexBufferHandle, int vertexOffset, bgfx::IndexBufferHandle indexBufferHandle, int indexOffset, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, ulong long renderState, bool cullFace, uint textureUnit, uint scissorIndex = 0);

    // Draws a dynamic mesh using an encoder with specified parameters.
    void drawDynamicMeshToEncoder(bgfx::Encoder *encoder, int vertexCount, Graphics::State &state, void const* vertices, int vertexStride, void const* indices, int indexStride, bgfx::VertexLayout const& vertexLayout, bgfx::ProgramHandle const& programHandle, ulong long renderState, bool cullFace, uint textureUnit);
};