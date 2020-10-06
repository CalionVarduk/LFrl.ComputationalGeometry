#ifndef __LFRL_CG_CORE_VECTOR1_GUARD__
#define __LFRL_CG_CORE_VECTOR1_GUARD__

#include "vector.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct Vector<T, 1>
{
	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetSize() noexcept { return 1; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static Vector<T, 1> Normalize(Vector<T, 1> const& vec) { return Vector<T, 1>(vec).Normalize(); }

	static Vector<T, 1> Negate(Vector<T, 1> const& vec) { return Vector<T, 1>(vec).Negate(); }
	static Vector<T, 1> Incr(Vector<T, 1> const& vec) { return Vector<T, 1>(vec).Incr(); }
	static Vector<T, 1> Decr(Vector<T, 1> const& vec) { return Vector<T, 1>(vec).Decr(); }
	static Vector<T, 1> Add(Vector<T, 1> const& vec, Vector<T, 1> const& vec2) { return Vector<T, 1>(vec).Add(vec2); }
	static Vector<T, 1> Add(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>(vec).Add(scalar); }
	static Vector<T, 1> Add(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>(scalar).Add(vec); }
	static Vector<T, 1> Sub(Vector<T, 1> const& vec, Vector<T, 1> const& vec2) { return Vector<T, 1>(vec).Sub(vec2); }
	static Vector<T, 1> Sub(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>(vec).Sub(scalar); }
	static Vector<T, 1> Sub(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>(scalar).Sub(vec); }
	static Vector<T, 1> Mult(Vector<T, 1> const& vec, Vector<T, 1> const& vec2) { return Vector<T, 1>(vec).Mult(vec2); }
	static Vector<T, 1> Mult(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>(vec).Mult(scalar); }
	static Vector<T, 1> Mult(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>(scalar).Mult(vec); }
	static Vector<T, 1> Div(Vector<T, 1> const& vec, Vector<T, 1> const& vec2) { return Vector<T, 1>(vec).Div(vec2); }
	static Vector<T, 1> Div(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>(vec).Div(scalar); }
	static Vector<T, 1> Div(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>(scalar).Div(vec); }
	static Vector<T, 1> Mod(Vector<T, 1> const& vec, Vector<T, 1> const& vec2) { return Vector<T, 1>(vec).Mod(vec2); }
	static Vector<T, 1> Mod(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>(vec).Mod(scalar); }
	static Vector<T, 1> Mod(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>(scalar).Mod(vec); }

	T x;

	Vector();
	Vector(Vector<T, 1> const& vec) = default;
	Vector(Vector<T, 1>&& vec);
	explicit Vector(LFRL::param<T> value);

	T& GetScalar(u32 index);
	T const& GetScalar(u32 index) const;

	T GetMagnitudeSq() const { return x * x; }
	T GetMagnitude() const { return x; }

	Vector<T, 1>& SetScalar(u32 index, LFRL::param<T> value);

	Vector<T, 1>& Set(Vector<T, 1> const& vec);
	Vector<T, 1>& Set(LFRL::param<T> value);
	Vector<T, 1>& Reset() { return Set(T()); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, 1>& Normalize();

	Vector<T, 1>& Negate();
	Vector<T, 1>& Incr();
	Vector<T, 1>& Decr();
	Vector<T, 1>& Add(Vector<T, 1> const& vec);
	Vector<T, 1>& Add(LFRL::param<T> scalar);
	Vector<T, 1>& Sub(Vector<T, 1> const& vec);
	Vector<T, 1>& Sub(LFRL::param<T> scalar);
	Vector<T, 1>& Mult(Vector<T, 1> const& vec);
	Vector<T, 1>& Mult(LFRL::param<T> scalar);
	Vector<T, 1>& Div(Vector<T, 1> const& vec);
	Vector<T, 1>& Div(LFRL::param<T> scalar);
	Vector<T, 1>& Mod(Vector<T, 1> const& vec);
	Vector<T, 1>& Mod(LFRL::param<T> scalar);
	T Dot(Vector<T, 1> const& vec) const { return x * vec.x; }

	bool Equals(Vector<T, 1> const& vec) const { return x == vec.x; }

	T& operator[](u32 index) { return GetScalar(index); }
	T const& operator[](u32 index) const { return GetScalar(index); }

	Vector<T, 1> operator-() { return Negate(*this); }
	Vector<T, 1>& operator++() { return Incr(); }
	Vector<T, 1>& operator--() { return Decr(); }
	Vector<T, 1> operator++(int);
	Vector<T, 1> operator--(int);

	Vector<T, 1>& operator=(Vector<T, 1> const& vec) = default;
	Vector<T, 1>& operator=(Vector<T, 1>&& vec);
	Vector<T, 1>& operator+=(Vector<T, 1> const& vec) { return Add(vec); }
	Vector<T, 1>& operator+=(LFRL::param<T> scalar) { return Add(scalar); }
	Vector<T, 1>& operator-=(Vector<T, 1> const& vec) { return Sub(vec); }
	Vector<T, 1>& operator-=(LFRL::param<T> scalar) { return Sub(scalar); }
	Vector<T, 1>& operator*=(Vector<T, 1> const& vec) { return Mult(vec); }
	Vector<T, 1>& operator*=(LFRL::param<T> scalar) { return Mult(scalar); }
	Vector<T, 1>& operator/=(Vector<T, 1> const& vec) { return Div(vec); }
	Vector<T, 1>& operator/=(LFRL::param<T> scalar) { return Div(scalar); }
	Vector<T, 1>& operator%=(Vector<T, 1> const& vec) { return Mod(vec); }
	Vector<T, 1>& operator%=(LFRL::param<T> scalar) { return Mod(scalar); }

	bool operator==(Vector<T, 1> const& vec) const { return Equals(vec); }
	bool operator!=(Vector<T, 1> const& vec) const { return !Equals(vec); }
};

template <class T>
Vector<T, 1>::Vector()
	: x()
{}

template <class T>
Vector<T, 1>::Vector(Vector<T, 1>&& vec)
	: x(std::move(vec.x))
{}

template <class T>
Vector<T, 1>::Vector(LFRL::param<T> value)
	: x(value)
{}

template <class T>
T& Vector<T, 1>::GetScalar(u32 index)
{
	assert(index < GetSize());
	return x;
}

template <class T>
T const& Vector<T, 1>::GetScalar(u32 index) const
{
	assert(index < GetSize());
	return x;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::SetScalar(u32 index, LFRL::param<T> value)
{
	assert(index < GetSize());
	x = value;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Set(Vector<T, 1> const& vec)
{
	x = vec.x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Set(LFRL::param<T> value)
{
	x = value;
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, 1>& Vector<T, 1>::Normalize()
{
	x = x == static_cast<T>(0) ? static_cast<T>(0) : static_cast<T>(1);
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Negate()
{
	x = -x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Incr()
{
	++x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Decr()
{
	--x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Add(Vector<T, 1> const& vec)
{
	x += vec.x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Add(LFRL::param<T> scalar)
{
	x += scalar;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Sub(Vector<T, 1> const& vec)
{
	x -= vec.x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Sub(LFRL::param<T> scalar)
{
	x -= scalar;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Mult(Vector<T, 1> const& vec)
{
	x *= vec.x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Mult(LFRL::param<T> scalar)
{
	x *= scalar;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Div(Vector<T, 1> const& vec)
{
	x /= vec.x;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Div(LFRL::param<T> scalar)
{
	x /= scalar;
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Mod(Vector<T, 1> const& vec)
{
	x = LFRL::mod(x, vec.x);
	return *this;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::Mod(LFRL::param<T> scalar)
{
	x = LFRL::mod(x, scalar);
	return *this;
}

template <class T>
Vector<T, 1> Vector<T, 1>::operator++(int)
{
	Vector<T, 1> result(*this);
	Incr();
	return result;
}

template <class T>
Vector<T, 1> Vector<T, 1>::operator--(int)
{
	Vector<T, 1> result(*this);
	Decr();
	return result;
}

template <class T>
Vector<T, 1>& Vector<T, 1>::operator=(Vector<T, 1>&& vec)
{
	if (this != &vec)
		std::swap(x, vec.x);
	return *this;
}

template <class T>
Vector<T, 1> operator+(Vector<T, 1> const& vec1, Vector<T, 1> const& vec2) { return Vector<T, 1>::Add(vec1, vec2); }

template <class T>
Vector<T, 1> operator+(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>::Add(vec, scalar); }

template <class T>
Vector<T, 1> operator+(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>::Add(scalar, vec); }

template <class T>
Vector<T, 1> operator-(Vector<T, 1> const& vec1, Vector<T, 1> const& vec2) { return Vector<T, 1>::Sub(vec1, vec2); }

template <class T>
Vector<T, 1> operator-(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>::Sub(vec, scalar); }

template <class T>
Vector<T, 1> operator-(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>::Sub(scalar, vec); }

template <class T>
Vector<T, 1> operator*(Vector<T, 1> const& vec1, Vector<T, 1> const& vec2) { return Vector<T, 1>::Mult(vec1, vec2); }

template <class T>
Vector<T, 1> operator*(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>::Mult(vec, scalar); }

template <class T>
Vector<T, 1> operator*(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>::Mult(scalar, vec); }

template <class T>
Vector<T, 1> operator/(Vector<T, 1> const& vec1, Vector<T, 1> const& vec2) { return Vector<T, 1>::Div(vec1, vec2); }

template <class T>
Vector<T, 1> operator/(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>::Div(vec, scalar); }

template <class T>
Vector<T, 1> operator/(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>::Div(scalar, vec); }

template <class T>
Vector<T, 1> operator%(Vector<T, 1> const& vec1, Vector<T, 1> const& vec2) { return Vector<T, 1>::Mod(vec1, vec2); }

template <class T>
Vector<T, 1> operator%(Vector<T, 1> const& vec, LFRL::param<T> scalar) { return Vector<T, 1>::Mod(vec, scalar); }

template <class T>
Vector<T, 1> operator%(LFRL::param<T> scalar, Vector<T, 1> const& vec) { return Vector<T, 1>::Mod(scalar, vec); }

END_LFRL_CG_NAMESPACE

#endif
