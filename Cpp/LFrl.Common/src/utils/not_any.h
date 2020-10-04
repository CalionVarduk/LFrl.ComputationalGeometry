#ifndef __LFRL_COMMON_NOT_ANY_GUARD__
#define __LFRL_COMMON_NOT_ANY_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <bool... tests> struct not_any;

template <bool test, bool... tests>
struct not_any<test, tests...>
{
	static constexpr bool value = !test && not_any<tests...>::value;
};

template <bool test>
struct not_any<test>
{
	static constexpr bool value = !test;
};

template <>
struct not_any<>
{
	static constexpr bool value = true;
};

END_LFRL_NAMESPACE

#endif
