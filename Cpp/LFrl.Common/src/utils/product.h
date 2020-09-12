#ifndef __LFRL_COMMON_PRODUCT_GUARD__
#define __LFRL_COMMON_PRODUCT_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class T, T... vs> struct product;

template <class T, T v1, T... vs>
struct product<T, v1, vs...> {
	static constexpr T value = v1 * product<T, vs...>::value;
};

template <class T, T v1>
struct product<T, v1> {
	static constexpr T value = v1;
};

template <class T>
struct product<T> {
	static constexpr T value = T(0);
};

END_LFRLCOMMON_NAMESPACE

#endif
