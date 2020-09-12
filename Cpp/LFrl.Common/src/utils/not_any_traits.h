#ifndef __LFRL_COMMON_NOT_ANY_TRAITS_GUARD__
#define __LFRL_COMMON_NOT_ANY_TRAITS_GUARD__

#include "not_any.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class... Traits>
struct not_any_traits
{
	static constexpr bool value = not_any<(Traits::value)...>::value;
};

END_LFRLCOMMON_NAMESPACE

#endif
