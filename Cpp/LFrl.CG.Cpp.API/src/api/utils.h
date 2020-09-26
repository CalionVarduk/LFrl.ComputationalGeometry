#ifndef __LFRL_CG_API_UTILS_GUARD__
#define __LFRL_CG_API_UTILS_GUARD__

#include "ActionResult.h"
#include "../Services.h"

typedef LFRL_CG_API::ActionResult ACTION_RESULT;

BEGIN_LFRL_CG_API_NAMESPACE

inline ActionResult GetActionResult(Common::Store::ActionResult result) noexcept
{
	return static_cast<ActionResult>(result);
}

inline Common::u32 CombineResult(ActionResult result, Common::u16 internalResult) noexcept
{
	return static_cast<Common::u32>(result) | (static_cast<Common::u32>(internalResult) << 16);
}

template <class T>
ActionResult TrySafeCast(void* pThis, T*& result)
{
	auto storeResult = sStore->Get<T>(reinterpret_cast<Common::uPtr>(pThis));
	auto actionResult = GetActionResult(storeResult.first);
	result = storeResult.second;
	return actionResult;
}

template <class T>
ActionResult TrySafeCast(void const* pThis, T const*& result)
{
	auto storeResult = sStore->Get<const T>(reinterpret_cast<Common::uPtr>(pThis));
	auto actionResult = GetActionResult(storeResult.first);
	result = storeResult.second;
	return actionResult;
}

END_LFRL_CG_API_NAMESPACE

#endif
