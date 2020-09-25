#ifndef __LFRL_COMMON_ALL_TRAITS_GUARD__
#define __LFRL_COMMON_ALL_TRAITS_GUARD__

#include "all.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class... Traits>
struct all_traits
{
	static constexpr bool value = all<(Traits::value)...>::value;
};

END_LFRL_COMMON_NAMESPACE

#endif
