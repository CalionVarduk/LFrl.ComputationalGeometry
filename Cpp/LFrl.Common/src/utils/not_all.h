#ifndef __LFRL_COMMON_NOT_ALL_GUARD__
#define __LFRL_COMMON_NOT_ALL_GUARD__

#include "not.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <bool... tests> struct not_all;

template <bool test, bool... tests>
struct not_all<test, tests...> {
	static constexpr bool value = not<test> || not_all<tests...>::value;
};

template <bool test>
struct not_all<test> {
	static constexpr bool value = not<test>;
};

template <>
struct not_all<> {
	static constexpr bool value = false;
};

END_LFRLCOMMON_NAMESPACE

#endif
