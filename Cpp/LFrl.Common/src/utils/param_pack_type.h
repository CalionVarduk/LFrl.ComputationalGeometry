#ifndef __LFRL_COMMON_PARAM_PACK_TYPE_GUARD__
#define __LFRL_COMMON_PARAM_PACK_TYPE_GUARD__

#include "typedefs.h"

BEGIN_LFRL_NAMESPACE

template <u32 i, class T, class... Ts>
struct param_pack_type
{
	static_assert(i <= sizeof...(Ts), "param_pack_type<i, Ts...>: i must be less than size of Ts.");
	typedef typename param_pack_type<i - 1, Ts...>::type type;
};

template <class T, class... Ts>
struct param_pack_type<0, T, Ts...>
{
	typedef T type;
};

END_LFRL_NAMESPACE

#endif
