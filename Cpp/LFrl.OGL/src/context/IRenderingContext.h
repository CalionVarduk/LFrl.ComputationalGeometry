#ifndef __LFRL_OGL_RENDERING_CONTEXT_GUARD__
#define __LFRL_OGL_RENDERING_CONTEXT_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

struct RenderingAttributes
{

};

// represents HGLRC, created from HWND
// should have relation to DeviceContext
struct IRenderingContext
{
	IRenderingContext() = default;
	IRenderingContext(IRenderingContext const&) = delete;
	IRenderingContext(IRenderingContext&&) = delete;
	IRenderingContext& operator=(IRenderingContext const&) = delete;
	IRenderingContext& operator=(IRenderingContext&&) = delete;

	virtual ~IRenderingContext();
};

END_LFRL_OGL_NAMESPACE

#endif
