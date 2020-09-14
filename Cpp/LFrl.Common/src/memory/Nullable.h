#ifndef __LFRL_COMMON_NULLABLE_GUARD__
#define __LFRL_COMMON_NULLABLE_GUARD__

#include <utility>
#include "../utils/typedefs.h"

BEGIN_LFRL_COMMON_NAMESPACE

template <class T> class Nullable;

template <class T>
struct WeakNullable final
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	WeakNullable() noexcept = default;
	WeakNullable(WeakNullable<T> const&) noexcept = default;
	WeakNullable(WeakNullable<T>&&) noexcept = default;
	WeakNullable<T>& operator=(WeakNullable<T> const&) noexcept = default;
	WeakNullable<T>& operator=(WeakNullable<T>&&) noexcept = default;

	WeakNullable(pointer ptr) noexcept;
	explicit WeakNullable(reference value) noexcept;
	WeakNullable(Nullable<T> const& other) noexcept;
	WeakNullable(Nullable<T>&& other) noexcept;
	WeakNullable(Null) noexcept;

	bool HasValue() const noexcept { return _ptr != nullptr; }
	reference GetValue() const noexcept(false) { return *_ptr; }
	pointer Get() const noexcept { return _ptr; }
	uPtr GetAddress() const noexcept { return (uPtr)_ptr; }

	void Set(pointer ptr) noexcept { _ptr = ptr; }
	void Set(reference value) noexcept { Set(&value); }
	void Set(WeakNullable<T> const& other) noexcept { Set(other.Get()); }
	void Set(Nullable<T> const& other) noexcept { Set(other.Get()); }
	void Set(Nullable<T>&& other) noexcept;
	void Set(Null) noexcept { _ptr = nullptr; }
	void Clear() noexcept { Set(nullptr); }

	WeakNullable<T>& operator=(pointer ptr) noexcept;
	WeakNullable<T>& operator=(Nullable<T> const& other) noexcept;
	WeakNullable<T>& operator=(Nullable<T>&& other) noexcept;
	WeakNullable<T>& operator=(Null) noexcept;

	reference operator*() const noexcept(false) { return GetValue(); }
	pointer operator->() const noexcept { return Get(); }

	operator pointer() const noexcept { return Get(); }
	explicit operator reference() const noexcept(false) { return GetValue(); }
	operator WeakNullable<const T>() const noexcept { return WeakNullable<const T>(_ptr); }

private:
	pointer _ptr;
};

template <class T>
struct Nullable final
{
	Nullable(Nullable<T> const&) = delete;
	Nullable<T>& operator=(Nullable<T> const&) = delete;

public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	Nullable() noexcept = default;
	Nullable(Nullable<T>&&) = default;
	Nullable<T>& operator=(Nullable<T>&&) = default;

	explicit Nullable(pointer ptr) noexcept;
	explicit Nullable(WeakNullable<T> const& other) noexcept;
	Nullable(Null) noexcept;
	~Nullable();

	bool HasValue() const noexcept { return _ptr != nullptr; }
	reference GetValue() const noexcept(false) { return *_ptr; }
	pointer Get() const noexcept { return _ptr; }
	uPtr GetAddress() const noexcept { return (uPtr)_ptr; }

	void Set(pointer ptr);
	void Set(WeakNullable<T> const& other) { Set(other.Get()); }
	void Set(Nullable<T>&& other) { *this = std::move(other); }
	void Set(Null);
	void Clear() { Set(nullptr); }
	void RenounceOwnership() noexcept { _ptr = nullptr; }
	void Swap(Nullable<T>& other) noexcept;

	Nullable<T>& operator=(pointer ptr);
	Nullable<T>& operator=(WeakNullable<T> const& other);
	Nullable<T>& operator=(Null);

	reference operator*() const noexcept(false) { return GetValue(); }
	pointer operator->() const noexcept { return Get(); }

	explicit operator pointer() const noexcept { return Get(); }
	explicit operator reference() const noexcept(false) { return GetValue(); }
	operator WeakNullable<T>() const noexcept { return WeakNullable<T>(_ptr); }

private:
	pointer _ptr;
};

template <class T>
WeakNullable<T>::WeakNullable(typename WeakNullable<T>::pointer ptr) noexcept
	: _ptr(ptr)
{}

template <class T>
WeakNullable<T>::WeakNullable(typename WeakNullable<T>::reference value) noexcept
	: _ptr(&value)
{}

template <class T>
WeakNullable<T>::WeakNullable(Nullable<T> const& other) noexcept
	: _ptr(other.Get())
{}

template <class T>
WeakNullable<T>::WeakNullable(Nullable<T>&& other) noexcept
	: _ptr(other.Get())
{
	other.RenounceOwnership();
}

template <class T>
WeakNullable<T>::WeakNullable(Null) noexcept
	: _ptr(nullptr)
{}

template <class T>
void WeakNullable<T>::Set(Nullable<T>&& other) noexcept
{
	Set(other.Get());
	other.RenounceOwnership();
}

template <class T>
WeakNullable<T>& WeakNullable<T>::operator=(typename WeakNullable<T>::pointer ptr) noexcept
{
	Set(ptr);
	return *this;
}

template <class T>
WeakNullable<T>& WeakNullable<T>::operator=(Nullable<T> const& other) noexcept
{
	Set(other);
	return *this;
}

template <class T>
WeakNullable<T>& WeakNullable<T>::operator=(Nullable<T>&& other) noexcept
{
	Set(other);
	return *this;
}

template <class T>
WeakNullable<T>& WeakNullable<T>::operator=(Null) noexcept
{
	Set(nullptr);
	return *this;
}

template <class T>
Nullable<T>::Nullable(typename Nullable<T>::pointer ptr) noexcept
	: _ptr(ptr)
{}

template <class T>
Nullable<T>::Nullable(WeakNullable<T> const& other) noexcept
	: _ptr(other.Get())
{}

template <class T>
Nullable<T>::Nullable(Null) noexcept
	: _ptr(nullptr)
{}

template <class T>
Nullable<T>::~Nullable()
{
	Set(nullptr);
}

template <class T>
void Nullable<T>::Set(typename Nullable<T>::pointer ptr)
{
	if (_ptr == ptr)
		return;

	if (HasValue())
		delete _ptr;

	_ptr = ptr;
}

template <class T>
void Nullable<T>::Set(Null)
{
	if (HasValue())
	{
		delete _ptr;
		RenounceOwnership();
	}
}

template <class T>
void Nullable<T>::Swap(Nullable<T>& other) noexcept
{
	auto temp = _ptr;
	_ptr = other._ptr;
	other._ptr = temp;
}

template <class T>
Nullable<T>& Nullable<T>::operator=(typename Nullable<T>::pointer ptr)
{
	Set(ptr);
	return *this;
}

template <class T>
Nullable<T>& Nullable<T>::operator=(WeakNullable<T> const& other)
{
	Set(other);
	return *this;
}

template <class T>
Nullable<T>& Nullable<T>::operator=(Null)
{
	Set(nullptr);
	return *this;
}

template <class T>
WeakNullable<T> MakeWeakNullable(typename WeakNullable<T>::pointer ptr) noexcept
{
	return WeakNullable<T>(ptr);
}

template <class T>
WeakNullable<T> MakeWeakNullable(typename WeakNullable<T>::reference value) noexcept
{
	return WeakNullable<T>(value);
}

template <class T>
Nullable<T> MakeNullable(typename Nullable<T>::pointer ptr) noexcept
{
	return Nullable<T>(ptr);
}

END_LFRL_COMMON_NAMESPACE

#endif
