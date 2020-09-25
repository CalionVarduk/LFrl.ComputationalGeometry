#ifndef __LFRL_COMMON_NOT_ALL_GUARD__
#define __LFRL_COMMON_NOT_ALL_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <bool... tests> struct not_all;

template <bool test, bool... tests>
struct not_all<test, tests...>
{
	static constexpr bool value = !test || not_all<tests...>::value;
};

template <bool test>
struct not_all<test>
{
	static constexpr bool value = !test;
};

template <>
struct not_all<>
{
	static constexpr bool value = false;
};

END_LFRL_COMMON_NAMESPACE

#endif
