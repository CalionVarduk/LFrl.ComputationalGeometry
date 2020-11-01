#ifndef __LFRL_COMMON_NOT_TRAIT_GUARD__
#define __LFRL_COMMON_NOT_TRAIT_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <class Trait>
struct not_trait
{
	static constexpr bool value = !Trait::value;
};

END_LFRL_NAMESPACE

#endif
