#include "point_test_api.h"

PGLCANVAS lfrl_cg_api_point_test_gl_canvas_create(HWND parentHwnd, INT width, INT height)
{
	auto shaders = sServices->Get<LFRL_OGL::ShaderStore>();
	if (shaders == nullptr)
		return nullptr;

	LFRL_OGL_CG::PointTestContextFactory factory(shaders);

	auto canvas = sStore->Create<GLCANVAS>();
	auto result = canvas->Initialize(parentHwnd, { 0, 0, width, height }, &factory);
	if (result != LFRL_OGL_WND::GLCanvas::ActionResult::OK)
	{
		sStore->Delete(canvas);
		return nullptr;
	}
	return canvas;
}

ACTION_RESULT lfrl_cg_api_point_test_gl_canvas_dispose(PGLCANVAS pThis)
{
	PGLCANVAS canvas;
	auto actionResult = LFRL_CG_API::TrySafeCast<GLCANVAS>(pThis, canvas);
	if (actionResult == LFRL_CG_API::ActionResult::OK)
	{
		canvas->Dispose();
		sStore->Delete(canvas);
	}
	return actionResult;
}

ACTION_RESULT lfrl_cg_api_point_test_gl_canvas_get_hwnd(PCGLCANVAS pThis, HWND& result)
{
	PCGLCANVAS canvas;
	auto actionResult = LFRL_CG_API::TrySafeCast<GLCANVAS>(pThis, canvas);
	if (actionResult == LFRL_CG_API::ActionResult::OK)
	{
		result = canvas->GetHandle()->GetHwnd();
	}
	else
	{
		result = NULL;
	}
	return actionResult;
}
