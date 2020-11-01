#ifndef __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__
#define __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__

#include <algorithm>
#include "IConvexHull.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	Vec2<T>* _ch_naive_find_start_vertex(array_ptr<Vec2<T>> points)
	{
		return std::min_element(points.begin(), points.end(), vector2_comparer_yx<T>());
	}

	template <class T>
	Vec2<T>* _ch_naive_emplace_start_vertex(array_ptr<Vec2<T>> points)
	{
		auto startVertex = _ch_naive_find_start_vertex(points);
		std::iter_swap(startVertex, points.begin());
		return points.begin();
	}

	template <class T>
	bool _ch_naive_is_hull_vertex(array_ptr<Vec2<T>> candidates, Vec2<T> const* lastHullVertex, Vec2<T> const* point)
	{
		for (auto p = candidates.begin(); p < candidates.end(); ++p)
		{
			if (p == point)
				continue;

			if (compare_polar_same_half_inverse_magnitude(*p, *point, *lastHullVertex))
				return false;
		}
		return true;
	}

	template <class T>
	Vec2<T>* _ch_naive_find_next_vertex_candidate(array_ptr<Vec2<T>> candidates, Vec2<T> const* lastHullVertex)
	{
		auto end = candidates.end() - 1;

		for (auto p = candidates.begin(); p < end; ++p)
			if (_ch_naive_is_hull_vertex(candidates, lastHullVertex, p))
				return p;

		return end;
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

	virtual array_ptr<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	Vec2<T>* _Run(array_ptr<Vec2<T>> points);
};

template <class T>
array_ptr<Vec2<T>> ConvexHullNaive<T>::Run(array_ptr<Vec2<T>> points)
{
	if (points.size() < 3)
		return points;
	
	auto hullEnd = _Run(points);
	return make_array_ptr(points.begin(), hullEnd);
}

template <class T>
Vec2<T>* ConvexHullNaive<T>::_Run(array_ptr<Vec2<T>> points)
{
	auto hullBegin = detail::_ch_naive_emplace_start_vertex(points);
	auto hullEnd = hullBegin + 1;

	while (true)
	{
		auto candidateVertex = detail::_ch_naive_find_next_vertex_candidate(make_array_ptr(hullEnd, points.end()), hullEnd - 1);
		if (candidateVertex == points.end())
			break;

		if (compare_polar_same_half_inverse_magnitude(*hullBegin, *candidateVertex, *(hullEnd - 1)))
			break;

		std::iter_swap(candidateVertex, hullEnd++);
	}
	return hullEnd;
}


END_LFRL_CG_NAMESPACE

#endif
