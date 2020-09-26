#ifndef __LFRL_OGL_CG_POINT_TEST_CONTEXT_FACTORY_GUARD__
#define __LFRL_OGL_CG_POINT_TEST_CONTEXT_FACTORY_GUARD__

#include "PointTestContext.h"
#include "LFrl.OGL/src/context/IGLCanvasContextFactory.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

class PointTestContextFactory : public IGLCanvasContextFactory
{
public:
	virtual GLCanvasContext* Create(RenderingContext& rc) override { return new PointTestContext(rc); }
};

END_LFRL_OGL_CG_NAMESPACE

#endif
