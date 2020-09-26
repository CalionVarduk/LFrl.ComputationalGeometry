#ifndef __LFRL_CG_API_STORE_API_GUARD__
#define __LFRL_CG_API_STORE_API_GUARD__

#include "../internal/api_macros.h"
#include "utils.h"

BEGIN_LFRL_CG_API

LFRL_CG_API_ENTRY(ACTION_RESULT) lfrl_cg_api_store_add(LPVOID obj);
LFRL_CG_API_ENTRY(BOOL) lfrl_cg_api_store_contains(LPCVOID obj);
LFRL_CG_API_ENTRY(INT) lfrl_cg_api_store_get_size();
LFRL_CG_API_ENTRY(ACTION_RESULT) lfrl_cg_api_store_delete(LPCVOID obj);

END_LFRL_CG_API

#endif
