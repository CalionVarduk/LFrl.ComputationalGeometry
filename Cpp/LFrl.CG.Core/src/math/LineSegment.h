#ifndef __LFRL_CG_CORE_LINE_SEGMENT_GUARD__
#define __LFRL_CG_CORE_LINE_SEGMENT_GUARD__

#include "Vector.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T, u32 dimensions>
struct LineSegment
{
	static_assert(dimensions > 0, "LineSegment<T, dimensions>: dimensions must be greater than 0.");

	typedef T type;
	typedef LFRL::param<T> param_type;

	static constexpr u32 GetDimensions() noexcept { return dimensions; }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	static LineSegment<T, dimensions> Normalize(LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg).Normalize(); }

	static LineSegment<T, dimensions> Negate(LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg).Negate(); }
	static LineSegment<T, dimensions> Incr(LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg).Incr(); }
	static LineSegment<T, dimensions> Decr(LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg).Decr(); }
	static LineSegment<T, dimensions> Add(LineSegment<T, dimensions> const& seg, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>(seg).Add(seg2); }
	static LineSegment<T, dimensions> Sub(LineSegment<T, dimensions> const& seg, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>(seg).Sub(seg2); }
	static LineSegment<T, dimensions> Mult(LineSegment<T, dimensions> const& seg, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>(seg).Mult(seg2); }
	static LineSegment<T, dimensions> Div(LineSegment<T, dimensions> const& seg, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>(seg).Div(seg2); }
	static LineSegment<T, dimensions> Mod(LineSegment<T, dimensions> const& seg, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>(seg).Mod(seg2); }

	static LineSegment<T, dimensions> Add(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>(seg).Add(vec); }
	static LineSegment<T, dimensions> Sub(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>(seg).Sub(vec); }
	static LineSegment<T, dimensions> Mult(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>(seg).Mult(vec); }
	static LineSegment<T, dimensions> Div(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>(seg).Div(vec); }
	static LineSegment<T, dimensions> Mod(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>(seg).Mod(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Add(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg2) { return LineSegment<T, dimensions>(seg).Add<dim>(seg2); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Add(LineSegment<T, dim> const& seg2, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg2).Add(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Sub(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg2) { return LineSegment<T, dimensions>(seg).Sub<dim>(seg2); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Sub(LineSegment<T, dim> const& seg2, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg2).Sub(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mult(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg2) { return LineSegment<T, dimensions>(seg).Mult<dim>(seg2); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mult(LineSegment<T, dim> const& seg2, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg2).Mult(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Div(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg2) { return LineSegment<T, dimensions>(seg).Div<dim>(seg2); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Div(LineSegment<T, dim> const& seg2, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg2).Div(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mod(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg2) { return LineSegment<T, dimensions>(seg).Mod<dim>(seg2); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mod(LineSegment<T, dim> const& seg2, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>(seg2).Mod(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Add(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>(seg).Add<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Sub(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>(seg).Sub<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mult(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>(seg).Mult<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Div(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>(seg).Div<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	static LineSegment<T, dimensions> Mod(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>(seg).Mod<dim>(vec); }

	LineSegment();
	LineSegment(LineSegment<T, dimensions> const& seg) = default;
	LineSegment(LineSegment<T, dimensions>&& seg);
	LineSegment(Vector<T, dimensions> const& start, Vector<T, dimensions> const& end);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	explicit LineSegment(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment(Vector<T, dim> const& start, Vector<T, dim> const& end);

	Vector<T, dimensions> start;
	Vector<T, dimensions> end;

	Vector<T, dimensions> GetDirection() const { return end - start; }
	T GetLengthSq() const { return GetDirection().GetMagnitudeSq(); }
	T GetLength() const { return GetDirection().GetMagnitude(); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, dimensions>& SetLengthSq(LFRL::param<T> value);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, dimensions>& SetLength(LFRL::param<T> value);

	LineSegment<T, dimensions>& Set(LineSegment<T, dimensions> const& seg);
	LineSegment<T, dimensions>& Set(Vector<T, dimensions> const& start, Vector<T, dimensions> const& end);
	LineSegment<T, dimensions>& Reset();

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Set(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Set(Vector<T, dim> const& start, Vector<T, dim> const& end);

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	LineSegment<T, dimensions>& Normalize();

	LineSegment<T, dimensions>& Negate();
	LineSegment<T, dimensions>& Incr();
	LineSegment<T, dimensions>& Decr();
	LineSegment<T, dimensions>& Add(LineSegment<T, dimensions> const& seg);
	LineSegment<T, dimensions>& Sub(LineSegment<T, dimensions> const& seg);
	LineSegment<T, dimensions>& Mult(LineSegment<T, dimensions> const& seg);
	LineSegment<T, dimensions>& Div(LineSegment<T, dimensions> const& seg);
	LineSegment<T, dimensions>& Mod(LineSegment<T, dimensions> const& seg);

	LineSegment<T, dimensions>& Add(Vector<T, dimensions> const& vec);
	LineSegment<T, dimensions>& Sub(Vector<T, dimensions> const& vec);
	LineSegment<T, dimensions>& Mult(Vector<T, dimensions> const& vec);
	LineSegment<T, dimensions>& Div(Vector<T, dimensions> const& vec);
	LineSegment<T, dimensions>& Mod(Vector<T, dimensions> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Add(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Sub(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Mult(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Div(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Mod(LineSegment<T, dim> const& seg);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Add(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Sub(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Mult(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Div(Vector<T, dim> const& vec);

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& Mod(Vector<T, dim> const& vec);

	bool Equals(LineSegment<T, dimensions> const& seg) const { return start.Equals(seg.start) && end.Equals(seg.end); }

	LineSegment<T, dimensions> operator-() { return Negate(*this); }
	LineSegment<T, dimensions>& operator++() { return Incr(); }
	LineSegment<T, dimensions>& operator--() { return Decr(); }
	LineSegment<T, dimensions> operator++(int);
	LineSegment<T, dimensions> operator--(int);

	LineSegment<T, dimensions>& operator=(LineSegment<T, dimensions> const& seg) = default;
	LineSegment<T, dimensions>& operator=(LineSegment<T, dimensions>&& seg);
	LineSegment<T, dimensions>& operator+=(LineSegment<T, dimensions> const& seg) { return Add(seg); }
	LineSegment<T, dimensions>& operator-=(LineSegment<T, dimensions> const& seg) { return Sub(seg); }
	LineSegment<T, dimensions>& operator*=(LineSegment<T, dimensions> const& seg) { return Mult(seg); }
	LineSegment<T, dimensions>& operator/=(LineSegment<T, dimensions> const& seg) { return Div(seg); }
	LineSegment<T, dimensions>& operator%=(LineSegment<T, dimensions> const& seg) { return Mod(seg); }

	LineSegment<T, dimensions>& operator+=(Vector<T, dimensions> const& vec) { return Add(vec); }
	LineSegment<T, dimensions>& operator-=(Vector<T, dimensions> const& vec) { return Sub(vec); }
	LineSegment<T, dimensions>& operator*=(Vector<T, dimensions> const& vec) { return Mult(vec); }
	LineSegment<T, dimensions>& operator/=(Vector<T, dimensions> const& vec) { return Div(vec); }
	LineSegment<T, dimensions>& operator%=(Vector<T, dimensions> const& vec) { return Mod(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator+=(LineSegment<T, dim> const& seg) { return Add<dim>(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator-=(LineSegment<T, dim> const& seg) { return Sub<dim>(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator*=(LineSegment<T, dim> const& seg) { return Mult<dim>(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator/=(LineSegment<T, dim> const& seg) { return Div<dim>(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator%=(LineSegment<T, dim> const& seg) { return Mod<dim>(seg); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator+=(Vector<T, dim> const& vec) { return Add<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator-=(Vector<T, dim> const& vec) { return Sub<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator*=(Vector<T, dim> const& vec) { return Mult<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator/=(Vector<T, dim> const& vec) { return Div<dim>(vec); }

	template <u32 dim, LFRL::requires<dim < dimensions> = 0>
	LineSegment<T, dimensions>& operator%=(Vector<T, dim> const& vec) { return Mod<dim>(vec); }

	bool operator==(LineSegment<T, dimensions> const& seg) const { return Equals(seg); }
	bool operator!=(LineSegment<T, dimensions> const& seg) const { return !Equals(seg); }
};

template <class T, u32 dimensions>
LineSegment<T, dimensions>::LineSegment()
	: start(), end()
{}

template <class T, u32 dimensions>
LineSegment<T, dimensions>::LineSegment(LineSegment<T, dimensions>&& seg)
	: start(std::move(seg.start)), end(std::move(seg.end))
{}

template <class T, u32 dimensions>
LineSegment<T, dimensions>::LineSegment(Vector<T, dimensions> const& start, Vector<T, dimensions> const& end)
	: start(start), end(end)
{}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>::LineSegment(LineSegment<T, dim> const& seg)
	: start(seg.start), end(seg.end)
{}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>::LineSegment(Vector<T, dim> const& start, Vector<T, dim> const& end)
	: start(start), end(end)
{}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::SetLengthSq(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitudeSq(value);
	end = start + direction;
	return *this;
}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::SetLength(LFRL::param<T> value)
{
	auto direction = GetDirection();
	direction.SetMagnitude(value);
	end = start + direction;
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Set(LineSegment<T, dimensions> const& seg)
{
	start.Set(seg.start);
	end.Set(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Set(Vector<T, dimensions> const& start, Vector<T, dimensions> const& end)
{
	start.Set(start);
	end.Set(end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Reset()
{
	start.Reset();
	end.Reset();
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Set(LineSegment<T, dim> const& seg)
{
	start.Set(seg.start);
	end.Set(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Set(Vector<T, dim> const& start, Vector<T, dim> const& end)
{
	start.Set(start);
	end.Set(end);
	return *this;
}

template <class T, u32 dimensions> template <class Q, LFRL::requires<std::is_convertible<i32, Q>::value>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Normalize()
{
	auto direction = GetDirection();
	direction.Normalize();
	end = start + direction;
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Negate()
{
	start.Negate();
	end.Negate();
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Incr()
{
	start.Incr();
	end.Incr();
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Decr()
{
	start.Decr();
	end.Decr();
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Add(LineSegment<T, dimensions> const& seg)
{
	start.Add(seg.start);
	end.Add(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Sub(LineSegment<T, dimensions> const& seg)
{
	start.Sub(seg.start);
	end.Sub(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mult(LineSegment<T, dimensions> const& seg)
{
	start.Mult(seg.start);
	end.Mult(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Div(LineSegment<T, dimensions> const& seg)
{
	start.Div(seg.start);
	end.Div(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mod(LineSegment<T, dimensions> const& seg)
{
	start.Mod(seg.start);
	end.Mod(seg.end);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Add(Vector<T, dimensions> const& vec)
{
	start.Add(vec);
	end.Add(vec);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Sub(Vector<T, dimensions> const& vec)
{
	start.Sub(vec);
	end.Sub(vec);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mult(Vector<T, dimensions> const& vec)
{
	start.Mult(vec);
	end.Mult(vec);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Div(Vector<T, dimensions> const& vec)
{
	start.Div(vec);
	end.Div(vec);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mod(Vector<T, dimensions> const& vec)
{
	start.Mod(vec);
	end.Mod(vec);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Add(LineSegment<T, dim> const& seg)
{
	start.Add(seg.start);
	end.Add(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Sub(LineSegment<T, dim> const& seg)
{
	start.Sub(seg.start);
	end.Sub(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mult(LineSegment<T, dim> const& seg)
{
	start.Mult(seg.start);
	end.Mult(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Div(LineSegment<T, dim> const& seg)
{
	start.Div(seg.start);
	end.Div(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mod(LineSegment<T, dim> const& seg)
{
	start.Mod(seg.start);
	end.Mod(seg.end);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Add(Vector<T, dim> const& vec)
{
	start.Add(vec);
	end.Add(vec);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Sub(Vector<T, dim> const& vec)
{
	start.Sub(vec);
	end.Sub(vec);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mult(Vector<T, dim> const& vec)
{
	start.Mult(vec);
	end.Mult(vec);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Div(Vector<T, dim> const& vec)
{
	start.Div(vec);
	end.Div(vec);
	return *this;
}

template <class T, u32 dimensions> template <u32 dim, LFRL::requires<dim < dimensions>>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::Mod(Vector<T, dim> const& vec)
{
	start.Mod(vec);
	end.Mod(vec);
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions> LineSegment<T, dimensions>::operator++(int)
{
	LineSegment<T, dimensions> result(*this);
	Incr();
	return result;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions> LineSegment<T, dimensions>::operator--(int)
{
	LineSegment<T, dimensions> result(*this);
	Decr();
	return result;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions>& LineSegment<T, dimensions>::operator=(LineSegment<T, dimensions>&& seg)
{
	if (this != &seg)
	{
		std::swap(start, seg.start);
		std::swap(end, seg.end);
	}
	return *this;
}

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator+(LineSegment<T, dimensions> const& seg1, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>::Add(seg1, seg2); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator-(LineSegment<T, dimensions> const& seg1, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>::Sub(seg1, seg2); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator*(LineSegment<T, dimensions> const& seg1, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>::Mult(seg1, seg2); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator/(LineSegment<T, dimensions> const& seg1, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>::Div(seg1, seg2); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator%(LineSegment<T, dimensions> const& seg1, LineSegment<T, dimensions> const& seg2) { return LineSegment<T, dimensions>::Mod(seg1, seg2); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator+(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>::Add(seg, vec); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator-(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>::Sub(seg, vec); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator*(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>::Mult(seg, vec); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator/(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>::Div(seg, vec); }

template <class T, u32 dimensions>
LineSegment<T, dimensions> operator%(LineSegment<T, dimensions> const& seg, Vector<T, dimensions> const& vec) { return LineSegment<T, dimensions>::Mod(seg, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator+(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg1) { return LineSegment<T, dimensions>::Add<dim>(seg, seg1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator+(LineSegment<T, dim> const& seg1, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>::Add<dim>(seg1, seg); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator-(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg1) { return LineSegment<T, dimensions>::Sub<dim>(seg, seg1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator-(LineSegment<T, dim> const& seg1, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>::Sub<dim>(seg1, seg); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator*(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg1) { return LineSegment<T, dimensions>::Mult<dim>(seg, seg1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator*(LineSegment<T, dim> const& seg1, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>::Mult<dim>(seg1, seg); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator/(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg1) { return LineSegment<T, dimensions>::Div<dim>(seg, seg1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator/(LineSegment<T, dim> const& seg1, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>::Div<dim>(seg1, seg); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator%(LineSegment<T, dimensions> const& seg, LineSegment<T, dim> const& seg1) { return LineSegment<T, dimensions>::Mod<dim>(seg, seg1); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator%(LineSegment<T, dim> const& seg1, LineSegment<T, dimensions> const& seg) { return LineSegment<T, dimensions>::Mod<dim>(seg1, seg); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator+(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>::Add<dim>(seg, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator-(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>::Sub<dim>(seg, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator*(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>::Mult<dim>(seg, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator/(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>::Div<dim>(seg, vec); }

template <class T, u32 dimensions, u32 dim, LFRL::requires<dim < dimensions> = 0>
LineSegment<T, dimensions> operator%(LineSegment<T, dimensions> const& seg, Vector<T, dim> const& vec) { return LineSegment<T, dimensions>::Mod<dim>(seg, vec); }

END_LFRL_CG_NAMESPACE

#endif
