#ifndef __LFRL_COMMON_PARAM_GUARD__
#define __LFRL_COMMON_PARAM_GUARD__

#include "is_passed_by_const_ref.h"
#include "param_move.h"

BEGIN_LFRLCOMMON_NAMESPACE

template <class T>
struct param_type
{
	typedef typename std::conditional<is_passed_by_const_ref<T>::value, T const&, T>::type type;
	static constexpr pass_by_mode mode = is_passed_by_const_ref<T>::mode;
};

template <class T>
using param = typename param_type<T>::type;

END_LFRLCOMMON_NAMESPACE

#endif
