#ifndef __LFRL_OGL_DEVICE_CONTEXT_GUARD__
#define __LFRL_OGL_DEVICE_CONTEXT_GUARD__

#include <array>
#include "../wnd/Handle.h"

BEGIN_LFRL_OGL_NAMESPACE

struct PixelFormatAttributes final
{
	bool drawToWindow;
	bool supportOpenGL;
	bool doubleBuffer;
	LFRL_COMMON::u32 sampleCount;
	LFRL_COMMON::u32 pixelType;
	LFRL_COMMON::u32 colorBits;
	LFRL_COMMON::u32 depthBits;
	LFRL_COMMON::u32 stencilBits;

	PixelFormatAttributes() noexcept;

	std::array<int, 19> encode() const noexcept;
};

struct DeviceContext final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		INVALID_HANDLE = 2,
		HDC_INIT_FAILURE = 3,
		PIXEL_FORMAT_CHOICE_FAILURE = 4,
		PIXEL_FORMAT_INIT_FAILURE = 5,
		NOT_READY = 6,
		HDC_DISPOSAL_FAILURE = 7,
		ALREADY_DISPOSED = 8
	};

	enum struct State
	{
		CREATED = 0,
		INIT_FAILURE = 1,
		READY = 2,
		DISPOSED = 3
	};

	static const PIXELFORMATDESCRIPTOR DEFAULT_PIXEL_FORMAT_DESCRIPTOR;

	DeviceContext(DeviceContext const&) = delete;
	DeviceContext(DeviceContext&&) = delete;
	DeviceContext& operator=(DeviceContext const&) = delete;
	DeviceContext& operator=(DeviceContext&&) = delete;

	DeviceContext() noexcept;
	~DeviceContext() { Dispose(); }

	HDC GetHdc() const noexcept { return _hdc; }
	Wnd::Handle const* GetHandle() const noexcept { return _handle; }
	PIXELFORMATDESCRIPTOR const& GetPixelFormatDescriptor() const noexcept { return _pxfDescriptor; }
	PixelFormatAttributes const& GetPixelFormatAttributes() const noexcept { return _pxfAttributes; }
	LFRL_COMMON::i32 GetPixelFormat() const noexcept { return _pxf; }
	State GetState() const noexcept { return _state; }

	ActionResult Initialize(Wnd::Handle const& handle, PixelFormatAttributes attributes);
	ActionResult Initialize(Wnd::Handle const& handle, PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor);

	bool IsActive() const;
	bool SwapBuffers();

	ActionResult Dispose();

private:
	HDC _hdc;
	Wnd::Handle const* _handle;
	PIXELFORMATDESCRIPTOR _pxfDescriptor;
	PixelFormatAttributes _pxfAttributes;
	LFRL_COMMON::i32 _pxf;
	State _state;
};

END_LFRL_OGL_NAMESPACE

#endif
