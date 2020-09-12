#ifndef __LFRL_COMMON_IS_ANY_CHAR_GUARD__
#define __LFRL_COMMON_IS_ANY_CHAR_GUARD__

#include "any_traits.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class T>
struct is_any_char
{
	typedef T type;
	static constexpr bool value =
		any_traits<std::is_same<T, char>, std::is_same<T, signed char>, std::is_same<T, unsigned char>,
		std::is_same<T, wchar_t>, std::is_same<T, char16_t>, std::is_same<T, char32_t>>::value;
};

END_LFRLCOMMON_NAMESPACE

#endif
