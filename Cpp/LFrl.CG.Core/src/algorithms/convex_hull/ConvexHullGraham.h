#ifndef __LFRL_CG_CORE_CONVEX_HULL_GRAHAM_GUARD__
#define __LFRL_CG_CORE_CONVEX_HULL_GRAHAM_GUARD__

#include <algorithm>
#include "IConvexHull.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	void _ch_graham_sort_points(array_ptr<Vec2<T>> points)
	{
		auto origin = std::min_element(points.begin(), points.end(), vector2_comparer_yx<T>());
		std::sort(points.begin(), points.end(), vector2_compare_polar_same_half<T>(*origin));
	}

	template <class T>
	Vec2<T>* _ch_graham_pop_invalid_vertexes(Vec2<T>* hullBegin, Vec2<T>* hullEnd, Vec2<T> const* current)
	{
		while (hullEnd - hullBegin > 1)
		{
			auto orientation = Orientation(*(hullEnd - 2), *(hullEnd - 1), *current);
			if (orientation.IsLeft()) // TODO: this doesn't require checking collinear points, interesting observation due to sorting?
				break;

			--hullEnd;
		}
		return hullEnd;
	}
}

template <class T>
struct ConvexHullGraham : public IConvexHull<T>
{
	ConvexHullGraham() = default;
	ConvexHullGraham(ConvexHullGraham<T> const&) = delete;
	ConvexHullGraham(ConvexHullGraham<T>&&) = default;
	ConvexHullGraham<T>& operator=(ConvexHullGraham<T> const&) = delete;
	ConvexHullGraham<T>& operator=(ConvexHullGraham<T>&&) = default;

	~ConvexHullGraham() = default;

	virtual array_ptr<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	Vec2<T>* _Run(array_ptr<Vec2<T>> points);
};

template <class T>
array_ptr<Vec2<T>> ConvexHullGraham<T>::Run(array_ptr<Vec2<T>> points)
{
	if (points.size() < 3)
		return points;

	auto hullEnd = _Run(points);
	return make_array_ptr(points.begin(), hullEnd);
}

template <class T>
Vec2<T>* ConvexHullGraham<T>::_Run(array_ptr<Vec2<T>> points)
{
	detail::_ch_graham_sort_points(points);
	auto hullEnd = points.begin() + 3;

	for (auto p = hullEnd; p < points.end(); ++p)
	{
		hullEnd = detail::_ch_graham_pop_invalid_vertexes(points.begin(), hullEnd, p);
		std::iter_swap(hullEnd++, p);
	}
	return hullEnd;
}

END_LFRL_CG_NAMESPACE

#endif
