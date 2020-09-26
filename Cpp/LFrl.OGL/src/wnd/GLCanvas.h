#ifndef __LFRL_OGL_WND_GL_CANVAS_GUARD__
#define __LFRL_OGL_WND_GL_CANVAS_GUARD__

#include "GLCanvasEventHandlerFactory.h"
#include "../context/IGLCanvasContextFactory.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

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
		CONTEXT_INIT_FAILURE = 5,
		EVENT_HANDLER_INIT_FAILURE = 6,
		NO_CHANGE = 7,
		ALREADY_DISPOSED = 8,
		HANDLE_DISPOSAL_FAILURE = 9,
		DC_DISPOSAL_FAILURE = 10,
		RC_DISPOSAL_FAILURE = 11,
		NOT_READY = 12
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

	Handle* GetHandle() noexcept { return &_handle; }
	Handle const* GetHandle() const noexcept { return &_handle; }
	DeviceContext* GetDc() noexcept { return &_dc; }
	DeviceContext const* GetDc() const noexcept { return &_dc; }
	RenderingContext* GetRc() noexcept { return &_rc; }
	RenderingContext const* GetRc() const noexcept { return &_rc; }
	GLCanvasContext* GetContext() noexcept { return _context; }
	GLCanvasContext const* GetContext() const noexcept { return _context; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize(HWND parent, RECT bounds, IGLCanvasContextFactory* contextFactory, GLCanvasEventHandlerFactory* eventHandlerFactory = nullptr);
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
	GLCanvasContext* _context;
	GLCanvasEventHandler* _eventHandler;
	ObjectState _state;

	static LRESULT CALLBACK _WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

END_LFRL_OGL_WND_NAMESPACE

#endif
