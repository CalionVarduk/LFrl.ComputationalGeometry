#ifndef __LFRL_COMMON_REQUIRES_GUARD__
#define __LFRL_COMMON_REQUIRES_GUARD__

#include "all_traits.h"
#include "any_traits.h"
#include "not_trait.h"

BEGIN_LFRLCOMMON_NAMESPACE

namespace __detail {
	typedef std::nullptr_t enabling_type;
}

template <bool test>
using requires = typename std::enable_if<test, __detail::enabling_type>::type;

template <bool... tests>
using requires_all = typename std::enable_if<all<tests...>::value, __detail::enabling_type>::type;

template <bool... tests>
using requires_any = typename std::enable_if<any<tests...>::value, __detail::enabling_type>::type;

template <typename Trait>
using requires_trait = typename std::enable_if<Trait::value, __detail::enabling_type>::type;

template <typename... Traits>
using requires_all_traits = typename std::enable_if<all_traits<Traits...>::value, __detail::enabling_type>::type;

template <typename... Traits>
using requires_any_traits = typename std::enable_if<any_traits<Traits...>::value, __detail::enabling_type>::type;

END_LFRLCOMMON_NAMESPACE

#endif
