#ifndef __LFRL_COMMON_PARAM_MOVE_GUARD__
#define __LFRL_COMMON_PARAM_MOVE_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class T>
constexpr typename std::conditional<std::is_const<typename std::remove_reference<T>::type>::value,
typename std::remove_reference<T>::type const&,
typename std::remove_reference<T>::type&&>::type
	param_move(T&& x)
{
	return static_cast<typename std::conditional<std::is_const<typename std::remove_reference<T>::type>::value,
		typename std::remove_reference<T>::type const&,
		typename std::remove_reference<T>::type&&>::type>(x);
}

END_LFRL_COMMON_NAMESPACE

#endif
