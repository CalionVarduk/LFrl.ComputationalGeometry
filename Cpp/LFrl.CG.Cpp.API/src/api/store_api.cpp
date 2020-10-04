#include "store_api.h"

ACTION_RESULT lfrl_cg_api_store_add(LPVOID obj)
{
	auto result = sStore->Add(obj);
	return LFRL_CG_API::GetActionResult(result);
}

BOOL lfrl_cg_api_store_contains(LPCVOID obj)
{
	return sStore->Contains(obj);
}

INT lfrl_cg_api_store_get_size()
{
	return static_cast<INT>(sStore->GetSize());
}

ACTION_RESULT lfrl_cg_api_store_delete(LPCVOID obj)
{
	auto result = sStore->Delete(obj);
	return LFRL_CG_API::GetActionResult(result);
}
