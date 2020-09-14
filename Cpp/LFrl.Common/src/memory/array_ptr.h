#ifndef __LFRL_COMMON_ARRAY_PTR_GUARD__
#define __LFRL_COMMON_ARRAY_PTR_GUARD__

#include <iterator>
#include "../utils/typedefs.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class T>
struct array_ptr final
{
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type const* const_pointer;
	typedef value_type& reference;
	typedef value_type const& const_reference;
	typedef sz size_type;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	array_ptr() noexcept = default;
	array_ptr(array_ptr<T> const&) noexcept = default;
	array_ptr(array_ptr<T>&&) noexcept = default;
	~array_ptr() noexcept = default;
	array_ptr<T>& operator= (array_ptr<T> const&) noexcept = default;
	array_ptr<T>& operator= (array_ptr<T>&&) noexcept = default;

	array_ptr(pointer begin, pointer end) noexcept;
	array_ptr(pointer begin, size_type size) noexcept;

	array_ptr<const T> to_const() const noexcept { return array_ptr<const T>(_begin, _end); }

	size_type size() const noexcept { return (size_type)(_end - _begin); }
	bool empty() const noexcept { return _end <= _begin; }

	iterator begin() noexcept { return _begin; }
	const_iterator begin() const noexcept { return _begin; }
	const_iterator cbegin() const noexcept { return _begin; }
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
	iterator end() noexcept { return _end; }
	const_iterator end() const noexcept { return _end; }
	const_iterator cend() const noexcept { return _end; }
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

	pointer get() noexcept { return _begin; }
	const_pointer get() const noexcept { return _begin; }

	reference at(size_type i) noexcept(false);
	const_reference at(size_type i) const noexcept(false);

	reference front() { return *_begin; }
	const_reference front() const { return *_begin; }
	reference back() { return *(_end - 1); }
	const_reference back() const { return *(_end - 1); }

	reference operator[] (size_type i) { return _begin[i]; }
	const_reference operator[] (size_type i) const { return _begin[i]; }

private:
	const pointer _begin;
	const pointer _end;
};

template <class T>
array_ptr<T>::array_ptr(typename array_ptr<T>::pointer begin, typename array_ptr<T>::pointer end) noexcept
	: _begin(begin), _end(end)
{}

template <class T>
array_ptr<T>::array_ptr(typename array_ptr<T>::pointer begin, typename array_ptr<T>::size_type size) noexcept
	: _begin(begin), _end(begin + size)
{}

template <class T>
typename array_ptr<T>::reference array_ptr<T>::at(typename array_ptr<T>::size_type i) noexcept(false)
{
	if (i >= size())
		throw std::out_of_range("index is out of range");

	return _begin[i];
}

template <class T>
typename array_ptr<T>::const_reference array_ptr<T>::at(typename array_ptr<T>::size_type i) const noexcept(false)
{
	if (i >= size())
		throw std::out_of_range("index is out of range");

	return _begin[i];
}

template <class T>
array_ptr<T> make_array_ptr(typename array_ptr<T>::pointer begin, typename array_ptr<T>::pointer end) noexcept
{
	return array_ptr<T>(begin, end);
}

template <class T>
array_ptr<T> make_array_ptr(typename array_ptr<T>::pointer begin, typename array_ptr<T>::size_type size) noexcept
{
	return array_ptr<T>(begin, size);
}

template <class T>
array_ptr<const T> make_const_array_ptr(typename array_ptr<const T>::pointer begin, typename array_ptr<const T>::pointer end) noexcept
{
	return array_ptr<const T>(begin, end);
}

template <class T>
array_ptr<const T> make_const_array_ptr(typename array_ptr<const T>::pointer begin, typename array_ptr<const T>::size_type size) noexcept
{
	return array_ptr<const T>(begin, size);
}

END_LFRL_COMMON_NAMESPACE

#endif
