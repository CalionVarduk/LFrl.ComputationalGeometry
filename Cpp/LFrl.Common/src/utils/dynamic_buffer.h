#ifndef __LFRL_COMMON_DYNAMIC_BUFFER_GUARD__
#define __LFRL_COMMON_DYNAMIC_BUFFER_GUARD__

#include <cstring>
#include "typedefs.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class T>
struct dynamic_buffer final
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

	dynamic_buffer() = delete;
	dynamic_buffer(dynamic_buffer<T> const&) = delete;
	dynamic_buffer(dynamic_buffer<T>&&) noexcept = default;
	dynamic_buffer<T>& operator= (dynamic_buffer<T> const&) = delete;
	dynamic_buffer<T>& operator= (dynamic_buffer<T>&&) noexcept = default;

	explicit dynamic_buffer(size_type size);
	~dynamic_buffer();

	void reset();

	bool ok() const noexcept { return _data !== nullptr; }
	size_type size() const noexcept { return _size; }
	pointer data() const noexcept { return _data; }

	iterator begin() noexcept { return _data; }
	const_iterator begin() const noexcept { return _data; }
	const_iterator cbegin() const noexcept { return _data; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
	iterator end() noexcept { return _data + _size; }
	const_iterator end() const noexcept { return _data + _size; }
    const_iterator cend() const noexcept { return _data + _size; }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

	reference operator[] (i32 index) noexcept(false) { return _data[index]; }
    reference operator[] (u32 index) noexcept(false) { return _data[index]; }
    reference operator[] (i64 index) noexcept(false) { return _data[index]; }
    reference operator[] (u64 index) noexcept(false) { return _data[index]; }
	const_reference operator[] (i32 index) const noexcept(false) { return _data[index]; }
    const_reference operator[] (u32 index) const noexcept(false) { return _data[index]; }
    const_reference operator[] (i64 index) const noexcept(false) { return _data[index]; }
    const_reference operator[] (u64 index) const noexcept(false) { return _data[index]; }

private:
	size_type _size;
	pointer _data;
};

template <class T>
dynamic_buffer<T>::dynamic_buffer(typename dynamic_buffer<T>::size_type size)
	: _size(size),
	_data([size]() -> auto {
		if (size == 0)
			return static_cast<T*>(nullptr);

		auto result = new T[size];
		std::memset(result, 0, size);
		return result;
	}())
{}

template <class T>
dynamic_buffer<T>::~dynamic_buffer()
{
	delete[] _data;
	_data = nullptr;
	_size = 0;
}

template <class T>
void dynamic_buffer<T>::reset()
{
	if (ok())
		std::memset(_data, 0, _size);
}

END_LFRL_COMMON_NAMESPACE

#endif
