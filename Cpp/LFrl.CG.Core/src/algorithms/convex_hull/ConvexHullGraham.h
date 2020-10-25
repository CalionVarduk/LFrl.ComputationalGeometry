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
	void _ch_graham_pop_invalid_vertexes(std::vector<Vec2<T>>& result, Vec2<T> const* current)
	{
		while (result.size() > 1)
		{
			auto orientation = Orientation(*(result.end() - 2), *(result.end() - 1), *current);
			if (orientation.IsLeft()) // TODO: this doesn't require checking collinear points, interesting observation due to sorting?
				break;

			result.pop_back();
		}
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

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	void _Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points);
};

template <class T>
std::vector<Vec2<T>> ConvexHullGraham<T>::Run(array_ptr<Vec2<T>> points)
{
	std::vector<Vec2<T>> result;
	if (points.size() < 3)
		result.insert(result.end(), points.begin(), points.end());
	else
		_Run(result, points);
	return result;
}

template <class T>
void ConvexHullGraham<T>::_Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points)
{
	detail::_ch_graham_sort_points(points);

	result.insert(result.end(), points.begin(), points.begin() + 3);

	// TODO: think about how to handle stack operations inside beginning of points
	// there exists an algorithm that does exactly that
	for (auto p = points.begin() + 3; p < points.end(); ++p)
	{
		detail::_ch_graham_pop_invalid_vertexes(result, p);
		result.push_back(*p);
	}
}

END_LFRL_CG_NAMESPACE

#endif
