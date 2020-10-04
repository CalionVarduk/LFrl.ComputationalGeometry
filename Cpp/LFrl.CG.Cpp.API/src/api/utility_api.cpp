#include "utility_api.h"

INT lfrl_cg_api_utility_setup_gl()
{
	auto result = LFRL_OGL::Initialize();
	if (result == LFRL_OGL::InitializationResult::OK)
	{
		sServices->Add(new LFRL_OGL::ShaderStore());
		return static_cast<INT>(ACTION_RESULT::OK);
	}
	auto apiResult = LFRL_CG_API::GetOtherFailureResult(static_cast<LFRL::u16>(result));
	return static_cast<INT>(apiResult);
}

INT lfrl_cg_api_utility_setup_winapi()
{
	auto result = LFRL_OGL_WND::GLCanvas::Register();
	if (result == LFRL_OGL_WND::Class::ActionResult::OK)
		return static_cast<INT>(ACTION_RESULT::OK);
	
	auto apiResult = LFRL_CG_API::GetOtherFailureResult(static_cast<LFRL::u16>(result));
	return static_cast<INT>(apiResult);
}

INT lfrl_cg_api_utility_dispose_winapi()
{
	auto result = LFRL_OGL_WND::GLCanvas::Unregister();
	if (result == LFRL_OGL_WND::Class::ActionResult::OK)
		return static_cast<INT>(ACTION_RESULT::OK);

	auto apiResult = LFRL_CG_API::GetOtherFailureResult(static_cast<LFRL::u16>(result));
	return static_cast<INT>(apiResult);
}
