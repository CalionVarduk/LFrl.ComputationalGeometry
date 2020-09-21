#ifndef __LFRL_OGL_WND_GL_CANVAS_GUARD__
#define __LFRL_OGL_WND_GL_CANVAS_GUARD__

#include "../context/RenderingContext.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

// TODO: ASAP, before ICanvasContext, so that I know what am I working with winapi-wise
// and what needs to be abstracted away via the context
class GLCanvas
{
public:
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		HANDLE_INIT_FAILURE = 2,
		DC_INIT_FAILURE = 3,
		RC_INIT_FAILURE = 4,
		NO_CHANGE = 5,
		ALREADY_DISPOSED = 6,
		HANDLE_DISPOSAL_FAILURE = 7,
		DC_DISPOSAL_FAILURE = 8,
		RC_DISPOSAL_FAILURE = 9,
		NOT_READY = 10
	};

	static Class const& GetClass() noexcept { return _Class; }
	static Class::ActionResult Register();
	static Class::ActionResult Unregister() { return _Class.Dispose(); }

	GLCanvas(GLCanvas const&) = delete;
	GLCanvas(GLCanvas&&) = delete;
	GLCanvas& operator=(GLCanvas const&) = delete;
	GLCanvas& operator=(GLCanvas&&) = delete;

	GLCanvas() noexcept;
	~GLCanvas() { Dispose(); }

	Handle const& GetHandle() const noexcept { return _handle; }
	DeviceContext const& GetDc() const noexcept { return _dc; }
	RenderingContext const& GetRc() const noexcept { return _rc; }
	ObjectState GetState() const noexcept { return _state; }

	// init ( with context factory? or just a pointer to context? factory would be nicer, i think )
	ActionResult Initialize(HWND parent, RECT bounds);
	ActionResult ChangePixelFormat(PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor);
	ActionResult ChangePixelFormat(PixelFormatAttributes attributes) { return ChangePixelFormat(attributes, DeviceContext::DEFAULT_PIXEL_FORMAT_DESCRIPTOR); }

	bool SetBounds(RECT value);
	bool Draw();

	ActionResult Dispose();

private:
	static Class _Class;

	Handle _handle;
	DeviceContext _dc;
	RenderingContext _rc;
	ObjectState _state;

	static LRESULT CALLBACK _WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

END_LFRL_OGL_WND_NAMESPACE

#endif
