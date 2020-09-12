#ifndef __LFRL_COMMON_NOT_ALL_TRAITS_GUARD__
#define __LFRL_COMMON_NOT_ALL_TRAITS_GUARD__

#include "not_all.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class... Traits>
struct not_all_traits
{
	static constexpr bool value = not_all<(Traits::value)...>::value;
};

END_LFRLCOMMON_NAMESPACE

#endif
