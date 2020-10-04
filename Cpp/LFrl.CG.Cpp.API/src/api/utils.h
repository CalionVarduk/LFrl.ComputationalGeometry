#ifndef __LFRL_CG_API_UTILS_GUARD__
#define __LFRL_CG_API_UTILS_GUARD__

#include "ActionResult.h"
#include "../Services.h"

typedef LFRL_CG_API::ActionResult ACTION_RESULT;

BEGIN_LFRL_CG_API_NAMESPACE

inline ActionResult GetActionResult(Store::ActionResult result) noexcept
{
	return static_cast<ActionResult>(result);
}

inline u32 CombineResult(ActionResult result, u16 internalResult) noexcept
{
	return static_cast<u32>(result) | (static_cast<u32>(internalResult) << 16);
}

inline u32 GetOtherFailureResult(u16 internalResult) noexcept
{
	return CombineResult(ActionResult::OTHER_FAILURE, internalResult);
}

template <class T>
ActionResult TrySafeCast(void* pThis, T*& result)
{
	auto storeResult = sStore->Get<T>(reinterpret_cast<uPtr>(pThis));
	auto actionResult = GetActionResult(storeResult.first);
	result = storeResult.second;
	return actionResult;
}

template <class T>
ActionResult TrySafeCast(void const* pThis, T const*& result)
{
	auto storeResult = sStore->Get<const T>(reinterpret_cast<uPtr>(pThis));
	auto actionResult = GetActionResult(storeResult.first);
	result = storeResult.second;
	return actionResult;
}

END_LFRL_CG_API_NAMESPACE

#endif
