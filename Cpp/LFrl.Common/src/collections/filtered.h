#ifndef __LFRL_COMMON_FILTERED_GUARD__
#define __LFRL_COMMON_FILTERED_GUARD__

#include <iterator>
#include "../utils/is_iterable.h"
#include "../utils/requires.h"

BEGIN_LFRL_NAMESPACE

template <class TIter, class TPred>
struct filter_iterator;

template <class TIter, class TPred>
filter_iterator<TIter, TPred> filter(TIter begin, TIter end, TPred predicate);

template <class TIter, class TPred>
filter_iterator<TIter, TPred> filter_end(TIter end, TPred predicate);

template <class TIter, class TPred>
struct filter_iterator final
{
	friend filter_iterator LFrl::filter(TIter, TIter, TPred);
	friend filter_iterator LFrl::filter_end(TIter, TPred);

	typedef TIter iterator_type;
	typedef TPred predicate_type;
	typedef std::forward_iterator_tag iterator_category;
	typedef typename std::iterator_traits<TIter>::difference_type difference_type;
	typedef typename std::iterator_traits<TIter>::value_type value_type;
	typedef typename std::iterator_traits<TIter>::pointer pointer;
	typedef typename std::iterator_traits<TIter>::reference reference;

	filter_iterator() = default;
	filter_iterator(filter_iterator<TIter, TPred> const&) = default;
	filter_iterator(filter_iterator<TIter, TPred>&&) = default;
	filter_iterator<TIter, TPred>& operator=(filter_iterator<TIter, TPred> const&) = default;
	filter_iterator<TIter, TPred>& operator=(filter_iterator<TIter, TPred>&&) = default;

	predicate_type predicate() const { return _predicate; }
	iterator_type current() const { return _it; }
	iterator_type end() const { return _end; }
	filter_iterator<TIter, TPred> filter_end() const { return ::filter_end(_end, _predicate); }

	filter_iterator<TIter, TPred>& operator++();
	filter_iterator<TIter, TPred> operator++(int);

	template <class I = TIter, requires<std::is_pointer<I>::value> = 0>
	pointer operator->() { return static_cast<pointer>(_it); }

	template <class I = TIter, requires<!std::is_pointer<I>::value> = 0>
	pointer operator->() { return _it.operator->(); }

	template <class I = TIter, requires<std::is_pointer<I>::value> = 0>
	value_type const* operator->() const { return static_cast<value_type const*>(_it); }

	template <class I = TIter, requires<!std::is_pointer<I>::value> = 0>
	value_type const* operator->() const { return _it.operator->(); }

	reference operator*() { return *_it; }
	value_type const& operator*() const { return *_it; }

	bool operator==(filter_iterator<TIter, TPred> const& other) const { return _it == other._it; }
	bool operator!=(filter_iterator<TIter, TPred> const& other) const { return _it != other._it; }
	bool operator==(TIter const& other) const { return _it == other; }
	bool operator!=(TIter const& other) const { return _it != other; }

private:
	iterator_type _it;
	iterator_type _end;
	predicate_type _predicate;

	filter_iterator(TIter it, TIter end, TPred predicate) : _it(it), _end(end), _predicate(predicate) {}
	void _init();
};

template <class TIter, class TPred>
filter_iterator<TIter, TPred>& filter_iterator<TIter, TPred>::operator++()
{
	if (_it != _end)
	{
		++_it;
		while (_it != _end && !static_cast<bool>(_predicate(*_it)))
			++_it;
	}
	return *this;
}

template <class TIter, class TPred>
filter_iterator<TIter, TPred> filter_iterator<TIter, TPred>::operator++(int)
{
	filter_iterator<TIter, TPred> result(*this);
	++(*this);
	return result;
}

template <class TIter, class TPred>
void filter_iterator<TIter, TPred>::_init()
{
	if (_it != _end && !static_cast<bool>(_predicate(*_it)))
	{
		++_it;
		while (_it != _end && !static_cast<bool>(_predicate(*_it)))
			++_it;
	}
}

template <class TIter, class TPred>
filter_iterator<TIter, TPred> filter(TIter begin, TIter end, TPred predicate)
{
	filter_iterator<TIter, TPred> result(begin, end, predicate);
	result._init();
	return result;
}

template <class TIter, class TPred>
filter_iterator<TIter, TPred> filter_end(TIter end, TPred predicate)
{
	return filter_iterator<TIter, TPred>(end, end, predicate);
}

template <class TCollection, class TPred>
struct filtered final
{
	static_assert(is_iterable<TCollection>::value, "filtered<TCollection, TPred>: TCollection must be iterable.");

	typedef TCollection collection_type;
	typedef TPred predicate_type;
	typedef typename TCollection::value_type value_type;
	typedef typename TCollection::pointer pointer;
	typedef typename TCollection::const_pointer const_pointer;
	typedef typename TCollection::reference reference;
	typedef typename TCollection::const_reference const_reference;
	typedef typename TCollection::size_type size_type;
	typedef typename TCollection::const_iterator const_collection_iterator;
	typedef typename std::conditional<std::is_const<TCollection>::value, const_collection_iterator, typename TCollection::iterator>::type collection_iterator;
	typedef typename TCollection::const_reverse_iterator const_reverse_collection_iterator;
	typedef typename std::conditional<std::is_const<TCollection>::value, const_reverse_collection_iterator, typename TCollection::reverse_iterator>::type reverse_collection_iterator;
	typedef filter_iterator<collection_iterator, TPred> iterator;
	typedef filter_iterator<const_collection_iterator, TPred> const_iterator;
	typedef filter_iterator<reverse_collection_iterator, TPred> reverse_iterator;
	typedef filter_iterator<const_reverse_collection_iterator, TPred> const_reverse_iterator;

	TCollection* const collection;

	filtered() = delete;
	filtered(filtered<TCollection, TPred> const&) = default;
	filtered(filtered<TCollection, TPred>&&) = default;
	filtered(TCollection& collection, TPred predicate) : collection(&collection), _predicate(predicate) {}
	filtered<TCollection, TPred>& operator=(filtered<TCollection, TPred> const&) = default;
	filtered<TCollection, TPred>& operator=(filtered<TCollection, TPred>&&) = default;

	bool empty() const { return begin() != end(); }
	predicate_type predicate() const { return _predicate; }

	iterator begin() { return filter(collection->begin(), collection->end(), _predicate); }
	const_iterator begin() const { return filter(collection->begin(), collection->end(), _predicate); }
	const_iterator cbegin() const { return filter(collection->cbegin(), collection->cend(), _predicate); }
	reverse_iterator rbegin() { return filter(collection->rbegin(), collection->rend(), _predicate); }
	const_reverse_iterator rbegin() const { return filter(collection->rbegin(), collection->rend(), _predicate); }
	const_reverse_iterator crbegin() const { return filter(collection->crbegin(), collection->crend(), _predicate); }

	collection_iterator end() { return collection->end(); }
	const_collection_iterator end() const { return collection->end(); }
	const_collection_iterator cend() const { return collection->cend(); }
	reverse_collection_iterator rend() { return collection->rend(); }
	const_reverse_collection_iterator rend() const { return collection->rend(); }
	const_reverse_collection_iterator crend() const { return collection->crend(); }

private:
	predicate_type _predicate;
};

template <class TCollection, class TPred>
filtered<TCollection, TPred> filter(TCollection& collection, TPred predicate)
{
	return filtered<TCollection, TPred>(collection, predicate);
}

template <class TCollection, class TPred>
filtered<const TCollection, TPred> filter_const(TCollection const& collection, TPred predicate)
{
	return filtered<const TCollection, TPred>(collection, predicate);
}

END_LFRL_NAMESPACE

namespace std
{
	template <class TIter, class TPred>
	typename LFRL::filter_iterator<TIter, TPred>::difference_type distance(LFRL::filter_iterator<TIter, TPred> const& first, TIter last)
	{
		return std::distance(first, LFRL::filter_end(last, first.predicate()));
	}
}

#endif
