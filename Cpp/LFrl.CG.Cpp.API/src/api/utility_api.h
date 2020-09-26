#ifndef __LFRL_CG_API_SETUP_API_GUARD__
#define __LFRL_CG_API_SETUP_API_GUARD__

#include "../internal/api_macros.h"
#include "utils.h"
#include "LFrl.OGL/src/Initialize.h"
#include "LFrl.OGL/src/wnd/GLCanvas.h"

BEGIN_LFRL_CG_API

LFRL_CG_API_ENTRY(INT) lfrl_cg_api_utility_setup_gl();
LFRL_CG_API_ENTRY(INT) lfrl_cg_api_utility_setup_winapi();
LFRL_CG_API_ENTRY(INT) lfrl_cg_api_utility_dispose_winapi();
// TODO: logger configuration? ogl debug?

END_LFRL_CG_API

#endif
