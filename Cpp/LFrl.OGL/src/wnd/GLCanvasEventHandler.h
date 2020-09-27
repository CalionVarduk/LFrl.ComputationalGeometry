#ifndef __LFRL_OGL_WND_GL_CANVAS_EVENT_HANDLER_GUARD__
#define __LFRL_OGL_WND_GL_CANVAS_EVENT_HANDLER_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

class GLCanvas;

struct GLCanvasEventHandler
{
	GLCanvasEventHandler() = delete;
	GLCanvasEventHandler(GLCanvasEventHandler const&) = delete;
	GLCanvasEventHandler& operator=(GLCanvasEventHandler const&) = delete;

	explicit GLCanvasEventHandler(GLCanvas& canvas) noexcept;
	GLCanvasEventHandler(GLCanvasEventHandler&&) noexcept = default;
	GLCanvasEventHandler& operator=(GLCanvasEventHandler&&) noexcept = default;
	virtual ~GLCanvasEventHandler() { _canvas = nullptr; }

	virtual LRESULT Handle(UINT message, WPARAM wParam, LPARAM lParam);

private:
	GLCanvas* _canvas;
};

END_LFRL_OGL_WND_NAMESPACE

#endif
