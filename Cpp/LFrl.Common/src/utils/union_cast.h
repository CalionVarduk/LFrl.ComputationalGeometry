#ifndef __LFRL_COMMON_UNION_CAST_GUARD__
#define __LFRL_COMMON_UNION_CAST_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class Out, class In>
Out union_cast(In val) noexcept
{
	union { In i; Out o; } u = { val };
	return u.o;
}

END_LFRL_COMMON_NAMESPACE

#endif
