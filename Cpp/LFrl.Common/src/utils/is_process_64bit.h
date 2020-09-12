#ifndef __LFRL_COMMON_IS_PROCESS_64_BIT_GUARD__
#define __LFRL_COMMON_IS_PROCESS_64_BIT_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

struct is_process_64bit {
	static constexpr bool value = sizeof(char*) * CHAR_BIT == 64;
};

END_LFRLCOMMON_NAMESPACE

#endif
