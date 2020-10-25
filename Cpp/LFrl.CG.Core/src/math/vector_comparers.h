#ifndef __LFRL_CG_CORE_VECTOR_COMPARERS_GUARD__
#define __LFRL_CG_CORE_VECTOR_COMPARERS_GUARD__

#include "vector_typedefs.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
bool is_y_greater(Vec2<T> const& a, Vec2<T> const& b)
{
	return a.y > b.y || (a.y == b.y && a.x > b.x);
}

template <class T>
bool is_y_less(Vec2<T> const& a, Vec2<T> const& b)
{
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

template <class T>
bool is_x_greater(Vec2<T> const& a, Vec2<T> const& b)
{
	return a.x > b.x || (a.x == b.x && a.y > b.y);
}

template <class T>
bool is_x_less(Vec2<T> const& a, Vec2<T> const& b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

template <class T>
bool compare_polar_top_half_include_origin(Vec2<T> const& a, Vec2<T> const& b, Vec2<T> const& origin)
{
	auto orientation = Orientation(a, origin, b);
	if (orientation.IsRight())
		return true;
	if (orientation.IsLeft())
		return false;

	if (a.y == origin.y)
	{
		if (b.y > origin.y)
			return true;

		return a.x >= origin.x ?
			b.x < origin.x || a.x < b.x :
			b.x < a.x;
	}
	return b.y > origin.y && (a - origin).GetMagnitudeSq() < (b - origin).GetMagnitudeSq();
}


// TODO: lemma, we don't need to bother with handling special cases on the origin.y axis for graham CH 
// e.g. when a.y == b.y and sign(a.x) != sign(b.x)
// since we look for the origin with lowest y, then lowest x
// so it's impossible for a point other than origin to exist, that has the same y, but lower x
template <class T>
bool compare_polar_same_half(Vec2<T> const& a, Vec2<T> const& b, Vec2<T> const& origin)
{
	auto orientation = Orientation(a, origin, b);
	if (orientation.IsRight())
		return true;
	if (orientation.IsLeft())
		return false;
	return (a - origin).GetMagnitudeSq() < (b - origin).GetMagnitudeSq();
}

template <class T>
bool compare_polar(Vec2<T> const& a, Vec2<T> const& b, Vec2<T> const& origin)
{
	return a.y >= origin.y ?
		b.y < origin.y || compare_polar_top_half_include_origin(a, b, origin) :
		b.y < origin.y && compare_polar_same_half(a, b, origin);
}

template <class T>
struct vector2_comparer_xy
{
	typedef T type;
	typedef Vec2<T> vector_type;
	bool operator()(Vec2<T> const& a, Vec2<T> const& b) const { return is_x_less(a, b); }
};

template <class T>
struct vector2_comparer_yx
{
	typedef T type;
	typedef Vec2<T> vector_type;
	bool operator()(Vec2<T> const& a, Vec2<T> const& b) const { return is_y_less(a, b); }
};

template <class T>
struct vector2_compare_polar_same_half
{
	typedef T type;
	typedef Vec2<T> vector_type;

	Vec2<T> origin;

	vector2_compare_polar_same_half() : origin() {}
	vector2_compare_polar_same_half(Vec2<T> const& origin) : origin(origin) {}
	vector2_compare_polar_same_half(Vec2<T>&& origin) : origin(std::move(origin)) {}

	bool operator()(Vec2<T> const& a, Vec2<T> const& b) const { return compare_polar_same_half(a, b, origin); }
};

template <class T>
struct vector2_compare_polar
{
	typedef T type;
	typedef Vec2<T> vector_type;

	Vec2<T> origin;

	vector2_compare_polar() : origin() {}
	vector2_compare_polar(Vec2<T> const& origin) : origin(origin) {}
	vector2_compare_polar(Vec2<T>&& origin) : origin(std::move(origin)) {}

	bool operator()(Vec2<T> const& a, Vec2<T> const& b) const { return compare_polar(a, b, origin); }
};

END_LFRL_CG_NAMESPACE

#endif
