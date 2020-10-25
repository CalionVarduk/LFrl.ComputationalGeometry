#ifndef __LFRL_CG_CORE_CONVEX_HULL_JARVIS_GUARD__
#define __LFRL_CG_CORE_CONVEX_HULL_JARVIS_GUARD__

#include <algorithm>
#include "IConvexHull.h"
#include "LFrl.Common/src/collections/filtered.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	struct __ch_jarvis_above_origin_predicate final
	{
		Vec2<T> const* origin;
		__ch_jarvis_above_origin_predicate(Vec2<T> const* origin) : origin(origin) {}
		bool operator()(Vec2<T> const& p) const { return is_y_greater(p, *origin); }
	};

	template <class T>
	struct __ch_jarvis_below_origin_predicate final
	{
		Vec2<T> const* origin;
		__ch_jarvis_below_origin_predicate(Vec2<T> const* origin) : origin(origin) {}
		bool operator()(Vec2<T> const& p) const { return is_y_less(p, *origin); }
	};

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_jarvis_find_initial_points(array_ptr<Vec2<T>> points)
	{
		return std::minmax_element(points.begin(), points.end(), vector2_comparer_yx<T>());
	}

	template <class T>
	Vec2<T> const* _ch_jarvis_find_next_on_right_chain(array_ptr<Vec2<T>> points, Vec2<T> const* current)
	{
		auto pointsAboveCurrent = filter(points.begin(), points.end(), __ch_jarvis_above_origin_predicate<T>(current));
		// TODO: replace min_element with custom iteration
		return std::min_element(pointsAboveCurrent, pointsAboveCurrent.filter_end(), vector2_compare_polar_same_half<T>(*current)).current();

		//auto next = points.begin();
		//while (!is_y_greater(*next, *current))
		//	++next;

		//for (auto p = next + 1; p < points.end(); ++p)
		//{
		//	if (p->y < current->y)
		//		continue;

		//	if (p->y == current->y)
		//	{
		//		if (p->x <= current->x || (next->y == current->y && p->x <= next->x))
		//			continue;
		//	}
		//	else
		//	{
		//		auto orientation = Orientation(*p, *current, *next);
		//		if (orientation.IsLeft() || (orientation.IsCollinear() && (*p - *current).GetMagnitudeSq() <= (*next - *current).GetMagnitudeSq()))
		//			continue;
		//	}
		//	next = p;
		//}
		//return next;
	}

	template <class T>
	Vec2<T> const* _ch_jarvis_find_next_on_left_chain(array_ptr<Vec2<T>> points, Vec2<T> const* current)
	{
		auto pointsBelowCurrent = filter(points.begin(), points.end(), __ch_jarvis_below_origin_predicate<T>(current));
		return std::min_element(pointsBelowCurrent, pointsBelowCurrent.filter_end(), vector2_compare_polar_same_half<T>(*current)).current();

		//auto next = points.begin();
		//while (!is_y_less(*next, *current))
		//	++next;

		//for (auto p = next + 1; p < points.end(); ++p)
		//{
		//	if (p->y > current->y)
		//		continue;

		//	if (p->y == current->y)
		//	{
		//		if (p->x >= current->x || (next->y == current->y && p->x >= next->x))
		//			continue;
		//	}
		//	else
		//	{
		//		auto orientation = Orientation(*p, *current, *next);
		//		if (orientation.IsLeft() || (orientation.IsCollinear() && (*p - *current).GetMagnitudeSq() <= (*next - *current).GetMagnitudeSq()))
		//			continue;
		//	}
		//	next = p;
		//}
		//return next;
	}

	template <class T>
	void _ch_jarvis_add_right_chain(array_ptr<Vec2<T>> points, Vec2<T> const* top, Vec2<T> const* bottom, std::vector<Vec2<T>>& result)
	{
		auto current = bottom;

		while (current != top)
		{
			// TODO: think about doing this in-place, by pushing hull points to the beginning of points
			// will it break comaprison between current and top/bottom?
			current = _ch_jarvis_find_next_on_right_chain(points, current);
			result.push_back(*current);
		}
	}

	template <class T>
	void _ch_jarvis_add_left_chain(array_ptr<Vec2<T>> points, Vec2<T> const* top, Vec2<T> const* bottom, std::vector<Vec2<T>>& result)
	{
		auto current = top;

		while (current != bottom)
		{
			current = _ch_jarvis_find_next_on_left_chain(points, current);
			result.push_back(*current);
		}
	}
}

template <class T>
struct ConvexHullJarvis : public IConvexHull<T>
{
	ConvexHullJarvis() = default;
	ConvexHullJarvis(ConvexHullJarvis<T> const&) = delete;
	ConvexHullJarvis(ConvexHullJarvis<T>&&) = default;
	ConvexHullJarvis<T>& operator=(ConvexHullJarvis<T> const&) = delete;
	ConvexHullJarvis<T>& operator=(ConvexHullJarvis<T>&&) = default;

	~ConvexHullJarvis() = default;

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	void _Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points);
};

template <class T>
std::vector<Vec2<T>> ConvexHullJarvis<T>::Run(array_ptr<Vec2<T>> points)
{
	std::vector<Vec2<T>> result;
	if (points.size() < 3)
		result.insert(result.end(), points.begin(), points.end());
	else
		_Run(result, points);
	return result;
}

template <class T>
void ConvexHullJarvis<T>::_Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points)
{
	auto initialPoints = detail::_ch_jarvis_find_initial_points(points);
	auto bottom = initialPoints.first;
	auto top = initialPoints.second;

	detail::_ch_jarvis_add_right_chain(points, top, bottom, result);
	detail::_ch_jarvis_add_left_chain(points, top, bottom, result);
}

END_LFRL_CG_NAMESPACE

#endif
