#ifndef __LFRL_CG_API_POINT_TEST_API_GUARD__
#define __LFRL_CG_API_POINT_TEST_API_GUARD__

#include "../internal/api_macros.h"
#include "utils.h"
#include "LFrl.OGL/src/wnd/GLCanvas.h"
#include "LFrl.OGL.CG/src/context/PointTestContextFactory.h"

typedef LFRL_OGL_WND::GLCanvas GLCANVAS;
typedef GLCANVAS* PGLCANVAS;
typedef GLCANVAS const* PCGLCANVAS;

BEGIN_LFRL_CG_API

LFRL_CG_API_ENTRY(PGLCANVAS) lfrl_cg_api_point_test_gl_canvas_create(HWND parentHwnd, INT width, INT height);
LFRL_CG_API_ENTRY(ACTION_RESULT) lfrl_cg_api_point_test_gl_canvas_dispose(PGLCANVAS pThis);
LFRL_CG_API_ENTRY(ACTION_RESULT) lfrl_cg_api_point_test_gl_canvas_get_hwnd(PCGLCANVAS pThis, HWND& result);

END_LFRL_CG_API

#endif
