#ifndef __LFRL_COMMON_IS_FUNCTION_POINTER_GUARD__
#define __LFRL_COMMON_IS_FUNCTION_POINTER_GUARD__

#include "all_traits.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class T>
struct is_function_pointer
{
	typedef T type;
	static constexpr bool value = all_traits<std::is_pointer<T>, std::is_function<typename std::remove_pointer<T>::type>>::value;
};

END_LFRL_COMMON_NAMESPACE

#endif
