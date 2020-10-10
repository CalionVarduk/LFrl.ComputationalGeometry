#ifndef __LFRL_CG_CORE_LINE_SEGMENT1_GUARD__
#define __LFRL_CG_CORE_LINE_SEGMENT1_GUARD__

#include "LineSegment.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct LineSegment<T, 1>
{
	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetDimensions() noexcept { return 1; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static LineSegment<T, 1> Normalize(LineSegment<T, 1> const& seg) { return LineSegment<T, 1>(seg).Normalize(); }

	static LineSegment<T, 1> Negate(LineSegment<T, 1> const& seg) { return LineSegment<T, 1>(seg).Negate(); }
	static LineSegment<T, 1> Incr(LineSegment<T, 1> const& seg) { return LineSegment<T, 1>(seg).Incr(); }
	static LineSegment<T, 1> Decr(LineSegment<T, 1> const& seg) { return LineSegment<T, 1>(seg).Decr(); }
	static LineSegment<T, 1> Add(LineSegment<T, 1> const& seg, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>(seg).Add(seg2); }
	static LineSegment<T, 1> Sub(LineSegment<T, 1> const& seg, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>(seg).Sub(seg2); }
	static LineSegment<T, 1> Mult(LineSegment<T, 1> const& seg, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>(seg).Mult(seg2); }
	static LineSegment<T, 1> Div(LineSegment<T, 1> const& seg, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>(seg).Div(seg2); }
	static LineSegment<T, 1> Mod(LineSegment<T, 1> const& seg, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>(seg).Mod(seg2); }

	static LineSegment<T, 1> Add(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>(seg).Add(vec); }
	static LineSegment<T, 1> Sub(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>(seg).Sub(vec); }
	static LineSegment<T, 1> Mult(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>(seg).Mult(vec); } 
	static LineSegment<T, 1> Div(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>(seg).Div(vec); }
	static LineSegment<T, 1> Mod(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>(seg).Mod(vec); }

	Vector<T, 1> start;
	Vector<T, 1> end;

	LineSegment();
	LineSegment(LineSegment<T, 1> const& seg) = default;
	LineSegment(LineSegment<T, 1>&& seg);
	LineSegment(Vector<T, 1> const& start, Vector<T, 1> const& end);

	Vector<T, 1> GetDirection() const { return end - start; }
	T GetLengthSq() const { return GetDirection().GetMagnitudeSq(); }
	T GetLength() const { return GetDirection().GetMagnitude(); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 1>& SetLengthSq(LFRL::param<T> value);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 1>& SetLength(LFRL::param<T> value);

	Vector<T, 1> GetPointAt(LFRL::param<T> anchor) const;

	LineSegment<T, 1>& Set(LineSegment<T, 1> const& seg);
	LineSegment<T, 1>& Set(Vector<T, 1> const& start, Vector<T, 1> const& end);
	LineSegment<T, 1>& Reset();

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, 1>& Normalize();

	LineSegment<T, 1>& Negate();
	LineSegment<T, 1>& Incr();
	LineSegment<T, 1>& Decr();
	LineSegment<T, 1>& Add(LineSegment<T, 1> const& seg);
	LineSegment<T, 1>& Sub(LineSegment<T, 1> const& seg);
	LineSegment<T, 1>& Mult(LineSegment<T, 1> const& seg);
	LineSegment<T, 1>& Div(LineSegment<T, 1> const& seg);
	LineSegment<T, 1>& Mod(LineSegment<T, 1> const& seg);

	LineSegment<T, 1>& Add(Vector<T, 1> const& vec);
	LineSegment<T, 1>& Sub(Vector<T, 1> const& vec);
	LineSegment<T, 1>& Mult(Vector<T, 1> const& vec);
	LineSegment<T, 1>& Div(Vector<T, 1> const& vec);
	LineSegment<T, 1>& Mod(Vector<T, 1> const& vec);

	bool Equals(LineSegment<T, 1> const& seg) const { return start.Equals(seg.start) && end.Equals(seg.end); }

	LineSegment<T, 1> operator-() { return Negate(*this); }
	LineSegment<T, 1>& operator++() { return Incr(); }
	LineSegment<T, 1>& operator--() { return Decr(); }
	LineSegment<T, 1> operator++(int);
	LineSegment<T, 1> operator--(int);

	LineSegment<T, 1>& operator=(LineSegment<T, 1> const& seg) = default;
	LineSegment<T, 1>& operator=(LineSegment<T, 1>&& seg);
	LineSegment<T, 1>& operator+=(LineSegment<T, 1> const& seg) { return Add(seg); }
	LineSegment<T, 1>& operator-=(LineSegment<T, 1> const& seg) { return Sub(seg); }
	LineSegment<T, 1>& operator*=(LineSegment<T, 1> const& seg) { return Mult(seg); }
	LineSegment<T, 1>& operator/=(LineSegment<T, 1> const& seg) { return Div(seg); }
	LineSegment<T, 1>& operator%=(LineSegment<T, 1> const& seg) { return Mod(seg); }

	LineSegment<T, 1>& operator+=(Vector<T, 1> const& vec) { return Add(vec); }
	LineSegment<T, 1>& operator-=(Vector<T, 1> const& vec) { return Sub(vec); }
	LineSegment<T, 1>& operator*=(Vector<T, 1> const& vec) { return Mult(vec); }
	LineSegment<T, 1>& operator/=(Vector<T, 1> const& vec) { return Div(vec); }
	LineSegment<T, 1>& operator%=(Vector<T, 1> const& vec) { return Mod(vec); }

	bool operator==(LineSegment<T, 1> const& seg) const { return Equals(seg); }
	bool operator!=(LineSegment<T, 1> const& seg) const { return !Equals(seg); }
};

template <class T>
LineSegment<T, 1>::LineSegment()
	: start(), end()
{}

template <class T>
LineSegment<T, 1>::LineSegment(LineSegment<T, 1>&& seg)
	: start(std::move(seg.start)), end(std::move(seg.end))
{}

template <class T>
LineSegment<T, 1>::LineSegment(Vector<T, 1> const& start, Vector<T, 1> const& end)
	: start(start), end(end)
{}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 1>& LineSegment<T, 1>::SetLengthSq(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitudeSq(value);
	end = start + direction;
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 1>& LineSegment<T, 1>::SetLength(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitude(value);
	end = start + direction;
	return *this;
}

template <class T>
Vector<T, 1> LineSegment<T, 1>::GetPointAt(LFRL::param<T> anchor) const
{
	auto direction = GetDirection();
	direction.Mult(anchor);
	return start + direction;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Set(LineSegment<T, 1> const& seg)
{
	start.Set(seg.start);
	end.Set(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Set(Vector<T, 1> const& start, Vector<T, 1> const& end)
{
	start.Set(start);
	end.Set(end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Reset()
{
	start.Reset();
	end.Reset();
	return *this;
}

template <class T> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, 1>& LineSegment<T, 1>::Normalize()
{
	auto direction = GetDirection();
	direction.Normalize();
	end = start + direction;
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Negate()
{
	start.Negate();
	end.Negate();
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Incr()
{
	start.Incr();
	end.Incr();
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Decr()
{
	start.Decr();
	end.Decr();
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Add(LineSegment<T, 1> const& seg)
{
	start.Add(seg.start);
	end.Add(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Sub(LineSegment<T, 1> const& seg)
{
	start.Sub(seg.start);
	end.Sub(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Mult(LineSegment<T, 1> const& seg)
{
	start.Mult(seg.start);
	end.Mult(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Div(LineSegment<T, 1> const& seg)
{
	start.Div(seg.start);
	end.Div(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Mod(LineSegment<T, 1> const& seg)
{
	start.Mod(seg.start);
	end.Mod(seg.end);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Add(Vector<T, 1> const& vec)
{
	start.Add(vec);
	end.Add(vec);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Sub(Vector<T, 1> const& vec)
{
	start.Sub(vec);
	end.Sub(vec);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Mult(Vector<T, 1> const& vec)
{
	start.Mult(vec);
	end.Mult(vec);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Div(Vector<T, 1> const& vec)
{
	start.Div(vec);
	end.Div(vec);
	return *this;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::Mod(Vector<T, 1> const& vec)
{
	start.Mod(vec);
	end.Mod(vec);
	return *this;
}

template <class T>
LineSegment<T, 1> LineSegment<T, 1>::operator++(int)
{
	LineSegment<T, 1> result(*this);
	Incr();
	return result;
}

template <class T>
LineSegment<T, 1> LineSegment<T, 1>::operator--(int)
{
	LineSegment<T, 1> result(*this);
	Decr();
	return result;
}

template <class T>
LineSegment<T, 1>& LineSegment<T, 1>::operator=(LineSegment<T, 1>&& seg)
{
	if (this != &seg)
	{
	std::swap(start, seg.start);
	std::swap(end, seg.end);
	}
	return *this;
}

template <class T>
LineSegment<T, 1> operator+(LineSegment<T, 1> const& seg1, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>::Add(seg1, seg2); }

template <class T>
LineSegment<T, 1> operator-(LineSegment<T, 1> const& seg1, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>::Sub(seg1, seg2); }

template <class T>
LineSegment<T, 1> operator*(LineSegment<T, 1> const& seg1, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>::Mult(seg1, seg2); }

template <class T>
LineSegment<T, 1> operator/(LineSegment<T, 1> const& seg1, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>::Div(seg1, seg2); }

template <class T>
LineSegment<T, 1> operator%(LineSegment<T, 1> const& seg1, LineSegment<T, 1> const& seg2) { return LineSegment<T, 1>::Mod(seg1, seg2); }

template <class T>
LineSegment<T, 1> operator+(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>::Add(seg, vec); }

template <class T>
LineSegment<T, 1> operator-(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>::Sub(seg, vec); }

template <class T>
LineSegment<T, 1> operator*(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>::Mult(seg, vec); }

template <class T>
LineSegment<T, 1> operator/(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>::Div(seg, vec); }

template <class T>
LineSegment<T, 1> operator%(LineSegment<T, 1> const& seg, Vector<T, 1> const& vec) { return LineSegment<T, 1>::Mod(seg, vec); }

END_LFRL_CG_NAMESPACE

#endif
