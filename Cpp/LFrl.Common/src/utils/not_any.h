#ifndef __LFRL_COMMON_NOT_ANY_GUARD__
#define __LFRL_COMMON_NOT_ANY_GUARD__

#include "not.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <bool... tests> struct not_any;

template <bool test, bool... tests>
struct not_any<test, tests...> {
	static constexpr bool value = not<test> && not_any<tests...>::value;
};

template <bool test>
struct not_any<test> {
	static constexpr bool value = not<test>;
};

template <>
struct not_any<> {
	static constexpr bool value = true;
};

END_LFRLCOMMON_NAMESPACE

#endif
