#ifndef __LFRL_COMMON_OFFSET_OF_GUARD__
#define __LFRL_COMMON_OFFSET_OF_GUARD__

#include "typedefs.h"

BEGIN_LFRL_NAMESPACE

template <typename T, typename MType>
constexpr sz offset_of(MType T::* mPtr)
{
	return reinterpret_cast<sz>(&(reinterpret_cast<T const*>(nullptr)->*mPtr));
}

END_LFRL_NAMESPACE

#endif
