#ifndef __LFRL_COMMON_COMPARER_GUARD__
#define __LFRL_COMMON_COMPARER_GUARD__

#include "param.h"

BEGIN_LFRL_NAMESPACE

template <class T>
struct comparer final
{
	typedef T type;
	typedef param<T> param_type;
	bool operator()(param_type o1, param_type o2) const { return o1 < o2; }
};

template <class T, class TComparer = comparer<T>>
struct reverse_comparer final
{
	typedef T type;
	typedef param<T> param_type;
	typedef TComparer comparer_type;
	bool operator()(param_type o1, param_type o2) const { return !comparer_type()(o1, o2); }
};

END_LFRL_NAMESPACE

#define LFRL_COMMON_SPECIALIZE_COMPARER(TYPE, BODY)\
template <> struct LFRL::comparer<TYPE> {\
typedef TYPE type;\
typedef LFRL::param<TYPE> param_type;\
bool operator()(LFRL::param<TYPE> o1, LFRL::param<TYPE> o2) const {\
BODY;\
}\
};

#endif
