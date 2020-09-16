#include "DeviceContext.h"

BEGIN_LFRL_OGL_NAMESPACE

PIXELFORMATDESCRIPTOR __create_default_pxf_descriptor()
{
	PIXELFORMATDESCRIPTOR descriptor;
	std::memset(&descriptor, 0, sizeof(descriptor));
	descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	descriptor.nVersion = 1;
	descriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	descriptor.iPixelType = PFD_TYPE_RGBA;
	descriptor.cColorBits = 32;
	descriptor.cDepthBits = 32;
	descriptor.iLayerType = PFD_MAIN_PLANE;
	return descriptor;
}

PixelFormatAttributes::PixelFormatAttributes() noexcept
	: drawToWindow(true), supportOpenGL(true), doubleBuffer(true), sampleCount(4), pixelType(WGL_TYPE_RGBA_ARB), colorBits(32), depthBits(24), stencilBits(8)
{}

std::array<int, 19> PixelFormatAttributes::encode() const noexcept
{
	return {
	WGL_DRAW_TO_WINDOW_ARB, (int)drawToWindow,
	WGL_SUPPORT_OPENGL_ARB, (int)supportOpenGL,
	WGL_DOUBLE_BUFFER_ARB, (int)doubleBuffer,
	WGL_PIXEL_TYPE_ARB, (int)pixelType,
	WGL_COLOR_BITS_ARB, (int)colorBits,
	WGL_DEPTH_BITS_ARB, (int)depthBits,
	WGL_STENCIL_BITS_ARB, (int)stencilBits,
	WGL_SAMPLE_BUFFERS_ARB, sampleCount > 0 ? 1 : 0,
	WGL_SAMPLES_ARB, (int)sampleCount,
	0 };
}

const PIXELFORMATDESCRIPTOR DeviceContext::DEFAULT_PIXEL_FORMAT_DESCRIPTOR = __create_default_pxf_descriptor();

DeviceContext::DeviceContext() noexcept
	: _hdc(NULL), _handle(NULL), _pxfDescriptor(), _pxfAttributes(), _pxf(0), _state(State::CREATED)
{
	std::memset(&_pxfDescriptor, 0, sizeof(_pxfDescriptor));
}

DeviceContext::ActionResult DeviceContext::Initialize(Wnd::Handle const& handle, PixelFormatAttributes attributes)
{
	PIXELFORMATDESCRIPTOR descriptor;
	std::memcpy(&descriptor, &DEFAULT_PIXEL_FORMAT_DESCRIPTOR, sizeof(descriptor));
	return Initialize(handle, attributes, descriptor);
}

DeviceContext::ActionResult DeviceContext::Initialize(Wnd::Handle const& handle, PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor)
{
	if (_state == State::READY || _state == State::DISPOSED)
		return ActionResult::ALREADY_INITIALIZED;

	if (handle.GetState() != Wnd::Handle::State::READY)
	{
		_state = State::INIT_FAILURE;
		return ActionResult::INVALID_HANDLE;
	}

	auto hdc = ::GetDC(handle.GetHwnd());
	if (hdc == NULL)
	{
		_state = State::INIT_FAILURE;
		return ActionResult::HDC_INIT_FAILURE;
	}

	descriptor.nSize = DEFAULT_PIXEL_FORMAT_DESCRIPTOR.nSize;
	descriptor.nVersion = DEFAULT_PIXEL_FORMAT_DESCRIPTOR.nVersion;

	auto pxf = 0;
	auto iNumFormats = 0U;
	auto attribs = attributes.encode();

	if (!wglChoosePixelFormatARB(hdc, attribs.data(), NULL, 1, &pxf, &iNumFormats))
	{
		pxf = ::ChoosePixelFormat(hdc, &descriptor);
		if (pxf == 0)
		{
			::ReleaseDC(handle.GetHwnd(), hdc);
			_state = State::INIT_FAILURE;
			return ActionResult::PIXEL_FORMAT_CHOICE_FAILURE;
		}
	}
	if (!::SetPixelFormat(hdc, pxf, &descriptor))
	{
		::ReleaseDC(handle.GetHwnd(), hdc);
		_state = State::INIT_FAILURE;
		return ActionResult::PIXEL_FORMAT_INIT_FAILURE;
	}

	_hdc = hdc;
	_handle = &handle;
	_pxfDescriptor = descriptor;
	_pxfAttributes = attributes;
	_pxf = pxf;
	_state = State::READY;
	return ActionResult::OK;
}

bool DeviceContext::IsActive() const
{
	return wglGetCurrentDC() == _hdc;
}

bool DeviceContext::SwapBuffers()
{
	return ::SwapBuffers(_hdc);
}

DeviceContext::ActionResult DeviceContext::Dispose()
{
	if (_state == State::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != State::READY)
		return ActionResult::NOT_READY;

	if (!::ReleaseDC(_handle->GetHwnd(), _hdc))
		return ActionResult::HDC_DISPOSAL_FAILURE;

	_hdc = NULL;
	_state = State::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
