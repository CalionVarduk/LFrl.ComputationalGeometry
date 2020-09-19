#ifndef __LFRL_COMMON_IS_ITERABLE_GUARD__
#define __LFRL_COMMON_IS_ITERABLE_GUARD__

#include <type_traits>
#include "../internal/namespace_macros.h"

#define __DECLVAL(TYPE) std::declval<TYPE&>()
#define __BEGIN(TYPE) std::begin(__DECLVAL(TYPE))
#define __END(TYPE) std::end(__DECLVAL(TYPE))

BEGIN_LFRL_COMMON_NAMESPACE

namespace __detail
{
	struct __false_t { char _[1]; };
	struct __true_t { char _[2]; };

	template <class T>
	auto __is_iterable_check(int) -> decltype(
		__BEGIN(T) != __END(T),
		void(),
		++__DECLVAL(decltype(__BEGIN(T))),
		void(*__BEGIN(T)),
		std::declval<typename std::conditional<std::is_same<decltype(__BEGIN(T)), decltype(__END(T))>::value, __true_t, __false_t>::type>());

	template <class T>
	__false_t __is_iterable_check(...);
}

template <class T>
struct is_iterable
{
	typedef T type;
	static constexpr bool value = sizeof(__detail::__is_iterable_check<T>(0)) == sizeof(__detail::__true_t);
};

template <class T, class V>
struct is_iterable_of
{
	typedef T type;
	typedef V value_type;
	static constexpr bool value = is_iterable<T>::value && std::is_same<decltype(*__BEGIN(T)), V&>::value;
};

END_LFRL_COMMON_NAMESPACE

#undef __DECLVAL
#undef __BEGIN
#undef __END

#endif
