#ifndef __LFRL_CG_CORE_VECTOR_GUARD__
#define __LFRL_CG_CORE_VECTOR_GUARD__

#include <cassert>
#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/math.h"
#include "LFrl.Common/src/utils/param.h"
#include "LFrl.Common/src/utils/requires.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T, u32 size>
struct Vector
{
	static_assert(size > 0, "Vector<T, size>: size must be greater than 0.");

	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetSize() noexcept { return size; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static Vector<T, size> Normalize(Vector<T, size> const& vec) { return Vector<T, size>(vec).Normalize(); }

	static Vector<T, size> Negate(Vector<T, size> const& vec) { return Vector<T, size>(vec).Negate(); }
	static Vector<T, size> Incr(Vector<T, size> const& vec) { return Vector<T, size>(vec).Incr(); }
	static Vector<T, size> Decr(Vector<T, size> const& vec) { return Vector<T, size>(vec).Decr(); }
	static Vector<T, size> Add(Vector<T, size> const& vec, Vector<T, size> const& vec2) { return Vector<T, size>(vec).Add(vec2); }
	static Vector<T, size> Add(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>(vec).Add(scalar); }
	static Vector<T, size> Add(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>(scalar).Add(vec); }
	static Vector<T, size> Sub(Vector<T, size> const& vec, Vector<T, size> const& vec2) { return Vector<T, size>(vec).Sub(vec2); }
	static Vector<T, size> Sub(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>(vec).Sub(scalar); }
	static Vector<T, size> Sub(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>(scalar).Sub(vec); }
	static Vector<T, size> Mult(Vector<T, size> const& vec, Vector<T, size> const& vec2) { return Vector<T, size>(vec).Mult(vec2); }
	static Vector<T, size> Mult(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>(vec).Mult(scalar); }
	static Vector<T, size> Mult(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>(scalar).Mult(vec); }
	static Vector<T, size> Div(Vector<T, size> const& vec, Vector<T, size> const& vec2) { return Vector<T, size>(vec).Div(vec2); }
	static Vector<T, size> Div(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>(vec).Div(scalar); }
	static Vector<T, size> Div(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>(scalar).Div(vec); }
	static Vector<T, size> Mod(Vector<T, size> const& vec, Vector<T, size> const& vec2) { return Vector<T, size>(vec).Mod(vec2); }
	static Vector<T, size> Mod(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>(vec).Mod(scalar); }
	static Vector<T, size> Mod(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>(scalar).Mod(vec); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Add(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>(vec).Add<sz>(vec1); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Add(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>(vec1).Add(vec); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Sub(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>(vec).Sub<sz>(vec1); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Sub(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>(vec1).Sub(vec); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Mult(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>(vec).Mult<sz>(vec1); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Mult(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>(vec1).Mult(vec); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Div(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>(vec).Div<sz>(vec1); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Div(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>(vec1).Div(vec); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Mod(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>(vec).Mod<sz>(vec1); }
	
	template <u32 sz, LFRL::requires<sz < size> = 0>
	static Vector<T, size> Mod(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>(vec1).Mod(vec); }

	Vector();
	Vector(Vector<T, size> const& vec) = default;
	Vector(Vector<T, size>&& vec);
	explicit Vector(LFRL::param<T> value);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	explicit Vector(Vector<T, sz> const& vec);

	T& GetScalar(u32 index);
	T const& GetScalar(u32 index) const;

	T GetMagnitudeSq() const;
	T GetMagnitude() const { return LFRL::sqrt(GetMagnitudeSq()); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, size>& SetMagnitudeSq(LFRL::param<T> value);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, size>& SetMagnitude(LFRL::param<T> value);

	Vector<T, size>& SetScalar(u32 index, LFRL::param<T> value);

	Vector<T, size>& Set(Vector<T, size> const& vec);
	Vector<T, size>& Set(LFRL::param<T> value);
	Vector<T, size>& Reset() { return Set(T()); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Set(Vector<T, sz> const& vec);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, size>& Normalize();

	Vector<T, size>& Negate();
	Vector<T, size>& Incr();
	Vector<T, size>& Decr();
	Vector<T, size>& Add(Vector<T, size> const& vec);
	Vector<T, size>& Add(LFRL::param<T> scalar);
	Vector<T, size>& Sub(Vector<T, size> const& vec);
	Vector<T, size>& Sub(LFRL::param<T> scalar);
	Vector<T, size>& Mult(Vector<T, size> const& vec);
	Vector<T, size>& Mult(LFRL::param<T> scalar);
	Vector<T, size>& Div(Vector<T, size> const& vec);
	Vector<T, size>& Div(LFRL::param<T> scalar);
	Vector<T, size>& Mod(Vector<T, size> const& vec);
	Vector<T, size>& Mod(LFRL::param<T> scalar);
	T Dot(Vector<T, size> const& vec) const;

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Add(Vector<T, sz> const& vec);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Sub(Vector<T, sz> const& vec);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Mult(Vector<T, sz> const& vec);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Div(Vector<T, sz> const& vec);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& Mod(Vector<T, sz> const& vec);

	template <u32 sz, LFRL::requires<sz < size> = 0>
	T Dot(Vector<T, sz> const& vec) const;

	bool Equals(Vector<T, size> const& vec) const;

	T& operator[](u32 index) { return GetScalar(index); }
	T const& operator[](u32 index) const { return GetScalar(index); }

	Vector<T, size> operator-() { return Negate(*this); }
	Vector<T, size>& operator++() { return Incr(); }
	Vector<T, size>& operator--() { return Decr(); }
	Vector<T, size> operator++(int);
	Vector<T, size> operator--(int);

	Vector<T, size>& operator=(Vector<T, size> const& vec) = default;
	Vector<T, size>& operator=(Vector<T, size>&& vec);
	Vector<T, size>& operator+=(Vector<T, size> const& vec) { return Add(vec); }
	Vector<T, size>& operator+=(LFRL::param<T> scalar) { return Add(scalar); }
	Vector<T, size>& operator-=(Vector<T, size> const& vec) { return Sub(vec); }
	Vector<T, size>& operator-=(LFRL::param<T> scalar) { return Sub(scalar); }
	Vector<T, size>& operator*=(Vector<T, size> const& vec) { return Mult(vec); }
	Vector<T, size>& operator*=(LFRL::param<T> scalar) { return Mult(scalar); }
	Vector<T, size>& operator/=(Vector<T, size> const& vec) { return Div(vec); }
	Vector<T, size>& operator/=(LFRL::param<T> scalar) { return Div(scalar); }
	Vector<T, size>& operator%=(Vector<T, size> const& vec) { return Mod(vec); }
	Vector<T, size>& operator%=(LFRL::param<T> scalar) { return Mod(scalar); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& operator+=(Vector<T, sz> const& vec) { return Add<sz>(vec); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& operator-=(Vector<T, sz> const& vec) { return Sub<sz>(vec); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& operator*=(Vector<T, sz> const& vec) { return Mult<sz>(vec); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& operator/=(Vector<T, sz> const& vec) { return Div<sz>(vec); }

	template <u32 sz, LFRL::requires<sz < size> = 0>
	Vector<T, size>& operator%=(Vector<T, sz> const& vec) { return Mod<sz>(vec); }

	bool operator==(Vector<T, size> const& vec) const { return Equals(vec); }
	bool operator!=(Vector<T, size> const& vec) const { return !Equals(vec); }

private:
	T _scalars[size];
};

template <class T, u32 size>
Vector<T, size>::Vector()
	: _scalars()
{
	Reset();
}

template <class T, u32 size>
Vector<T, size>::Vector(Vector<T, size>&& vec)
	: _scalars()
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = std::move(vec._scalars[i]);
}

template <class T, u32 size>
Vector<T, size>::Vector(LFRL::param<T> value)
	: _scalars()
{
	Set(value);
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>::Vector(Vector<T, sz> const& vec)
	: _scalars()
{
	Set<sz>(vec);
}

template <class T, u32 size>
T& Vector<T, size>::GetScalar(u32 index)
{
	assert(index < GetSize());
	return _scalars[index];
}

template <class T, u32 size>
T const& Vector<T, size>::GetScalar(u32 index) const
{
	assert(index < GetSize());
	return _scalars[index];
}

template <class T, u32 size>
T Vector<T, size>::GetMagnitudeSq() const
{
	T result = _scalars[0] * _scalars[0];
	for (u32 i = 1; i < size; ++i)
		result += _scalars[i] * _scalars[i];
	return result;
}

template <class T, u32 size> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, size>& Vector<T, size>::SetMagnitudeSq(LFRL::param<T> value)
{
	if (value <= static_cast<T>(0))
	{
		for (u32 i = 0; i < size; ++i)
			_scalars[i] = static_cast<T>(0);
	}
	else
	{
		auto magnitudeSq = GetMagnitudeSq();
		if (magnitudeSq == static_cast<T>(0))
			_scalars[0] = LFRL::sqrt(value);
		else
		{
			auto scale = value / magnitudeSq;
			for (u32 i = 0; i < size; ++i)
				_scalars[i] *= scale;
		}
	}
	return *this;
}

template <class T, u32 size> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, size>& Vector<T, size>::SetMagnitude(LFRL::param<T> value)
{
	if (value <= static_cast<T>(0))
	{
		for (u32 i = 0; i < size; ++i)
			_scalars[i] = static_cast<T>(0);
	}
	else
	{
		auto magnitudeSq = GetMagnitudeSq();
		if (magnitudeSq == static_cast<T>(0))
			_scalars[0] = value;
		else
		{
			auto scale = value / LFRL::sqrt(magnitudeSq);
			for (u32 i = 0; i < size; ++i)
				_scalars[i] *= scale;
		}
	}
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::SetScalar(u32 index, LFRL::param<T> value)
{
	_scalars[index] = value;
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Set(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = vec._scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Set(LFRL::param<T> value)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = value;
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
	Vector<T, size>& Vector<T, size>::Set(Vector<T, sz> const& vec)
	{
		for (u32 i = 0; i < sz; ++i)
			_scalars[i] = vec[i];
		for (u32 i = sz; i < size; ++i)
			_scalars[i] = T();
		return *this;
	}

template <class T, u32 size> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, size>& Vector<T, size>::Normalize()
{
	auto magnitudeSq = GetMagnitudeSq();
	if (magnitudeSq == static_cast<T>(0))
		Set(static_cast<T>(0));
	else
	{
		auto magnitude = LFRL::sqrt(magnitudeSq);
		for (u32 i = 0; i < size; ++i)
			_scalars[i] /= magnitude;
	}
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Negate()
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = -_scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Incr()
{
	for (u32 i = 0; i < size; ++i)
		++_scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Decr()
{
	for (u32 i = 0; i < size; ++i)
		--_scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Add(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] += vec._scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Add(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] += scalar;
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Sub(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] -= vec._scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Sub(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] -= scalar;
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Mult(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] *= vec._scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Mult(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] *= scalar;
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Div(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] /= vec._scalars[i];
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Div(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] /= scalar;
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Mod(Vector<T, size> const& vec)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], vec._scalars[i]);
	return *this;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::Mod(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < size; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], scalar);
	return *this;
}

template <class T, u32 size>
T Vector<T, size>::Dot(Vector<T, size> const& vec) const
{
	auto result = _scalars[0] * vec._scalars[0];
	for (u32 i = 1; i < size; ++i)
		result += _scalars[i] * vec._scalars[i];
	return result;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>& Vector<T, size>::Add(Vector<T, sz> const& vec)
{
	for (u32 i = 0; i < sz; ++i)
		_scalars[i] += vec[i];
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>& Vector<T, size>::Sub(Vector<T, sz> const& vec)
{
	for (u32 i = 0; i < sz; ++i)
		_scalars[i] -= vec[i];
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>& Vector<T, size>::Mult(Vector<T, sz> const& vec)
{
	for (u32 i = 0; i < sz; ++i)
		_scalars[i] *= vec[i];
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>& Vector<T, size>::Div(Vector<T, sz> const& vec)
{
	for (u32 i = 0; i < sz; ++i)
		_scalars[i] /= vec[i];
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
Vector<T, size>& Vector<T, size>::Mod(Vector<T, sz> const& vec)
{
	for (u32 i = 0; i < sz; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], vec[i]);
	return *this;
}

template <class T, u32 size> template <u32 sz, LFRL::requires<sz < size>>
T Vector<T, size>::Dot(Vector<T, sz> const& vec) const
{
	auto result = _scalars[0] * vec[0];
	for (u32 i = 1; i < sz; ++i)
		result += _scalars[i] * vec[i];
	return result;
}

template <class T, u32 size>
bool Vector<T, size>::Equals(Vector<T, size> const& vec) const
{
	for (u32 i = 0; i < size; ++i)
		if (_scalars[i] != vec._scalars[i])
			return false;
	return true;
}

template <class T, u32 size>
Vector<T, size> Vector<T, size>::operator++(int)
{
	Vector<T, size> result(*this);
	Incr();
	return result;
}

template <class T, u32 size>
Vector<T, size> Vector<T, size>::operator--(int)
{
	Vector<T, size> result(*this);
	Decr();
	return result;
}

template <class T, u32 size>
Vector<T, size>& Vector<T, size>::operator=(Vector<T, size>&& vec)
{
	if (this != &vec)
		for (u32 i = 0; i < size; ++i)
			_scalars[i] = std::move(vec._scalars[i]);
	return *this;
}

template <class T, u32 size>
Vector<T, size> operator+(Vector<T, size> const& vec1, Vector<T, size> const& vec2) { return Vector<T, size>::Add(vec1, vec2); }

template <class T, u32 size>
Vector<T, size> operator+(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>::Add(vec, scalar); }

template <class T, u32 size>
Vector<T, size> operator+(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>::Add(scalar, vec); }

template <class T, u32 size>
Vector<T, size> operator-(Vector<T, size> const& vec1, Vector<T, size> const& vec2) { return Vector<T, size>::Sub(vec1, vec2); }

template <class T, u32 size>
Vector<T, size> operator-(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>::Sub(vec, scalar); }

template <class T, u32 size>
Vector<T, size> operator-(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>::Sub(scalar, vec); }

template <class T, u32 size>
Vector<T, size> operator*(Vector<T, size> const& vec1, Vector<T, size> const& vec2) { return Vector<T, size>::Mult(vec1, vec2); }

template <class T, u32 size>
Vector<T, size> operator*(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>::Mult(vec, scalar); }

template <class T, u32 size>
Vector<T, size> operator*(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>::Mult(scalar, vec); }

template <class T, u32 size>
Vector<T, size> operator/(Vector<T, size> const& vec1, Vector<T, size> const& vec2) { return Vector<T, size>::Div(vec1, vec2); }

template <class T, u32 size>
Vector<T, size> operator/(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>::Div(vec, scalar); }

template <class T, u32 size>
Vector<T, size> operator/(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>::Div(scalar, vec); }

template <class T, u32 size>
Vector<T, size> operator%(Vector<T, size> const& vec1, Vector<T, size> const& vec2) { return Vector<T, size>::Mod(vec1, vec2); }

template <class T, u32 size>
Vector<T, size> operator%(Vector<T, size> const& vec, LFRL::param<T> scalar) { return Vector<T, size>::Mod(vec, scalar); }

template <class T, u32 size>
Vector<T, size> operator%(LFRL::param<T> scalar, Vector<T, size> const& vec) { return Vector<T, size>::Mod(scalar, vec); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator+(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>::Add<sz>(vec, vec1); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator+(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>::Add<sz>(vec1, vec); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator-(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>::Sub<sz>(vec, vec1); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator-(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>::Sub<sz>(vec1, vec); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator*(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>::Mult<sz>(vec, vec1); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator*(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>::Mult<sz>(vec1, vec); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator/(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>::Div<sz>(vec, vec1); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator/(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>::Div<sz>(vec1, vec); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator%(Vector<T, size> const& vec, Vector<T, sz> const& vec1) { return Vector<T, size>::Mod<sz>(vec, vec1); }

template <class T, u32 size, u32 sz, LFRL::requires<sz < size> = 0>
Vector<T, size> operator%(Vector<T, sz> const& vec1, Vector<T, size> const& vec) { return Vector<T, size>::Mod<sz>(vec1, vec); }

END_LFRL_CG_NAMESPACE

#endif
