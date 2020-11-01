#ifndef __LFRL_COMMON_STATIC_CTOR_GUARD__
#define __LFRL_COMMON_STATIC_CTOR_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <void(*ctor)()>
struct static_ctor
{
	static_assert(ctor != nullptr, "static_ctor<void(*)()>: provided ctor function can't be null.");

	static struct __ctor_impl
	{
		__ctor_impl() { ctor(); }
	} setup;
};

template <void(*ctor)()>
typename static_ctor<ctor>::__ctor_impl static_ctor<ctor>::setup;

END_LFRL_NAMESPACE

#endif
