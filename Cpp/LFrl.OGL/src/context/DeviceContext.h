#ifndef __LFRL_OGL_DEVICE_CONTEXT_GUARD__
#define __LFRL_OGL_DEVICE_CONTEXT_GUARD__

#include <array>
#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

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
		HDC_INIT_FAILURE = 2,
		PIXEL_FORMAT_CHOICE_FAILURE = 3,
		PIXEL_FORMAT_INIT_FAILURE = 4,
		NOT_READY = 5,
		HDC_DISPOSAL_FAILURE = 6,
		ALREADY_DISPOSED = 7
	};

	enum struct State
	{
		CREATED = 0,
		INIT_FAILURE = 1,
		READY = 2,
		DISPOSED = 3
	};

	static const PIXELFORMATDESCRIPTOR DEFAULT_PIXEL_FORMAT_DESCRIPTOR;

	DeviceContext() = delete;
	DeviceContext(DeviceContext const&) = delete;
	DeviceContext(DeviceContext&&) = delete;
	DeviceContext& operator=(DeviceContext const&) = delete;
	DeviceContext& operator=(DeviceContext&&) = delete;

	DeviceContext(HWND handle) noexcept;
	~DeviceContext() { Dispose(); }

	HWND GetParentHandle() const;
	HWND GetHandle() const noexcept { return _handle; }
	HDC GetHdc() const noexcept { return _hdc; }
	PIXELFORMATDESCRIPTOR const& GetPixelFormatDescriptor() const noexcept { return _pxfDescriptor; }
	PixelFormatAttributes const& GetPixelFormatAttributes() const noexcept { return _pxfAttributes; }
	LFRL_COMMON::i32 GetPixelFormat() const noexcept { return _pxf; }
	State GetState() const noexcept { return _state; }

	ActionResult Initialize(PixelFormatAttributes attributes);
	ActionResult Initialize(PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor);

	bool IsActive() const;
	bool SwapBuffers();
	bool Validate(RECT const* rect = NULL);

	ActionResult Dispose();

private:
	const HWND _handle;
	HDC _hdc;
	PIXELFORMATDESCRIPTOR _pxfDescriptor;
	PixelFormatAttributes _pxfAttributes;
	LFRL_COMMON::i32 _pxf;
	State _state;
};

END_LFRL_OGL_NAMESPACE

#endif
