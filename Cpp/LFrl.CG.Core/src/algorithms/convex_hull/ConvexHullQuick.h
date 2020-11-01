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
		Vec2<T> const* pole;
		Vec2<T> const* antipole;
		_ch_quick_partition_predicate(Vec2<T> const* pole, Vec2<T> const* antipole) : pole(pole), antipole(antipole) {}
		bool operator()(Vec2<T> const& p)
		{
			auto orientation = Orientation(p, *pole, *antipole);
			return orientation.IsRight();
		}
	};

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_quick_find_start_vertexes(array_ptr<Vec2<T>> points)
	{
		return std::minmax_element(points.begin(), points.end(), vector2_comparer_xy<T>());
	}

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_quick_emplace_start_vertexes(array_ptr<Vec2<T>> points)
	{
		auto initial = _ch_quick_find_start_vertexes(points);
		auto pole = initial.first;
		auto antipole = initial.second;

		auto first = points.begin();
		auto last = points.end() - 1;

		std::iter_swap(first, pole);
		std::iter_swap(last, antipole == first ? pole : antipole);

		return std::make_pair(first, last);
	}

	template <class T>
	Vec2<T>* _ch_quick_find_most_distant_point(array_ptr<Vec2<T>> candidates, Vec2<T> const* pole, Vec2<T> const* antipole)
	{
		auto result = candidates.begin();
		auto maxOrientation = Orientation(*result, *pole, *antipole);

		for (auto p = candidates.begin() + 1; p < candidates.end(); ++p)
		{
			auto orientation = Orientation(*p, *pole, *antipole);
			if (orientation.value < maxOrientation.value)
			{
				result = p;
				maxOrientation = orientation;
			}
		}
		return result;
	}

	template <class T>
	Vec2<T>* _ch_quick_recur_step(array_ptr<Vec2<T>> points, Vec2<T> const* pole, Vec2<T> const* antipole, Vec2<T>* hullEnd)
	{
		if (points.size() == 0)
			return hullEnd;

		if (points.size() == 1)
		{
			std::iter_swap(points.begin(), hullEnd);
			return hullEnd + 1;
		}

		auto hullVertex = _ch_quick_find_most_distant_point(points, pole, antipole);
		auto last = points.end() - 1;
		std::iter_swap(hullVertex, last);
		hullVertex = last;

		auto polePartitionPivot = std::partition(points.begin(), last, _ch_quick_partition_predicate<T>(pole, hullVertex));
		std::iter_swap(hullVertex, polePartitionPivot);
		hullVertex = polePartitionPivot;

		hullEnd = _ch_quick_recur_step(make_array_ptr(points.begin(), polePartitionPivot), pole, hullVertex, hullEnd);
		auto antipolePartitionPivot = std::partition(polePartitionPivot + 1, points.end(), _ch_quick_partition_predicate<T>(hullVertex, antipole));
		std::iter_swap(hullVertex, hullEnd);
		hullVertex = hullEnd;

		return _ch_quick_recur_step(make_array_ptr(polePartitionPivot + 1, antipolePartitionPivot), hullVertex, antipole, hullEnd + 1);
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

	virtual array_ptr<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	Vec2<T>* _Run(array_ptr<Vec2<T>> points);
};

template <class T>
array_ptr<Vec2<T>> ConvexHullQuick<T>::Run(array_ptr<Vec2<T>> points)
{
	if (points.size() < 3)
		return points;

	auto hullEnd = _Run(points);
	return make_array_ptr(points.begin(), hullEnd);
}

template <class T>
Vec2<T>* ConvexHullQuick<T>::_Run(array_ptr<Vec2<T>> points)
{
	auto initial = detail::_ch_quick_emplace_start_vertexes(points);
	auto pole = initial.first;
	auto antipole = initial.second;
	auto hullEnd = pole + 1;

	auto polePartitionPivot = std::partition(hullEnd, antipole, detail::_ch_quick_partition_predicate<T>(pole, antipole));
	std::iter_swap(polePartitionPivot, antipole);
	antipole = polePartitionPivot;

	hullEnd = detail::_ch_quick_recur_step(make_array_ptr(hullEnd, polePartitionPivot), pole, antipole, hullEnd);
	std::iter_swap(antipole, hullEnd);
	antipole = hullEnd;

	auto antipolePartitionPivot = std::partition(polePartitionPivot + 1, points.end(), detail::_ch_quick_partition_predicate<T>(antipole, pole));
	return detail::_ch_quick_recur_step(make_array_ptr(polePartitionPivot + 1, antipolePartitionPivot), antipole, pole, hullEnd + 1);
}

END_LFRL_CG_NAMESPACE

#endif
