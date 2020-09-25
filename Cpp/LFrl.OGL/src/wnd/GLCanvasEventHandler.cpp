#include "GLCanvasEventHandler.h"

#include "GLCanvas.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

GLCanvasEventHandler::GLCanvasEventHandler(GLCanvas& canvas) noexcept
	: _canvas(&canvas)
{}

LRESULT GLCanvasEventHandler::Handle(UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(_canvas->GetHandle()->GetHwnd(), message, wParam, lParam);
}

END_LFRL_OGL_WND_NAMESPACE
