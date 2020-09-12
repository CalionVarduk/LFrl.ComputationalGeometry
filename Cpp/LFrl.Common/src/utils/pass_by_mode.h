#ifndef __LFRL_COMMON_PASS_BY_MODE_GUARD__
#define __LFRL_COMMON_PASS_BY_MODE_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

enum struct pass_by_mode {
    value = 0,
    cref = 1
};

END_LFRLCOMMON_NAMESPACE

#endif
