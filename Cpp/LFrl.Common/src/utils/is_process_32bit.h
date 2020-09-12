#ifndef __LFRL_COMMON_IS_PROCESS_32_BIT_GUARD__
#define __LFRL_COMMON_IS_PROCESS_32_BIT_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

struct is_process_32bit {
	static constexpr bool value = sizeof(char*) * CHAR_BIT == 32;
};

END_LFRLCOMMON_NAMESPACE

#endif
