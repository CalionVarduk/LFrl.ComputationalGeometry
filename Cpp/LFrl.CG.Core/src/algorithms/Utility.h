#ifndef __LFRL_CG_CORE_UTILITY_GUARD__
#define __LFRL_CG_CORE_UTILITY_GUARD__

#include "../math/vector_comparers.h"
#include "../math/line_segment_typedefs.h"
#include "../math/bounding_rectangle_typedefs.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct OrientationResult final
{
	typedef T type;

	T value;

	OrientationResult() : value() {}
	OrientationResult(OrientationResult<T> const&) = default;
	OrientationResult(OrientationResult<T>&& other) : value(std::move(other.value)) {}
	explicit OrientationResult(LFRL::param<T> value) : value(value) {}

	OrientationResult<T>& operator=(OrientationResult<T> const&) = default;
	OrientationResult<T>& operator=(OrientationResult<T>&& other)
	{
		if (this != &other)
			std::move(value, other.value);
		return *this;
	}

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsLeft() const { return value > static_cast<T>(0); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsRight() const { return value < static_cast<T>(0); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsCollinear() const { return value == static_cast<T>(0); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsNotCollinear() const { return value != static_cast<T>(0); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsLeftOrCollinear() const { return value >= static_cast<T>(0); }

	template <class Q = T, LFRL::requires<std::is_convertible<i32, Q>::value> = 0>
	bool IsRightOrCollinear() const { return value <= static_cast<T>(0); }
};

template <class T>
struct IntersectionResult final
{
	typedef T type;

	bool ok;
	Vector<T, 2> point;
};

template <class T>
struct BoundLineSegment
{
	typedef T type;

	BoundLineSegment() : _segment(), _bounds(_segment) {}
	BoundLineSegment(BoundLineSegment<T> const&) = default;
	BoundLineSegment(BoundLineSegment<T>&& other) : _segment(std::move(other._segment)), _bounds(std::move(other._bounds)) {}
	explicit BoundLineSegment(LineSegment<T, 2> const& seg) : _segment(seg), _bounds(_segment) {}

	BoundLineSegment<T>& operator=(BoundLineSegment<T> const&) = default;
	BoundLineSegment<T>& operator=(BoundLineSegment<T>&& other)
	{
		if (this != &other)
		{
			std::swap(_segment, other._segment);
			std::swap(_bounds, other._bounds);
		}
		return *this;
	}

	LineSegment<T, 2> const& GetSegment() const noexcept { return _segment; }
	BoundingRectangle<T> const& GetBounds() const noexcept { return _bounds; }

	void SetSegment(LineSegment<T, 2> const& seg)
	{
		_segment = seg;
		UpdateBounds();
	}

	void UpdateBounds() { _bounds = BoundingRectangle<T>(_segment); }

private:
	LineSegment<T, 2> _segment;
	BoundingRectangle<T> _bounds;
};

template <class T>
OrientationResult<T> Orientation(Vector<T, 2> const& p, Vector<T, 2> const& s, Vector<T, 2> const& e)
{
	return OrientationResult<T>((s - p).Cross(e - p));
}

template <class T>
OrientationResult<T> Orientation(Vector<T, 2> const& p, LineSegment<T, 2> const& seg)
{
	return Orientation(p, seg.start, seg.end);
}

template <class T>
bool Contains(BoundingRectangle<T> const& rect, Vector<T, 2> const& p)
{
	return p.x >= rect.bottomLeft.x &&
		p.x <= rect.topRight.x &&
		p.y >= rect.bottomLeft.y &&
		p.y <= rect.topRight.y;
}

template <class T>
bool Contains(BoundingRectangle<T> const& rect, BoundLineSegment<T> const& seg)
{
	return rect.Contains(seg.GetBounds());
}

template <class T>
bool Contains(BoundingRectangle<T> const& rect, LineSegment<T, 2> const& seg)
{
	return Contains(rect, seg.start) && Contains(rect, seg.end);
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Contains(BoundLineSegment<T> const& seg, Vector<T, 2> const& p)
{
	return Orientation(p, seg.GetSegment()).IsCollinear() && Contains(seg.GetBounds(), p);
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Contains(LineSegment<T, 2> const& seg, Vector<T, 2> const& p)
{
	return Contains(BoundLineSegment<T>(seg), p);
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Contains(BoundLineSegment<T> const& seg, BoundLineSegment<T> const& other)
{
	return Orientation(other.GetSegment().start, seg.GetSegment()).IsCollinear() &&
		Orientation(other.GetSegment().end, seg.GetSegment()).IsCollinear() &&
		seg.GetBounds().Contains(other.GetBounds());
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Contains(LineSegment<T, 2> const& seg, LineSegment<T, 2> const& other)
{
	return Contains(BoundLineSegment<T>(seg), BoundLineSegment<T>(other));
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Intersects(BoundLineSegment<T> const& seg1, BoundLineSegment<T> const& seg2)
{
	return seg1.GetBounds().Intersects(seg2.GetBounds()) &&
		OrientationResult<T>(Orientation(seg1.GetSegment().start, seg2.GetSegment()).value * Orientation(seg1.GetSegment().end, seg2.GetSegment()).value).IsRightOrCollinear() &&
		OrientationResult<T>(Orientation(seg2.GetSegment().start, seg1.GetSegment()).value * Orientation(seg2.GetSegment().end, seg1.GetSegment()).value).IsRightOrCollinear();
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
bool Intersects(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2)
{
	return Intersects(BoundLineSegment<T>(seg1), BoundLineSegment<T>(seg2));
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
IntersectionResult<T> GetLineIntersection(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2)
{
	auto d1 = seg1.GetDirection();
	auto d2 = seg2.GetDirection();
	auto directionCross = d1.Cross(d2);

	if (directionCross != static_cast<T>(0))
	{
		auto startDiff = seg2.start - seg1.start;
		auto t = startDiff.Cross(d2) / directionCross;
		auto u = startDiff.Cross(d1) / directionCross;
		return { true, d1.Mult(t).Add(seg1.start) };
	}
	return { false, Vector<T, 2>() };
}

template <class T, LFRL::requires<std::is_convertible<i32, T>::value> = 0>
IntersectionResult<T> GetSegmentIntersection(LineSegment<T, 2> const& seg1, LineSegment<T, 2> const& seg2)
{
	auto d1 = seg1.GetDirection();
	auto d2 = seg2.GetDirection();
	auto directionCross = d1.Cross(d2);

	if (directionCross != static_cast<T>(0))
	{
		auto startDiff = seg2.start - seg1.start;
		auto t = startDiff.Cross(d2) / directionCross;
		if (t >= static_cast<T>(0) && t <= static_cast<T>(1))
		{
			auto u = startDiff.Cross(d1) / directionCross;
			if (u >= static_cast<T>(0) && u <= static_cast<T>(1))
				return { true, d1.Mult(t).Add(seg1.start) };
		}
	}
	return { false, Vector<T, 2>() };
}

END_LFRL_CG_NAMESPACE

#endif
