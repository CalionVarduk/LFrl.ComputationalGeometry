#ifndef __LFRL_COMMON_ALL_GUARD__
#define __LFRL_COMMON_ALL_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <bool... tests> struct all;

template <bool test, bool... tests>
struct all<test, tests...>
{
	static constexpr bool value = test && all<tests...>::value;
};

template <bool test>
struct all<test>
{
	static constexpr bool value = test;
};

template <>
struct all<>
{
	static constexpr bool value = true;
};

END_LFRL_NAMESPACE

#endif
