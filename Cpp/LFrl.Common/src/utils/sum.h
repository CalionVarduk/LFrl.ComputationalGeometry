#ifndef __LFRL_COMMON_SUM_GUARD__
#define __LFRL_COMMON_SUM_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class T, T... vs> struct sum;

template <class T, T v1, T... vs>
struct sum<T, v1, vs...> {
	static constexpr T value = v1 + sum<T, vs...>::value;
};

template <class T, T v1>
struct sum<T, v1> {
	static constexpr T value = v1;
};

template <class T>
struct sum<T> {
	static constexpr T value = T(0);
};

END_LFRLCOMMON_NAMESPACE

#endif
