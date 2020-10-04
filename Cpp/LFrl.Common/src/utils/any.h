#ifndef __LFRL_COMMON_ANY_GUARD__
#define __LFRL_COMMON_ANY_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <bool... tests> struct any;

template <bool test, bool... tests>
struct any<test, tests...>
{
	static constexpr bool value = test || any<tests...>::value;
};

template <bool test>
struct any<test>
{
	static constexpr bool value = test;
};

template <>
struct any<>
{
	static constexpr bool value = false;
};

END_LFRL_NAMESPACE

#endif
