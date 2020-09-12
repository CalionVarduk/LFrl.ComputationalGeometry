#ifndef __LFRL_COMMON_NOT_GUARD__
#define __LFRL_COMMON_NOT_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <bool test>
struct not {
    static constexpr bool value = !test;
};

END_LFRLCOMMON_NAMESPACE

#endif
