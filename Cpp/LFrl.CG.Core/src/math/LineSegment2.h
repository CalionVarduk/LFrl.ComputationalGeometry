#ifndef __LFRL_CG_CORE_LINE_SEGMENT2_GUARD__
#define __LFRL_CG_CORE_LINE_SEGMENT2_GUARD__

#include "LineSegment1.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct LineSegment<T, 2>
{
	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetDimensions() noexcept { return 2; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static LineSegment<T, 2> Normalize(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).Normalize(); }

	static LineSegment<T, 2> Negate(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).Negate(); }
	static LineSegment<T, 2> Incr(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).Incr(); }
	static LineSegment<T, 2> Decr(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).Decr(); }
	static LineSegment<T, 2> Add(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>(seg).Add(seg2); }
	static LineSegment<T, 2> Sub(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>(seg).Sub(seg2); }
	static LineSegment<T, 2> Mult(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>(seg).Mult(seg2); }
	static LineSegment<T, 2> Div(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>(seg).Div(seg2); }
	static LineSegment<T, 2> Mod(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>(seg).Mod(seg2); }

	static LineSegment<T, 2> Add(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>(seg).Add(vec); }
	static LineSegment<T, 2> Sub(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>(seg).Sub(vec); }
	static LineSegment<T, 2> Mult(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>(seg).Mult(vec); }
	static LineSegment<T, 2> Div(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>(seg).Div(vec); }
	static LineSegment<T, 2> Mod(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>(seg).Mod(vec); }

	static LineSegment<T, 2> Add(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>(seg).Add(seg1); }
	static LineSegment<T, 2> Add(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg1).Add(seg); }
	static LineSegment<T, 2> Sub(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>(seg).Sub(seg1); }
	static LineSegment<T, 2> Sub(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg1).Sub(seg); }
	static LineSegment<T, 2> Mult(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>(seg).Mult(seg1); }
	static LineSegment<T, 2> Mult(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg1).Mult(seg); }
	static LineSegment<T, 2> Div(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>(seg).Div(seg1); }
	static LineSegment<T, 2> Div(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg1).Div(seg); }
	static LineSegment<T, 2> Mod(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>(seg).Mod(seg1); }
	static LineSegment<T, 2> Mod(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg1).Mod(seg); }

	static LineSegment<T, 2> Add(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>(seg).Add(vec); }
	static LineSegment<T, 2> Sub(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>(seg).Sub(vec); }
	static LineSegment<T, 2> Mult(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>(seg).Mult(vec); }
	static LineSegment<T, 2> Div(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>(seg).Div(vec); }
	static LineSegment<T, 2> Mod(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>(seg).Mod(vec); }

	static LineSegment<T, 2> RotateCw(LineSegment<T, 2> const& seg, LFRL::param<T> radians) { return LineSegment<T, 2>(seg).RotateCw(radians); }
	static LineSegment<T, 2> RotateCcw(LineSegment<T, 2> const& seg, LFRL::param<T> radians) { return LineSegment<T, 2>(seg).RotateCcw(radians); }
	static LineSegment<T, 2> RotateCwHalfPi(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).RotateCwHalfPi(); }
	static LineSegment<T, 2> RotateCcwHalfPi(LineSegment<T, 2> const& seg) { return LineSegment<T, 2>(seg).RotateCcwHalfPi(); }

	Vector<T, 2> start;
	Vector<T, 2> end;

	LineSegment();
	LineSegment(LineSegment<T, 2> const& seg) = default;
	LineSegment(LineSegment<T, 2>&& seg);
	LineSegment(Vector<T, 2> const& start, Vector<T, 2> const& end);

	explicit LineSegment(LineSegment<T, 1> const& seg);
	LineSegment(Vector<T, 1> const& start, Vector<T, 1> const& end);

	Vector<T, 2> GetDirection() const { return end - start; }
	T GetLengthSq() const { return GetDirection().GetMagnitudeSq(); }
	T GetLength() const { return GetDirection().GetMagnitude(); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 2>& SetLengthSq(LFRL::param<T> value);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 2>& SetLength(LFRL::param<T> value);

	Vector<T, 2> GetPointAt(LFRL::param<T> anchor) const;

	LineSegment<T, 2>& Set(LineSegment<T, 2> const& seg);
	LineSegment<T, 2>& Set(Vector<T, 2> const& start, Vector<T, 2> const& end);
	LineSegment<T, 2>& Reset();

	LineSegment<T, 2>& Set(LineSegment<T, 1> const& seg);
	LineSegment<T, 2>& Set(Vector<T, 1> const& start, Vector<T, 1> const& end);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 2>& Normalize();

	LineSegment<T, 2>& RotateCw(LFRL::param<T> radians);
	LineSegment<T, 2>& RotateCcw(LFRL::param<T> radians);
	LineSegment<T, 2>& RotateCwHalfPi();
	LineSegment<T, 2>& RotateCcwHalfPi();

	T GetAngle() const { return GetDirection().GetAngle(); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 2>& SetAngle(LFRL::param<T> radians);

	LineSegment<T, 2>& Negate();
	LineSegment<T, 2>& Incr();
	LineSegment<T, 2>& Decr();
	LineSegment<T, 2>& Add(LineSegment<T, 2> const& seg);
	LineSegment<T, 2>& Sub(LineSegment<T, 2> const& seg);
	LineSegment<T, 2>& Mult(LineSegment<T, 2> const& seg);
	LineSegment<T, 2>& Div(LineSegment<T, 2> const& seg);
	LineSegment<T, 2>& Mod(LineSegment<T, 2> const& seg);

	LineSegment<T, 2>& Add(Vector<T, 2> const& vec);
	LineSegment<T, 2>& Sub(Vector<T, 2> const& vec);
	LineSegment<T, 2>& Mult(Vector<T, 2> const& vec);
	LineSegment<T, 2>& Div(Vector<T, 2> const& vec);
	LineSegment<T, 2>& Mod(Vector<T, 2> const& vec);

	LineSegment<T, 2>& Add(LineSegment<T, 1> const& seg);
	LineSegment<T, 2>& Sub(LineSegment<T, 1> const& seg);
	LineSegment<T, 2>& Mult(LineSegment<T, 1> const& seg);
	LineSegment<T, 2>& Div(LineSegment<T, 1> const& seg);
	LineSegment<T, 2>& Mod(LineSegment<T, 1> const& seg);

	LineSegment<T, 2>& Add(Vector<T, 1> const& vec);
	LineSegment<T, 2>& Sub(Vector<T, 1> const& vec);
	LineSegment<T, 2>& Mult(Vector<T, 1> const& vec);
	LineSegment<T, 2>& Div(Vector<T, 1> const& vec);
	LineSegment<T, 2>& Mod(Vector<T, 1> const& vec);

	bool Equals(LineSegment<T, 2> const& seg) const { return start.Equals(seg.start) && end.Equals(seg.end); }

	LineSegment<T, 2> operator-() { return Negate(*this); }
	LineSegment<T, 2>& operator++() { return Incr(); }
	LineSegment<T, 2>& operator--() { return Decr(); }
	LineSegment<T, 2> operator++(int);
	LineSegment<T, 2> operator--(int);

	LineSegment<T, 2>& operator=(LineSegment<T, 2> const& seg) = default;
	LineSegment<T, 2>& operator=(LineSegment<T, 2>&& seg);
	LineSegment<T, 2>& operator+=(LineSegment<T, 2> const& seg) { return Add(seg); }
	LineSegment<T, 2>& operator-=(LineSegment<T, 2> const& seg) { return Sub(seg); }
	LineSegment<T, 2>& operator*=(LineSegment<T, 2> const& seg) { return Mult(seg); }
	LineSegment<T, 2>& operator/=(LineSegment<T, 2> const& seg) { return Div(seg); }
	LineSegment<T, 2>& operator%=(LineSegment<T, 2> const& seg) { return Mod(seg); }

	LineSegment<T, 2>& operator+=(Vector<T, 2> const& vec) { return Add(vec); }
	LineSegment<T, 2>& operator-=(Vector<T, 2> const& vec) { return Sub(vec); }
	LineSegment<T, 2>& operator*=(Vector<T, 2> const& vec) { return Mult(vec); }
	LineSegment<T, 2>& operator/=(Vector<T, 2> const& vec) { return Div(vec); }
	LineSegment<T, 2>& operator%=(Vector<T, 2> const& vec) { return Mod(vec); }

	LineSegment<T, 2>& operator+=(LineSegment<T, 1> const& seg) { return Add(seg); }
	LineSegment<T, 2>& operator-=(LineSegment<T, 1> const& seg) { return Sub(seg); }
	LineSegment<T, 2>& operator*=(LineSegment<T, 1> const& seg) { return Mult(seg); }
	LineSegment<T, 2>& operator/=(LineSegment<T, 1> const& seg) { return Div(seg); }
	LineSegment<T, 2>& operator%=(LineSegment<T, 1> const& seg) { return Mod(seg); }

	LineSegment<T, 2>& operator+=(Vector<T, 1> const& vec) { return Add(vec); }
	LineSegment<T, 2>& operator-=(Vector<T, 1> const& vec) { return Sub(vec); }
	LineSegment<T, 2>& operator*=(Vector<T, 1> const& vec) { return Mult(vec); }
	LineSegment<T, 2>& operator/=(Vector<T, 1> const& vec) { return Div(vec); }
	LineSegment<T, 2>& operator%=(Vector<T, 1> const& vec) { return Mod(vec); }

	bool operator==(LineSegment<T, 2> const& seg) const { return Equals(seg); }
	bool operator!=(LineSegment<T, 2> const& seg) const { return !Equals(seg); }
};

template <class T>
LineSegment<T, 2>::LineSegment()
	: start(), end()
{}

template <class T>
LineSegment<T, 2>::LineSegment(LineSegment<T, 2>&& seg)
	: start(std::move(seg.start)), end(std::move(seg.end))
{}

template <class T>
LineSegment<T, 2>::LineSegment(Vector<T, 2> const& start, Vector<T, 2> const& end)
	: start(start), end(end)
{}

template <class T>
LineSegment<T, 2>::LineSegment(LineSegment<T, 1> const& seg)
	: start(seg.start), end(seg.end)
{}

template <class T>
LineSegment<T, 2>::LineSegment(Vector<T, 1> const& start, Vector<T, 1> const& end)
	: start(start), end(end)
{}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 2>& LineSegment<T, 2>::SetLengthSq(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitudeSq(value);
	end = start + direction;
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 2>& LineSegment<T, 2>::SetLength(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitude(value);
	end = start + direction;
	return *this;
}

template <class T>
Vector<T, 2> LineSegment<T, 2>::GetPointAt(LFRL::param<T> anchor) const
{
	auto direction = GetDirection();
	direction.Mult(anchor);
	return start + direction;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Set(LineSegment<T, 2> const& seg)
{
	start.Set(seg.start);
	end.Set(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Set(Vector<T, 2> const& start, Vector<T, 2> const& end)
{
	start.Set(start);
	end.Set(end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Reset()
{
	start.Reset();
	end.Reset();
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Set(LineSegment<T, 1> const& seg)
{
	start.Set(seg.start);
	end.Set(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Set(Vector<T, 1> const& start, Vector<T, 1> const& end)
{
	start.Set(start);
	end.Set(end);
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 2>& LineSegment<T, 2>::Normalize()
{
	auto direction = GetDirection();
	direction.Normalize();
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::RotateCw(LFRL::param<T> radians)
{
	auto direction = GetDirection();
	direction.RotateCw(radians);
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::RotateCcw(LFRL::param<T> radians)
{
	auto direction = GetDirection();
	direction.RotateCcw(radians);
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::RotateCwHalfPi()
{
	auto direction = GetDirection();
	direction.RotateCwHalfPi();
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::RotateCcwHalfPi()
{
	auto direction = GetDirection();
	direction.RotateCcwHalfPi();
	end = start + direction;
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 2>& LineSegment<T, 2>::SetAngle(LFRL::param<T> radians)
{
	auto direction = GetDirection();
	direction.SetAngle(radians);
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Negate()
{
	start.Negate();
	end.Negate();
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Incr()
{
	start.Incr();
	end.Incr();
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Decr()
{
	start.Decr();
	end.Decr();
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Add(LineSegment<T, 2> const& seg)
{
	start.Add(seg.start);
	end.Add(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Sub(LineSegment<T, 2> const& seg)
{
	start.Sub(seg.start);
	end.Sub(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mult(LineSegment<T, 2> const& seg)
{
	start.Mult(seg.start);
	end.Mult(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Div(LineSegment<T, 2> const& seg)
{
	start.Div(seg.start);
	end.Div(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mod(LineSegment<T, 2> const& seg)
{
	start.Mod(seg.start);
	end.Mod(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Add(Vector<T, 2> const& vec)
{
	start.Add(vec);
	end.Add(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Sub(Vector<T, 2> const& vec)
{
	start.Sub(vec);
	end.Sub(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mult(Vector<T, 2> const& vec)
{
	start.Mult(vec);
	end.Mult(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Div(Vector<T, 2> const& vec)
{
	start.Div(vec);
	end.Div(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mod(Vector<T, 2> const& vec)
{
	start.Mod(vec);
	end.Mod(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Add(LineSegment<T, 1> const& seg)
{
	start.Add(seg.start);
	end.Add(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Sub(LineSegment<T, 1> const& seg)
{
	start.Sub(seg.start);
	end.Sub(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mult(LineSegment<T, 1> const& seg)
{
	start.Mult(seg.start);
	end.Mult(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Div(LineSegment<T, 1> const& seg)
{
	start.Div(seg.start);
	end.Div(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mod(LineSegment<T, 1> const& seg)
{
	start.Mod(seg.start);
	end.Mod(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Add(Vector<T, 1> const& vec)
{
	start.Add(vec);
	end.Add(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Sub(Vector<T, 1> const& vec)
{
	start.Sub(vec);
	end.Sub(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mult(Vector<T, 1> const& vec)
{
	start.Mult(vec);
	end.Mult(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Div(Vector<T, 1> const& vec)
{
	start.Div(vec);
	end.Div(vec);
	return *this;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::Mod(Vector<T, 1> const& vec)
{
	start.Mod(vec);
	end.Mod(vec);
	return *this;
}

template <class T>
LineSegment<T, 2> LineSegment<T, 2>::operator++(int)
{
	LineSegment<T, 2> result(*this);
	Incr();
	return result;
}

template <class T>
LineSegment<T, 2> LineSegment<T, 2>::operator--(int)
{
	LineSegment<T, 2> result(*this);
	Decr();
	return result;
}

template <class T>
LineSegment<T, 2>& LineSegment<T, 2>::operator=(LineSegment<T, 2>&& seg)
{
	if (this != &seg)
	{
		std::swap(start, seg.start);
		std::swap(end, seg.end);
	}
	return *this;
}

template <class T>
LineSegment<T, 2> operator+(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>::Add(seg1, seg2); }

template <class T>
LineSegment<T, 2> operator-(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>::Sub(seg1, seg2); }

template <class T>
LineSegment<T, 2> operator*(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>::Mult(seg1, seg2); }

template <class T>
LineSegment<T, 2> operator/(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>::Div(seg1, seg2); }

template <class T>
LineSegment<T, 2> operator%(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2) { return LineSegment<T, 2>::Mod(seg1, seg2); }

template <class T>
LineSegment<T, 2> operator+(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>::Add(seg, vec); }

template <class T>
LineSegment<T, 2> operator-(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>::Sub(seg, vec); }

template <class T>
LineSegment<T, 2> operator*(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>::Mult(seg, vec); }

template <class T>
LineSegment<T, 2> operator/(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>::Div(seg, vec); }

template <class T>
LineSegment<T, 2> operator%(LineSegment<T, 2> const& seg, Vector<T, 2> const& vec) { return LineSegment<T, 2>::Mod(seg, vec); }

template <class T>
LineSegment<T, 2> operator+(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>::Add(seg, seg1); }

template <class T>
LineSegment<T, 2> operator+(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>::Add(seg1, seg); }

template <class T>
LineSegment<T, 2> operator-(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>::Sub(seg, seg1); }

template <class T>
LineSegment<T, 2> operator-(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>::Sub(seg1, seg); }

template <class T>
LineSegment<T, 2> operator*(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>::Mult(seg, seg1); }

template <class T>
LineSegment<T, 2> operator*(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>::Mult(seg1, seg); }

template <class T>
LineSegment<T, 2> operator/(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>::Div(seg, seg1); }

template <class T>
LineSegment<T, 2> operator/(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>::Div(seg1, seg); }

template <class T>
LineSegment<T, 2> operator%(LineSegment<T, 2> const& seg, LineSegment<T, 1> const& seg1) { return LineSegment<T, 2>::Mod(seg, seg1); }

template <class T>
LineSegment<T, 2> operator%(LineSegment<T, 1> const& seg1, LineSegment<T, 2> const& seg) { return LineSegment<T, 2>::Mod(seg1, seg); }

template <class T>
LineSegment<T, 2> operator+(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>::Add(seg, vec); }

template <class T>
LineSegment<T, 2> operator-(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>::Sub(seg, vec); }

template <class T>
LineSegment<T, 2> operator*(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>::Mult(seg, vec); }

template <class T>
LineSegment<T, 2> operator/(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>::Div(seg, vec); }

template <class T>
LineSegment<T, 2> operator%(LineSegment<T, 2> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 2>::Mod(seg, vec); }

END_LFRL_CG_NAMESPACE

#endif
