#ifndef __LFRL_CG_CORE_VECTOR2_GUARD__
#define __LFRL_CG_CORE_VECTOR2_GUARD__

#include "vector1.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct Vector<T, 2>
{
	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetSize() noexcept { return 2; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static Vector<T, 2> Normalize(Vector<T, 2> const& vec) { return Vector<T, 2>(vec).Normalize(); }

	static Vector<T, 2> Negate(Vector<T, 2> const& vec) { return Vector<T, 2>(vec).Negate(); }
	static Vector<T, 2> Incr(Vector<T, 2> const& vec) { return Vector<T, 2>(vec).Incr(); }
	static Vector<T, 2> Decr(Vector<T, 2> const& vec) { return Vector<T, 2>(vec).Decr(); }
	static Vector<T, 2> Add(Vector<T, 2> const& vec, Vector<T, 2> const& vec2) { return Vector<T, 2>(vec).Add(vec2); }
	static Vector<T, 2> Add(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>(vec).Add(scalar); }
	static Vector<T, 2> Add(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>(scalar).Add(vec); }
	static Vector<T, 2> Sub(Vector<T, 2> const& vec, Vector<T, 2> const& vec2) { return Vector<T, 2>(vec).Sub(vec2); }
	static Vector<T, 2> Sub(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>(vec).Sub(scalar); }
	static Vector<T, 2> Sub(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>(scalar).Sub(vec); }
	static Vector<T, 2> Mult(Vector<T, 2> const& vec, Vector<T, 2> const& vec2) { return Vector<T, 2>(vec).Mult(vec2); }
	static Vector<T, 2> Mult(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>(vec).Mult(scalar); }
	static Vector<T, 2> Mult(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>(scalar).Mult(vec); }
	static Vector<T, 2> Div(Vector<T, 2> const& vec, Vector<T, 2> const& vec2) { return Vector<T, 2>(vec).Div(vec2); }
	static Vector<T, 2> Div(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>(vec).Div(scalar); }
	static Vector<T, 2> Div(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>(scalar).Div(vec); }
	static Vector<T, 2> Mod(Vector<T, 2> const& vec, Vector<T, 2> const& vec2) { return Vector<T, 2>(vec).Mod(vec2); }
	static Vector<T, 2> Mod(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>(vec).Mod(scalar); }
	static Vector<T, 2> Mod(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>(scalar).Mod(vec); }

	static Vector<T, 2> Add(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>(vec).Add(vec1); }
	static Vector<T, 2> Add(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>(vec1).Add(vec); }
	static Vector<T, 2> Sub(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>(vec).Sub(vec1); }
	static Vector<T, 2> Sub(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>(vec1).Sub(vec); }
	static Vector<T, 2> Mult(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>(vec).Mult(vec1); }
	static Vector<T, 2> Mult(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>(vec1).Mult(vec); }
	static Vector<T, 2> Div(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>(vec).Div(vec1); }
	static Vector<T, 2> Div(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>(vec1).Div(vec); }
	static Vector<T, 2> Mod(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>(vec).Mod(vec1); }
	static Vector<T, 2> Mod(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>(vec1).Mod(vec); }

	T x;
	T y;

	Vector();
	Vector(Vector<T, 2> const& vec) = default;
	Vector(Vector<T, 2>&& vec);
	explicit Vector(LFRL::param<T> value);
	explicit Vector(Vector<T, 1> const& vec);
	Vector(LFRL::param<T> x, LFRL::param<T> y);
	Vector(Vector<T, 1> const& vec, LFRL::param<T> y);

	T& GetScalar(u32 index);
	T const& GetScalar(u32 index) const;

	T GetMagnitudeSq() const { return x * x + y * y; }
	T GetMagnitude() const { return LFRL::sqrt(GetMagnitudeSq()); }

	Vector<T, 2>& SetScalar(u32 index, LFRL::param<T> value);

	Vector<T, 2>& Set(Vector<T, 2> const& vec);
	Vector<T, 2>& Set(LFRL::param<T> value);
	Vector<T, 2>& Set(LFRL::param<T> x, LFRL::param<T> y);
	Vector<T, 2>& Set(Vector<T, 1> const& vec, LFRL::param<T> y);
	Vector<T, 2>& Reset() { return Set(T()); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	Vector<T, 2>& Normalize();

	Vector<T, 2>& Negate();
	Vector<T, 2>& Incr();
	Vector<T, 2>& Decr();
	Vector<T, 2>& Add(Vector<T, 2> const& vec);
	Vector<T, 2>& Add(LFRL::param<T> scalar);
	Vector<T, 2>& Sub(Vector<T, 2> const& vec);
	Vector<T, 2>& Sub(LFRL::param<T> scalar);
	Vector<T, 2>& Mult(Vector<T, 2> const& vec);
	Vector<T, 2>& Mult(LFRL::param<T> scalar);
	Vector<T, 2>& Div(Vector<T, 2> const& vec);
	Vector<T, 2>& Div(LFRL::param<T> scalar);
	Vector<T, 2>& Mod(Vector<T, 2> const& vec);
	Vector<T, 2>& Mod(LFRL::param<T> scalar);
	T Dot(Vector<T, 2> const& vec) const { return x * vec.x + y * vec.y; }

	Vector<T, 2>& Set(Vector<T, 1> const& vec);
	Vector<T, 2>& Add(Vector<T, 1> const& vec);
	Vector<T, 2>& Sub(Vector<T, 1> const& vec);
	Vector<T, 2>& Mult(Vector<T, 1> const& vec);
	Vector<T, 2>& Div(Vector<T, 1> const& vec);
	Vector<T, 2>& Mod(Vector<T, 1> const& vec);
	T Dot(Vector<T, 1> const& vec) const { return x * vec.x; }

	bool Equals(Vector<T, 2> const& vec) const { return x == vec.x && y == vec.y; }

	T& operator[](u32 index) { return GetScalar(index); }
	T const& operator[](u32 index) const { return GetScalar(index); }

	Vector<T, 2> operator-() { return Negate(*this); }
	Vector<T, 2>& operator++() { return Incr(); }
	Vector<T, 2>& operator--() { return Decr(); }
	Vector<T, 2> operator++(int);
	Vector<T, 2> operator--(int);

	Vector<T, 2>& operator=(Vector<T, 2> const& vec) = default;
	Vector<T, 2>& operator=(Vector<T, 2>&& vec);
	Vector<T, 2>& operator+=(Vector<T, 2> const& vec) { return Add(vec); }
	Vector<T, 2>& operator+=(LFRL::param<T> scalar) { return Add(scalar); }
	Vector<T, 2>& operator-=(Vector<T, 2> const& vec) { return Sub(vec); }
	Vector<T, 2>& operator-=(LFRL::param<T> scalar) { return Sub(scalar); }
	Vector<T, 2>& operator*=(Vector<T, 2> const& vec) { return Mult(vec); }
	Vector<T, 2>& operator*=(LFRL::param<T> scalar) { return Mult(scalar); }
	Vector<T, 2>& operator/=(Vector<T, 2> const& vec) { return Div(vec); }
	Vector<T, 2>& operator/=(LFRL::param<T> scalar) { return Div(scalar); }
	Vector<T, 2>& operator%=(Vector<T, 2> const& vec) { return Mod(vec); }
	Vector<T, 2>& operator%=(LFRL::param<T> scalar) { return Mod(scalar); }

	Vector<T, 2>& operator+=(Vector<T, 1> const& vec) { return Add(vec); }
	Vector<T, 2>& operator-=(Vector<T, 1> const& vec) { return Sub(vec); }
	Vector<T, 2>& operator*=(Vector<T, 1> const& vec) { return Mult(vec); }
	Vector<T, 2>& operator/=(Vector<T, 1> const& vec) { return Div(vec); }
	Vector<T, 2>& operator%=(Vector<T, 1> const& vec) { return Mod(vec); }

	bool operator==(Vector<T, 2> const& vec) const { return Equals(vec); }
	bool operator!=(Vector<T, 2> const& vec) const { return !Equals(vec); }
};

template <class T>
Vector<T, 2>::Vector()
	: x(), y()
{}

template <class T>
Vector<T, 2>::Vector(Vector<T, 2>&& vec)
	: x(std::move(vec.x)), y(std::move(vec.y))
{}

template <class T>
Vector<T, 2>::Vector(LFRL::param<T> value)
	: x(value), y()
{}

template <class T>
Vector<T, 2>::Vector(Vector<T, 1> const& vec)
	: x(vec.x), y()
{}

template <class T>
Vector<T, 2>::Vector(LFRL::param<T> x, LFRL::param<T> y)
	: x(x), y(y)
{}

template <class T>
Vector<T, 2>::Vector(Vector<T, 1> const& vec, LFRL::param<T> y)
	: x(vec.x), y(y)
{}

template <class T>
T& Vector<T, 2>::GetScalar(u32 index)
{
	assert(index < GetSize());
	switch (index)
	{
	case 1:
		return y;
	}
	return x;
}

template <class T>
T const& Vector<T, 2>::GetScalar(u32 index) const
{
	assert(index < GetSize());
	switch (index)
	{
	case 1:
		return y;
	}
	return x;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::SetScalar(u32 index, LFRL::param<T> value)
{
	assert(index < GetSize());
	switch (index)
	{
	case 0:
		x = value;
		break;
	case 1:
		y = value;
		break;
	}
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Set(Vector<T, 2> const& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Set(LFRL::param<T> value)
{
	x = value;
	y = value;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Set(LFRL::param<T> x, LFRL::param<T> y)
{
	x = x;
	y = y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Set(Vector<T, 1> const& vec, LFRL::param<T> y)
{
	x = vec.x;
	y = y;
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
Vector<T, 2>& Vector<T, 2>::Normalize()
{
	auto magnitudeSq = GetMagnitudeSq();
	if (magnitudeSq == static_cast<T>(0))
		Set(static_cast<T>(0));
	else
	{
		auto magnitude = LFRL::sqrt(magnitudeSq);
		x /= magnitude;
		y /= magnitude;
	}
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Negate()
{
	x = -x;
	y = -y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Incr()
{
	++x;
	++y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Decr()
{
	--x;
	--y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Add(Vector<T, 2> const& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Add(LFRL::param<T> scalar)
{
	x += scalar;
	y += scalar;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Sub(Vector<T, 2> const& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Sub(LFRL::param<T> scalar)
{
	x -= scalar;
	y -= scalar;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mult(Vector<T, 2> const& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mult(LFRL::param<T> scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Div(Vector<T, 2> const& vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Div(LFRL::param<T> scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mod(Vector<T, 2> const& vec)
{
	x = LFRL::mod(x, vec.x);
	y = LFRL::mod(y, vec.y);
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mod(LFRL::param<T> scalar)
{
	x = LFRL::mod(x, scalar);
	y = LFRL::mod(y, scalar);
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Set(Vector<T, 1> const& vec)
{
	x = vec.x;
	y = T();
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Add(Vector<T, 1> const& vec)
{
	x += vec.x;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Sub(Vector<T, 1> const& vec)
{
	x -= vec.x;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mult(Vector<T, 1> const& vec)
{
	x *= vec.x;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Div(Vector<T, 1> const& vec)
{
	x /= vec.x;
	return *this;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::Mod(Vector<T, 1> const& vec)
{
	x = LFRL::mod(x, vec.x);
	return *this;
}

template <class T>
Vector<T, 2> Vector<T, 2>::operator++(int)
{
	Vector<T, 2> result(*this);
	Incr();
	return result;
}

template <class T>
Vector<T, 2> Vector<T, 2>::operator--(int)
{
	Vector<T, 2> result(*this);
	Decr();
	return result;
}

template <class T>
Vector<T, 2>& Vector<T, 2>::operator=(Vector<T, 2>&& vec)
{
	if (this != &vec)
	{
		std::swap(x, vec.x);
		std::swap(y, vec.y);
	}
	return *this;
}

template <class T>
Vector<T, 2> operator+(Vector<T, 2> const& vec1, Vector<T, 2> const& vec2) { return Vector<T, 2>::Add(vec1, vec2); }

template <class T>
Vector<T, 2> operator+(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>::Add(vec, scalar); }

template <class T>
Vector<T, 2> operator+(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>::Add(scalar, vec); }

template <class T>
Vector<T, 2> operator-(Vector<T, 2> const& vec1, Vector<T, 2> const& vec2) { return Vector<T, 2>::Sub(vec1, vec2); }

template <class T>
Vector<T, 2> operator-(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>::Sub(vec, scalar); }

template <class T>
Vector<T, 2> operator-(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>::Sub(scalar, vec); }

template <class T>
Vector<T, 2> operator*(Vector<T, 2> const& vec1, Vector<T, 2> const& vec2) { return Vector<T, 2>::Mult(vec1, vec2); }

template <class T>
Vector<T, 2> operator*(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>::Mult(vec, scalar); }

template <class T>
Vector<T, 2> operator*(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>::Mult(scalar, vec); }

template <class T>
Vector<T, 2> operator/(Vector<T, 2> const& vec1, Vector<T, 2> const& vec2) { return Vector<T, 2>::Div(vec1, vec2); }

template <class T>
Vector<T, 2> operator/(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>::Div(vec, scalar); }

template <class T>
Vector<T, 2> operator/(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>::Div(scalar, vec); }

template <class T>
Vector<T, 2> operator%(Vector<T, 2> const& vec1, Vector<T, 2> const& vec2) { return Vector<T, 2>::Mod(vec1, vec2); }

template <class T>
Vector<T, 2> operator%(Vector<T, 2> const& vec, LFRL::param<T> scalar) { return Vector<T, 2>::Mod(vec, scalar); }

template <class T>
Vector<T, 2> operator%(LFRL::param<T> scalar, Vector<T, 2> const& vec) { return Vector<T, 2>::Mod(scalar, vec); }

template <class T>
Vector<T, 2> operator+(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>::Add(vec, vec1); }

template <class T>
Vector<T, 2> operator+(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>::Add(vec1, vec); }

template <class T>
Vector<T, 2> operator-(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>::Sub(vec, vec1); }

template <class T>
Vector<T, 2> operator-(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>::Sub(vec1, vec); }

template <class T>
Vector<T, 2> operator*(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>::Mult(vec, vec1); }

template <class T>
Vector<T, 2> operator*(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>::Mult(vec1, vec); }

template <class T>
Vector<T, 2> operator/(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>::Div(vec, vec1); }

template <class T>
Vector<T, 2> operator/(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>::Div(vec1, vec); }

template <class T>
Vector<T, 2> operator%(Vector<T, 2> const& vec, Vector<T, 1> const& vec1) { return Vector<T, 2>::Mod(vec, vec1); }

template <class T>
Vector<T, 2> operator%(Vector<T, 1> const& vec1, Vector<T, 2> const& vec) { return Vector<T, 2>::Mod(vec1, vec); }

END_LFRL_CG_NAMESPACE

#endif
