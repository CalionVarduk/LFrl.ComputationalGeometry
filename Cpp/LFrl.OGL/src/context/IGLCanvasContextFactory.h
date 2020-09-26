#ifndef __LFRL_OGL_GL_CANVAS_CONTEXT_FACTORY_GUARD__
#define __LFRL_OGL_GL_CANVAS_CONTEXT_FACTORY_GUARD__

#include "GLCanvasContext.h"

BEGIN_LFRL_OGL_NAMESPACE

struct IGLCanvasContextFactory
{
	virtual ~IGLCanvasContextFactory() {}

	virtual GLCanvasContext* Create(RenderingContext& rc) = 0;

protected:
	IGLCanvasContextFactory() noexcept = default;
};

END_LFRL_OGL_NAMESPACE

#endif
