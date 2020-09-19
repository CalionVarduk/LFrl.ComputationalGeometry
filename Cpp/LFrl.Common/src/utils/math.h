#ifndef __LFRL_COMMON_MATH_GUARD__
#define __LFRL_COMMON_MATH_GUARD__

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "param.h"
#include "requires.h"
#include <math.h>

BEGIN_LFRL_COMMON_NAMESPACE

template <class T, requires<std::is_floating_point<T>::value> = 0>
constexpr T pi() noexcept
{
	return static_cast<T>(M_PI);
}

template <class T, requires<std::is_floating_point<T>::value> = 0>
constexpr T pi_by_c180() noexcept
{
	return pi<T>() / 180;
}

template <class T, requires<std::is_floating_point<T>::value> = 0>
constexpr T c180_by_pi() noexcept
{
	return 180 / pi<T>();
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr T abs(param<T> v)
{
	return v < static_cast<T>(0) ? -v : v;
}

template <class T>
constexpr T min(param<T> v1, param<T> v2)
{
	return v1 < v2 ? v1 : v2;
}

template <class T>
constexpr T max(param<T> v1, param<T> v2)
{
	return v1 > v2 ? v1 : v2;
}

template <class T>
constexpr T at_least(param<T> min, param<T> v)
{
	return max<T>(min, v);
}

template <class T>
constexpr T at_most(param<T> max, param<T> v)
{
	return min<T>(max, v);
}

template <class T>
constexpr T between(param<T> min, param<T> max, param<T> v)
{
	return v < min ? min : v > max ? max : v;
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_equal(param<T> v1, param<T> v2, param<T> eps)
{
	return abs<T>(v1 - v2) <= eps;
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_not_equal(param<T> v1, param<T> v2, param<T> eps)
{
	return !fuzzy_equal<T>(v1, v2, eps);
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_is_greater(param<T> v1, param<T> v2, param<T> eps)
{
	return fuzzy_not_equal<T>(v1, v2, eps) && (v1 > v2);
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_is_less(param<T> v1, param<T> v2, param<T> eps)
{
	return fuzzy_not_equal<T>(v1, v2, eps) && (v1 < v2);
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_is_greater_or_equal(param<T> v1, param<T> v2, param<T> eps)
{
	return !fuzzy_is_less<T>(v1, v2, eps);
}

template <class T, requires<std::is_convertible<int, T>::value> = 0>
constexpr bool fuzzy_is_less_or_equal(param<T> v1, param<T> v2, param<T> eps)
{
	return !fuzzy_is_greater<T>(v1, v2, eps);
}

template <class T, requires<std::is_same<T, float>::value> = 0>
T sqrt(param<T> v)
{
	return ::sqrtf(v);
}

template <class T, requires<std::is_same<T, double>::value> = 0>
T sqrt(param<T> v)
{
	return ::sqrt(v);
}

template <class T, requires<std::is_same<T, long double>::value> = 0>
T sqrt(param<T> v)
{
	return ::sqrtl(v);
}

template <class T, requires_all<!std::is_floating_point<T>::value, std::is_convertible<T, double>::value, std::is_convertible<double, T>::value> = 0>
T sqrt(param<T> v)
{
	return static_cast<T>(sqrt<double>(static_cast<double>(v)));
}

template <class T, requires<std::is_same<T, float>::value> = 0>
T sin(param<T> v)
{
	return ::sinf(v);
}

template <class T, requires<std::is_same<T, double>::value> = 0>
T sin(param<T> v)
{
	return ::sin(v);
}

template <class T, requires<std::is_same<T, long double>::value> = 0>
T sin(param<T> v)
{
	return ::sinl(v);
}

template <class T, requires_all<!std::is_floating_point<T>::value, std::is_convertible<T, double>::value, std::is_convertible<double, T>::value> = 0>
T sin(param<T> v)
{
	return static_cast<T>(sin<double>(static_cast<double>(v)));
}

template <class T, requires<std::is_same<T, float>::value> = 0>
T cos(param<T> v)
{
	return ::cosf(v);
}

template <class T, requires<std::is_same<T, double>::value> = 0>
T cos(param<T> v)
{
	return ::cos(v);
}

template <class T, requires<std::is_same<T, long double>::value> = 0>
T cos(param<T> v)
{
	return ::cosl(v);
}

template <class T, requires_all<!std::is_floating_point<T>::value, std::is_convertible<T, double>::value, std::is_convertible<double, T>::value> = 0>
T cos(param<T> v)
{
	return static_cast<T>(cos<double>(static_cast<double>(v)));
}

template <class T, requires<std::is_same<T, float>::value> = 0>
T atan2(param<T> y, param<T> x)
{
	return ::atan2f(y, x);
}

template <class T, requires<std::is_same<T, double>::value> = 0>
T atan2(param<T> y, param<T> x)
{
	return ::atan2(y, x);
}

template <class T, requires<std::is_same<T, long double>::value> = 0>
T atan2(param<T> y, param<T> x)
{
	return ::atan2l(y, x);
}

template <class T, requires_all<!std::is_floating_point<T>::value, std::is_convertible<T, double>::value, std::is_convertible<double, T>::value> = 0>
T atan2(param<T> y, param<T> x)
{
	return static_cast<T>(atan2<double>(static_cast<double>(y), static_cast<double>(x)));
}

template <class T, requires<std::is_convertible<double, T>::value> = 0>
constexpr T deg_to_rad(param<T> deg)
{
	return deg * static_cast<T>(pi_by_c180<double>());
}

template <class T, requires<std::is_convertible<double, T>::value> = 0>
constexpr T rad_to_deg(param<T> rad)
{
	return rad * static_cast<T>(c180_by_pi<double>());
}

END_LFRL_COMMON_NAMESPACE

#endif
