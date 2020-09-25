#ifndef __LFRL_COMMON_IS_PASSED_BY_CONST_REF_GUARD__
#define __LFRL_COMMON_IS_PASSED_BY_CONST_REF_GUARD__

#include "not_trait.h"
#include "any_traits.h"
#include "all_traits.h"
#include "pass_by_mode.h"

#ifndef LFRL_COMMON_PASSING_PARAMS_BY_CONST_REF_THRESHOLD
#define LFRL_COMMON_PASSING_PARAMS_BY_CONST_REF_THRESHOLD 3
#endif

BEGIN_LFRL_COMMON_NAMESPACE

template <class T>
struct is_passed_by_const_ref
{
	typedef T type;
#if defined(LFRL_COMMON_FORCE_PASSING_PARAMS_BY_VALUE) && defined(LFRL_COMMON_FORCE_PASSING_PARAMS_BY_CONST_REF)
#error "LFRL_COMMON_FORCE_PASSING_PARAMS_BY_VALUE and LFRL_COMMON_FORCE_PASSING_PARAMS_BY_CONST_REF are exclusive."
#elif defined(LFRL_COMMON_FORCE_PASSING_PARAMS_BY_VALUE)
	static constexpr bool value = false;
	static constexpr pass_by_mode mode = pass_by_mode::value;
#elif defined(LFRL_COMMON_FORCE_PASSING_PARAMS_BY_CONST_REF)
	static constexpr bool value = true;
	static constexpr pass_by_mode mode = pass_by_mode::cref;
#else
	static constexpr bool value = !(any_traits<std::is_scalar<T>, std::is_void<T>>::value ||
		((std::is_array<T>::value || all_traits<std::is_trivially_destructible<T>, std::is_trivially_copy_constructible<T>>::value) &&
		(sizeof(T) >= LFRL_COMMON_PASSING_PARAMS_BY_CONST_REF_THRESHOLD * sizeof(T*))));

	static constexpr pass_by_mode mode = value ? pass_by_mode::cref : pass_by_mode::value;
#endif
};

END_LFRL_COMMON_NAMESPACE

#define LFRL_COMMON_SPECIALIZE_PASSING_BY_CONST_REF(TYPE, ...)\
template <> struct LFRL_COMMON::is_passed_by_const_ref<TYPE> {\
typedef TYPE type;\
static constexpr bool value = ( __VA_ARGS__ );\
static constexpr pass_by_mode mode = value ? pass_by_mode::cref : pass_by_mode::value;\
};

#endif
