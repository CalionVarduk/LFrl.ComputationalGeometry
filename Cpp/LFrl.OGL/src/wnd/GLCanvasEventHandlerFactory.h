#ifndef __LFRL_OGL_WND_GL_CANVAS_EVENT_HANDLER_FACTORY_GUARD__
#define __LFRL_OGL_WND_GL_CANVAS_EVENT_HANDLER_FACTORY_GUARD__

#include "GLCanvasEventHandler.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

struct GLCanvasEventHandlerFactory
{
	GLCanvasEventHandlerFactory() noexcept = default;

	virtual ~GLCanvasEventHandlerFactory() {}

	virtual GLCanvasEventHandler* Create(GLCanvas& canvas) { return new GLCanvasEventHandler(canvas); }
};

END_LFRL_OGL_WND_NAMESPACE

#endif
