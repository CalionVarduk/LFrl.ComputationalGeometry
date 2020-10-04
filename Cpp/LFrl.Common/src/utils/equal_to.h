#ifndef __LFRL_COMMON_EQUAL_TO_GUARD__
#define __LFRL_COMMON_EQUAL_TO_GUARD__

#include <functional>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_NAMESPACE

template <class T>
struct ptr_equal_to
{
	bool operator()(T const* lhs, T const* rhs) const
	{
		return lhs == rhs || (lhs != nullptr && rhs != nullptr && std::equal_to<T>()(*lhs, *rhs));
	}
};

END_LFRL_NAMESPACE

#endif
