#ifndef __LFRL_COMMON_ANY_TRAITS_GUARD__
#define __LFRL_COMMON_ANY_TRAITS_GUARD__

#include "any.h"

BEGIN_LFRL_NAMESPACE

template <class... Traits>
struct any_traits
{
	static constexpr bool value = any<(Traits::value)...>::value;
};

END_LFRL_NAMESPACE

#endif
