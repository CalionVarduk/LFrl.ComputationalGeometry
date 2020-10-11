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

END_LFRL_CG_NAMESPACE

#endif
