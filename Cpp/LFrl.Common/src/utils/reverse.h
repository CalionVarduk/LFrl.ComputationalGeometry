#ifndef __LFRL_COMMON_REVERSE_GUARD__
#define __LFRL_COMMON_REVERSE_GUARD__

#include <iterator>
#include "is_iterable.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class TIterable>
struct reverse final
{
	static_assert(is_iterable<TIterable>::value, "reverse<TIterable>: TIterable must be a valid iterable type.");

	typedef TIterable iterable_type;
	typedef typename is_iterable<TIterable>::iterator_type original_iterator;
	typedef typename is_iterable<TIterable>::const_iterator_type original_const_iterator;
	typedef std::reverse_iterator<original_iterator> reverse_iterator;
	typedef std::reverse_iterator<original_const_iterator> const_reverse_iterator;

	TIterable& iterable;

	reverse(TIterable& iterable) noexcept : iterable(iterable) {}

	reverse_iterator begin() { return reverse_iterator(iterable.end()); }
	const_reverse_iterator begin() const { return const_reverse_iterator(iterable.end()); }
	reverse_iterator end() { return reverse_iterator(iterable.begin()); }
	const_reverse_iterator end() const { return const_reverse_iterator(iterable.begin()); }
};

END_LFRL_COMMON_NAMESPACE

#endif
