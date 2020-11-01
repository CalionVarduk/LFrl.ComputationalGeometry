#ifndef __LFRL_CG_CORE_VECTOR_GUARD__
#define __LFRL_CG_CORE_VECTOR_GUARD__

#include <cassert>
#include "LFrl.Common/src/utils/math.h"
#include "LFrl.Common/src/utils/param.h"
#include "LFrl.Common/src/utils/requires.h"
#include "LFrl.Common/src/utils/typedefs.h"
#include "../internal/namespace_macros.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T, u32 dimensions>
struct Vector
{
	static_assert(dimensions > 0, "Vector<T, dimensions>: dimensions must be greater than 0.");

	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetDimensions() noexcept { return dimensions; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static Vector<T, dimensions> Normalize(Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec).Normalize(); }

	static Vector<T, dimensions> Negate(Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec).Negate(); }
	static Vector<T, dimensions> Incr(Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec).Incr(); }
	static Vector<T, dimensions> Decr(Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec).Decr(); }
	static Vector<T, dimensions> Add(Vector<T, dimensions> const& vec, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>(vec).Add(vec2); }
	static Vector<T, dimensions> Add(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>(vec).Add(scalar); }
	static Vector<T, dimensions> Add(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(scalar).Add(vec); }
	static Vector<T, dimensions> Sub(Vector<T, dimensions> const& vec, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>(vec).Sub(vec2); }
	static Vector<T, dimensions> Sub(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>(vec).Sub(scalar); }
	static Vector<T, dimensions> Sub(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(scalar).Sub(vec); }
	static Vector<T, dimensions> Mult(Vector<T, dimensions> const& vec, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>(vec).Mult(vec2); }
	static Vector<T, dimensions> Mult(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>(vec).Mult(scalar); }
	static Vector<T, dimensions> Mult(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(scalar).Mult(vec); }
	static Vector<T, dimensions> Div(Vector<T, dimensions> const& vec, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>(vec).Div(vec2); }
	static Vector<T, dimensions> Div(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>(vec).Div(scalar); }
	static Vector<T, dimensions> Div(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(scalar).Div(vec); }
	static Vector<T, dimensions> Mod(Vector<T, dimensions> const& vec, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>(vec).Mod(vec2); }
	static Vector<T, dimensions> Mod(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>(vec).Mod(scalar); }
	static Vector<T, dimensions> Mod(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(scalar).Mod(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Add(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>(vec).Add<dim>(vec1); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Add(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec1).Add(vec); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Sub(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>(vec).Sub<dim>(vec1); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Sub(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec1).Sub(vec); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Mult(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>(vec).Mult<dim>(vec1); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Mult(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec1).Mult(vec); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Div(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>(vec).Div<dim>(vec1); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Div(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec1).Div(vec); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Mod(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>(vec).Mod<dim>(vec1); }
	
	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static Vector<T, dimensions> Mod(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>(vec1).Mod(vec); }

	Vector();
	Vector(Vector<T, dimensions> const& vec) = default;
	Vector(Vector<T, dimensions>&& vec);
	explicit Vector(LFRL::param<T> value);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	explicit Vector(Vector<T, dim> const& vec);

	T& GetScalar(u32 index);
	T const& GetScalar(u32 index) const;

	T GetMagnitudeSq() const;
	T GetMagnitude() const { return LFRL::sqrt(GetMagnitudeSq()); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, dimensions>& SetMagnitudeSq(LFRL::param<T> value);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, dimensions>& SetMagnitude(LFRL::param<T> value);

	Vector<T, dimensions>& SetScalar(u32 index, LFRL::param<T> value);

	Vector<T, dimensions>& Set(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Set(LFRL::param<T> value);
	Vector<T, dimensions>& Reset() { return Set(T()); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Set(Vector<T, dim> const& vec);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, dimensions>& Normalize();

	Vector<T, dimensions>& Negate();
	Vector<T, dimensions>& Incr();
	Vector<T, dimensions>& Decr();
	Vector<T, dimensions>& Add(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Add(LFRL::param<T> scalar);
	Vector<T, dimensions>& Sub(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Sub(LFRL::param<T> scalar);
	Vector<T, dimensions>& Mult(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Mult(LFRL::param<T> scalar);
	Vector<T, dimensions>& Div(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Div(LFRL::param<T> scalar);
	Vector<T, dimensions>& Mod(Vector<T, dimensions> const& vec);
	Vector<T, dimensions>& Mod(LFRL::param<T> scalar);
	T Dot(Vector<T, dimensions> const& vec) const;

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Add(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Sub(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Mult(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Div(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& Mod(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	T Dot(Vector<T, dim> const& vec) const;

	bool Equals(Vector<T, dimensions> const& vec) const;

	T& operator[](u32 index) { return GetScalar(index); }
	T const& operator[](u32 index) const { return GetScalar(index); }

	Vector<T, dimensions> operator-() { return Negate(*this); }
	Vector<T, dimensions>& operator++() { return Incr(); }
	Vector<T, dimensions>& operator--() { return Decr(); }
	Vector<T, dimensions> operator++(int);
	Vector<T, dimensions> operator--(int);

	Vector<T, dimensions>& operator=(Vector<T, dimensions> const& vec) = default;
	Vector<T, dimensions>& operator=(Vector<T, dimensions>&& vec);
	Vector<T, dimensions>& operator+=(Vector<T, dimensions> const& vec) { return Add(vec); }
	Vector<T, dimensions>& operator+=(LFRL::param<T> scalar) { return Add(scalar); }
	Vector<T, dimensions>& operator-=(Vector<T, dimensions> const& vec) { return Sub(vec); }
	Vector<T, dimensions>& operator-=(LFRL::param<T> scalar) { return Sub(scalar); }
	Vector<T, dimensions>& operator*=(Vector<T, dimensions> const& vec) { return Mult(vec); }
	Vector<T, dimensions>& operator*=(LFRL::param<T> scalar) { return Mult(scalar); }
	Vector<T, dimensions>& operator/=(Vector<T, dimensions> const& vec) { return Div(vec); }
	Vector<T, dimensions>& operator/=(LFRL::param<T> scalar) { return Div(scalar); }
	Vector<T, dimensions>& operator%=(Vector<T, dimensions> const& vec) { return Mod(vec); }
	Vector<T, dimensions>& operator%=(LFRL::param<T> scalar) { return Mod(scalar); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& operator+=(Vector<T, dim> const& vec) { return Add<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& operator-=(Vector<T, dim> const& vec) { return Sub<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& operator*=(Vector<T, dim> const& vec) { return Mult<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& operator/=(Vector<T, dim> const& vec) { return Div<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	Vector<T, dimensions>& operator%=(Vector<T, dim> const& vec) { return Mod<dim>(vec); }

	bool operator==(Vector<T, dimensions> const& vec) const { return Equals(vec); }
	bool operator!=(Vector<T, dimensions> const& vec) const { return !Equals(vec); }

private:
	T _scalars[dimensions];
};

template <class T, u32 dimensions>
Vector<T, dimensions>::Vector()
	: _scalars()
{
	Reset();
}

template <class T, u32 dimensions>
Vector<T, dimensions>::Vector(Vector<T, dimensions>&& vec)
	: _scalars()
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = std::move(vec._scalars[i]);
}

template <class T, u32 dimensions>
Vector<T, dimensions>::Vector(LFRL::param<T> value)
	: _scalars()
{
	Set(value);
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>::Vector(Vector<T, dim> const& vec)
	: _scalars()
{
	Set<dim>(vec);
}

template <class T, u32 dimensions>
T& Vector<T, dimensions>::GetScalar(u32 index)
{
	assert(index < GetDimensions());
	return _scalars[index];
}

template <class T, u32 dimensions>
T const& Vector<T, dimensions>::GetScalar(u32 index) const
{
	assert(index < GetDimensions());
	return _scalars[index];
}

template <class T, u32 dimensions>
T Vector<T, dimensions>::GetMagnitudeSq() const
{
	T result = _scalars[0] * _scalars[0];
	for (u32 i = 1; i < dimensions; ++i)
		result += _scalars[i] * _scalars[i];
	return result;
}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, dimensions>& Vector<T, dimensions>::SetMagnitudeSq(LFRL::param<T> value)
{
	if (value <= static_cast<T>(0))
	{
		for (u32 i = 0; i < dimensions; ++i)
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
			for (u32 i = 0; i < dimensions; ++i)
				_scalars[i] *= scale;
		}
	}
	return *this;
}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, dimensions>& Vector<T, dimensions>::SetMagnitude(LFRL::param<T> value)
{
	if (value <= static_cast<T>(0))
	{
		for (u32 i = 0; i < dimensions; ++i)
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
			for (u32 i = 0; i < dimensions; ++i)
				_scalars[i] *= scale;
		}
	}
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::SetScalar(u32 index, LFRL::param<T> value)
{
	_scalars[index] = value;
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Set(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = vec._scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Set(LFRL::param<T> value)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = value;
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
	Vector<T, dimensions>& Vector<T, dimensions>::Set(Vector<T, dim> const& vec)
	{
		for (u32 i = 0; i < dim; ++i)
			_scalars[i] = vec[i];
		for (u32 i = dim; i < dimensions; ++i)
			_scalars[i] = T();
		return *this;
	}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, dimensions>& Vector<T, dimensions>::Normalize()
{
	auto magnitudeSq = GetMagnitudeSq();
	if (magnitudeSq == static_cast<T>(0))
		Set(static_cast<T>(0));
	else
	{
		auto magnitude = LFRL::sqrt(magnitudeSq);
		for (u32 i = 0; i < dimensions; ++i)
			_scalars[i] /= magnitude;
	}
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Negate()
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = -_scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Incr()
{
	for (u32 i = 0; i < dimensions; ++i)
		++_scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Decr()
{
	for (u32 i = 0; i < dimensions; ++i)
		--_scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Add(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] += vec._scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Add(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] += scalar;
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Sub(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] -= vec._scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Sub(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] -= scalar;
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Mult(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] *= vec._scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Mult(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] *= scalar;
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Div(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] /= vec._scalars[i];
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Div(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] /= scalar;
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Mod(Vector<T, dimensions> const& vec)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], vec._scalars[i]);
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::Mod(LFRL::param<T> scalar)
{
	for (u32 i = 0; i < dimensions; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], scalar);
	return *this;
}

template <class T, u32 dimensions>
T Vector<T, dimensions>::Dot(Vector<T, dimensions> const& vec) const
{
	auto result = _scalars[0] * vec._scalars[0];
	for (u32 i = 1; i < dimensions; ++i)
		result += _scalars[i] * vec._scalars[i];
	return result;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>& Vector<T, dimensions>::Add(Vector<T, dim> const& vec)
{
	for (u32 i = 0; i < dim; ++i)
		_scalars[i] += vec[i];
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>& Vector<T, dimensions>::Sub(Vector<T, dim> const& vec)
{
	for (u32 i = 0; i < dim; ++i)
		_scalars[i] -= vec[i];
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>& Vector<T, dimensions>::Mult(Vector<T, dim> const& vec)
{
	for (u32 i = 0; i < dim; ++i)
		_scalars[i] *= vec[i];
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>& Vector<T, dimensions>::Div(Vector<T, dim> const& vec)
{
	for (u32 i = 0; i < dim; ++i)
		_scalars[i] /= vec[i];
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
Vector<T, dimensions>& Vector<T, dimensions>::Mod(Vector<T, dim> const& vec)
{
	for (u32 i = 0; i < dim; ++i)
		_scalars[i] = LFRL::mod(_scalars[i], vec[i]);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
T Vector<T, dimensions>::Dot(Vector<T, dim> const& vec) const
{
	auto result = _scalars[0] * vec[0];
	for (u32 i = 1; i < dim; ++i)
		result += _scalars[i] * vec[i];
	return result;
}

template <class T, u32 dimensions>
bool Vector<T, dimensions>::Equals(Vector<T, dimensions> const& vec) const
{
	for (u32 i = 0; i < dimensions; ++i)
		if (_scalars[i] != vec._scalars[i])
			return false;
	return true;
}

template <class T, u32 dimensions>
Vector<T, dimensions> Vector<T, dimensions>::operator++(int)
{
	Vector<T, dimensions> result(*this);
	Incr();
	return result;
}

template <class T, u32 dimensions>
Vector<T, dimensions> Vector<T, dimensions>::operator--(int)
{
	Vector<T, dimensions> result(*this);
	Decr();
	return result;
}

template <class T, u32 dimensions>
Vector<T, dimensions>& Vector<T, dimensions>::operator=(Vector<T, dimensions>&& vec)
{
	if (this != &vec)
		for (u32 i = 0; i < dimensions; ++i)
			_scalars[i] = std::move(vec._scalars[i]);
	return *this;
}

template <class T, u32 dimensions>
Vector<T, dimensions> operator+(Vector<T, dimensions> const& vec1, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>::Add(vec1, vec2); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator+(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>::Add(vec, scalar); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator+(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Add(scalar, vec); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator-(Vector<T, dimensions> const& vec1, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>::Sub(vec1, vec2); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator-(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>::Sub(vec, scalar); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator-(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Sub(scalar, vec); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator*(Vector<T, dimensions> const& vec1, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>::Mult(vec1, vec2); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator*(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>::Mult(vec, scalar); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator*(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Mult(scalar, vec); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator/(Vector<T, dimensions> const& vec1, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>::Div(vec1, vec2); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator/(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>::Div(vec, scalar); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator/(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Div(scalar, vec); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator%(Vector<T, dimensions> const& vec1, Vector<T, dimensions> const& vec2) { return Vector<T, dimensions>::Mod(vec1, vec2); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator%(Vector<T, dimensions> const& vec, LFRL::param<T> scalar) { return Vector<T, dimensions>::Mod(vec, scalar); }

template <class T, u32 dimensions>
Vector<T, dimensions> operator%(LFRL::param<T> scalar, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Mod(scalar, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator+(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>::Add<dim>(vec, vec1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator+(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Add<dim>(vec1, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator-(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>::Sub<dim>(vec, vec1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator-(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Sub<dim>(vec1, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator*(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>::Mult<dim>(vec, vec1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator*(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Mult<dim>(vec1, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator/(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>::Div<dim>(vec, vec1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator/(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Div<dim>(vec1, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator%(Vector<T, dimensions> const& vec, Vector<T, dim> const& vec1) { return Vector<T, dimensions>::Mod<dim>(vec, vec1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
Vector<T, dimensions> operator%(Vector<T, dim> const& vec1, Vector<T, dimensions> const& vec) { return Vector<T, dimensions>::Mod<dim>(vec1, vec); }

END_LFRL_CG_NAMESPACE

#endif
