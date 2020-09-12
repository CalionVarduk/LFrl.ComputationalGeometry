#ifndef __LFRL_COMMON_NOT_TRAIT_GUARD__
#define __LFRL_COMMON_NOT_TRAIT_GUARD__

#include "not.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class Trait>
struct not_trait {
	static constexpr bool value = not<Trait::value>;
};

END_LFRLCOMMON_NAMESPACE

#endif
