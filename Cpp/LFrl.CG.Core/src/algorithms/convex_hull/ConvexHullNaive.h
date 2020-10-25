#ifndef __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__
#define __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__

#include <algorithm>
#include "IConvexHull.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	Vec2<T> const* _ch_naive_find_start_point(array_ptr<Vec2<T>> points)
	{
		return std::min_element(points.begin(), points.end(), vector2_comparer_yx<T>());
	}

	template <class T>
	bool _ch_naive_is_hull_vertex(array_ptr<Vec2<T>> points, Vec2<T> const* current, Vec2<T> const* point)
	{
		for (auto p = points.begin(); p < points.end(); ++p)
		{
			if (p == current || p == point)
				continue;

			auto orientation = Orientation(*point, *current, *p);
			if (orientation.IsLeft() || (orientation.IsCollinear() && (*point - *current).GetMagnitudeSq() < (*p - *current).GetMagnitudeSq()))
				return false;
		}
		return true;
	}

	template <class T>
	Vec2<T> const* _ch_naive_find_next_vertex(array_ptr<Vec2<T>> points, Vec2<T> const* current)
	{
		for (auto p = points.begin(); p < points.end(); ++p)
		{
			if (p == current)
				continue;

			if (_ch_naive_is_hull_vertex(points, current, p))
				return p;
		}
		return nullptr;
	}
}

template <class T>
struct ConvexHullNaive : public IConvexHull<T>
{
	ConvexHullNaive() = default;
	ConvexHullNaive(ConvexHullNaive<T> const&) = delete;
	ConvexHullNaive(ConvexHullNaive<T>&&) = default;
	ConvexHullNaive<T>& operator=(ConvexHullNaive<T> const&) = delete;
	ConvexHullNaive<T>& operator=(ConvexHullNaive<T>&&) = default;

	~ConvexHullNaive() = default;

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	void _Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points);
};

template <class T>
std::vector<Vec2<T>> ConvexHullNaive<T>::Run(array_ptr<Vec2<T>> points)
{
	std::vector<Vec2<T>> result;
	if (points.size() < 3)
		result.insert(result.end(), points.begin(), points.end());
	else
		_Run(result, points);
	return result;
}

template <class T>
void ConvexHullNaive<T>::_Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points)
{
	auto start = detail::_ch_naive_find_start_point(points);
	auto current = start;

	do
	{
		// TODO: push result sequentially to the beginning of points and move the begin pointer by +1
		auto next = detail::_ch_naive_find_next_vertex(points, current);
		result.push_back(*next);
		current = next;
	} while (current != start);
}


END_LFRL_CG_NAMESPACE

#endif
