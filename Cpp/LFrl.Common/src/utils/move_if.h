#ifndef __LFRL_COMMON_MOVE_IF_GUARD__
#define __LFRL_COMMON_MOVE_IF_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <bool test, class T>
constexpr typename std::conditional<test, typename std::remove_reference<T>::type&&, T>::type
	move_if(T&& x)
{
	return static_cast<typename std::conditional<test, typename std::remove_reference<T>::type&&, T>::type>(x);
}

END_LFRLCOMMON_NAMESPACE

#endif
