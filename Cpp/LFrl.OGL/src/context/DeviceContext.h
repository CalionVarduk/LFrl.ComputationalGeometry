#ifndef __LFRL_OGL_DEVICE_CONTEXT_GUARD__
#define __LFRL_OGL_DEVICE_CONTEXT_GUARD__

#include <array>
#include "../wnd/Handle.h"
#include "../ObjectState.h"

BEGIN_LFRL_OGL_NAMESPACE

struct PixelFormatAttributes final
{
	bool drawToWindow;
	bool doubleBuffer;
	LFRL::u32 sampleCount;
	LFRL::u32 pixelType;
	LFRL::u32 colorBits;
	LFRL::u32 depthBits;
	LFRL::u32 stencilBits;

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

	static const PIXELFORMATDESCRIPTOR DEFAULT_PIXEL_FORMAT_DESCRIPTOR;

	DeviceContext(DeviceContext const&) = delete;
	DeviceContext& operator=(DeviceContext const&) = delete;

	DeviceContext() noexcept;
	DeviceContext(DeviceContext&&) noexcept;
	DeviceContext& operator=(DeviceContext&&) noexcept;
	~DeviceContext() { Dispose(); }

	HDC GetHdc() const noexcept { return _hdc; }
	Wnd::Handle* GetHandle() noexcept { return _handle; }
	Wnd::Handle const* GetHandle() const noexcept { return _handle; }
	PIXELFORMATDESCRIPTOR const& GetPixelFormatDescriptor() const noexcept { return _pxfDescriptor; }
	PixelFormatAttributes const& GetPixelFormatAttributes() const noexcept { return _pxfAttributes; }
	LFRL::i32 GetPixelFormat() const noexcept { return _pxf; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize(Wnd::Handle& handle, PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor);
	ActionResult Initialize(Wnd::Handle& handle, PixelFormatAttributes attributes) { return Initialize(handle, attributes, DEFAULT_PIXEL_FORMAT_DESCRIPTOR); }

	bool IsActive() const;
	bool SwapBuffers();

	ActionResult Dispose();
	ActionResult Invalidate();

private:
	HDC _hdc;
	Wnd::Handle* _handle;
	PIXELFORMATDESCRIPTOR _pxfDescriptor;
	PixelFormatAttributes _pxfAttributes;
	LFRL::i32 _pxf;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
