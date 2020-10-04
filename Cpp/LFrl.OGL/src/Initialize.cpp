#include "Initialize.h"

#include "context/DeviceContext.h"

BEGIN_LFRL_OGL_NAMESPACE

struct __disposable_hdc
{
	HWND hwnd;
	HDC value;
	PIXELFORMATDESCRIPTOR pxfDescriptor;
	int pxf;

	__disposable_hdc() noexcept : hwnd(NULL), value(NULL), pxfDescriptor(DeviceContext::DEFAULT_PIXEL_FORMAT_DESCRIPTOR), pxf(0) {}
	~__disposable_hdc() { destroy(); }

	bool init(HWND h)
	{
		hwnd = h;
		value = GetDC(hwnd);
		if (value == NULL)
			return false;

		pxf = ChoosePixelFormat(value, &pxfDescriptor);
		if (pxf == 0)
		{
			ReleaseDC(h, value);
			return false;
		}
		if (!SetPixelFormat(value, pxf, &pxfDescriptor))
		{
			ReleaseDC(h, value);
			return false;
		}
		return true;
	}

	bool destroy()
	{
		return value != NULL && ReleaseDC(hwnd, value);
	}
};

struct __disposable_hglrc
{
	HGLRC value;

	__disposable_hglrc() noexcept : value(NULL) {}
	~__disposable_hglrc() { destroy(); }

	bool init(HDC hdc)
	{
		value = wglCreateContext(hdc);
		if (!wglMakeCurrent(hdc, value))
		{
			wglDeleteContext(value);
			value = NULL;
			return false;
		}
		return true;
	}

	bool destroy()
	{
		if (value == NULL)
			return false;

		wglMakeCurrent(NULL, NULL);
		return wglDeleteContext(value);
	}
};

LRESULT CALLBACK __dummy_wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, message, wParam, lParam);
}

InitializationResult Initialize()
{
	if (wglCreateContextAttribsARB != NULL)
		return InitializationResult::ALREADY_INITIALIZED;

	WNDCLASS wndCls;
	std::memset(&wndCls, 0, sizeof(wndCls));
	wndCls.style = CS_OWNDC | CS_GLOBALCLASS;
	wndCls.lpszClassName = "__LFrl::OGL::Initialize::DUMMY_WND_CLASS";
	wndCls.lpfnWndProc = __dummy_wnd_proc;

	Wnd::Class cls;
	auto cInitResult = cls.Initialize(wndCls);
	if (cInitResult != Wnd::Class::ActionResult::OK)
		return InitializationResult::WND_CLASS_INIT_FAILURE;

	Wnd::Handle handle;
	auto hInitResult = handle.Initialize(cls, Wnd::HandleParams());
	if (hInitResult != Wnd::Handle::ActionResult::OK)
		return InitializationResult::HWND_INIT_FAILURE;

	__disposable_hdc hdc;
	if (!hdc.init(handle.GetHwnd()))
		return InitializationResult::HDC_INIT_FAILURE;

	__disposable_hglrc hglrc;
	if (!hglrc.init(hdc.value))
		return InitializationResult::HGLRC_INIT_FAILURE;

	if (glewInit() != GLEW_OK)
		return InitializationResult::GLEW_INIT_FAILURE;

	if (!hglrc.destroy())
		return InitializationResult::HGLRC_DISPOSAL_FAILURE;

	if (!hdc.destroy())
		return InitializationResult::HDC_RELEASE_FAILURE;

	auto hDisposeResult = handle.Dispose();
	if (hDisposeResult != Wnd::Handle::ActionResult::OK)
		return InitializationResult::HWND_DISPOSAL_FAILURE;

	auto cDisposeResult = cls.Dispose();
	if (cDisposeResult != Wnd::Class::ActionResult::OK)
		return InitializationResult::WND_CLASS_DISPOSAL_FAILURE;

	return InitializationResult::OK;
}

END_LFRL_OGL_NAMESPACE
