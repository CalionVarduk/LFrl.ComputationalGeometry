#ifndef __LFRL_CG_CORE_CONVEX_HULL_QUICK_GUARD__
#define __LFRL_CG_CORE_CONVEX_HULL_QUICK_GUARD__

#include <algorithm>
#include "IConvexHull.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	struct _ch_quick_partition_predicate final
	{
		Vec2<T> const* start;
		Vec2<T> const* end;
		_ch_quick_partition_predicate(Vec2<T> const* start, Vec2<T> const* end) : start(start), end(end) {}
		bool operator()(Vec2<T> const& p)
		{
			auto orientation = Orientation(p, *start, *end);
			return orientation.IsRight();
		}
	};

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_quick_find_initial_points(array_ptr<Vec2<T>> points)
	{
		return std::minmax_element(points.begin(), points.end(), vector2_comparer_xy<T>());
	}

	template <class T>
	void _ch_quick_position_initial_points(array_ptr<Vec2<T>> points, Vec2<T>* left, Vec2<T>* right)
	{
		auto first = points.begin();
		auto last = points.end() - 1;

		std::iter_swap(first, left);
		std::iter_swap(last, right == first ? left : right);
	}

	template <class T>
	Vec2<T>* _ch_quick_find_most_distant_point(array_ptr<Vec2<T>> points, Vec2<T> const* left, Vec2<T> const* right)
	{
		auto result = points.begin();
		auto maxOrientation = Orientation(*result, *left, *right);

		for (auto p = points.begin() + 1; p < points.end(); ++p)
		{
			auto orientation = Orientation(*p, *left, *right);
			if (orientation.value < maxOrientation.value)
			{
				result = p;
				maxOrientation = orientation;
			}
		}
		return result;
	}

	template <class T>
	Vec2<T>* _ch_quick_recur_step(array_ptr<Vec2<T>> points, Vec2<T> const* left, Vec2<T> const* right, Vec2<T>* target)
	{
		if (points.size() == 0)
			return target;

		if (points.size() == 1)
		{
			std::iter_swap(points.begin(), target);
			return target + 1;
		}

		auto pivot = _ch_quick_find_most_distant_point(points, left, right);
		auto last = points.end() - 1;
		std::iter_swap(pivot, last);

		pivot = std::partition(points.begin(), last, _ch_quick_partition_predicate<T>(left, last));
		std::iter_swap(pivot, last);

		target = _ch_quick_recur_step(array_ptr<Vec2<T>>(points.begin(), pivot), left, pivot, target);
		auto nextPivot = std::partition(pivot + 1, points.end(), _ch_quick_partition_predicate<T>(pivot, right));
		std::iter_swap(pivot, target);

		return _ch_quick_recur_step(array_ptr<Vec2<T>>(pivot + 1, nextPivot), target, right, target + 1);
	}
}

template <class T>
struct ConvexHullQuick : public IConvexHull<T>
{
	ConvexHullQuick() = default;
	ConvexHullQuick(ConvexHullQuick<T> const&) = delete;
	ConvexHullQuick(ConvexHullQuick<T>&&) = default;
	ConvexHullQuick<T>& operator=(ConvexHullQuick<T> const&) = delete;
	ConvexHullQuick<T>& operator=(ConvexHullQuick<T>&&) = default;

	~ConvexHullQuick() = default;

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	void _Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points);
};

template <class T>
std::vector<Vec2<T>> ConvexHullQuick<T>::Run(array_ptr<Vec2<T>> points)
{
	std::vector<Vec2<T>> result;
	if (points.size() < 3)
		result.insert(result.end(), points.begin(), points.end());
	else
		_Run(result, points);
	return result;
}

template <class T>
void ConvexHullQuick<T>::_Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> points)
{
	auto initialPoints = detail::_ch_quick_find_initial_points(points);
	auto left = initialPoints.first;
	auto right = initialPoints.second;
	detail::_ch_quick_position_initial_points(points, left, right);
	auto first = points.begin() + 1;
	auto last = points.end() - 1;

	//TODO: think about making the points and swaps more readable
	auto pivot = std::partition(first, last, detail::_ch_quick_partition_predicate<T>(points.begin(), last));
	std::iter_swap(pivot, last);

	auto target = detail::_ch_quick_recur_step(array_ptr<Vec2<T>>(first, pivot), points.begin(), pivot, first);
	std::iter_swap(pivot, target);

	auto nextPivot = std::partition(pivot + 1, points.end(), detail::_ch_quick_partition_predicate<T>(target, points.begin()));
	target = detail::_ch_quick_recur_step(array_ptr<Vec2<T>>(pivot + 1, nextPivot), target, points.begin(), target + 1);

	// TODO: just return begin -> target array_ptr
	result.insert(result.end(), points.begin(), target);
}

END_LFRL_CG_NAMESPACE

#endif
