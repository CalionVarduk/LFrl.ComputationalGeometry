#ifndef __LFRL_CG_CORE_CONVEX_HULL_JARVIS_GUARD__
#define __LFRL_CG_CORE_CONVEX_HULL_JARVIS_GUARD__

#include <algorithm>
#include "IConvexHull.h"
#include "LFrl.Common/src/collections/filtered.h"

BEGIN_LFRL_CG_NAMESPACE

namespace detail
{
	template <class T>
	struct _ch_jarvis_above_origin_predicate final
	{
		Vec2<T> const* origin;
		_ch_jarvis_above_origin_predicate(Vec2<T> const* origin) : origin(origin) {}
		bool operator()(Vec2<T> const& p) const { return is_y_greater(p, *origin); }
	};

	template <class T>
	struct _ch_jarvis_below_origin_predicate final
	{
		Vec2<T> const* origin;
		_ch_jarvis_below_origin_predicate(Vec2<T> const* origin) : origin(origin) {}
		bool operator()(Vec2<T> const& p) const { return is_y_less(p, *origin); }
	};

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_jarvis_find_initial_vertexes(array_ptr<Vec2<T>> points)
	{
		return std::minmax_element(points.begin(), points.end(), vector2_comparer_yx<T>());
	}

	template <class T>
	std::pair<Vec2<T>*, Vec2<T>*> _ch_jarvis_emplace_initial_vertexes(array_ptr<Vec2<T>> points)
	{
		auto initial = _ch_jarvis_find_initial_vertexes(points);
		auto bottom = initial.first;
		auto top = initial.second;

		auto first = points.begin();
		auto last = points.end() - 1;

		std::iter_swap(first, bottom);
		std::iter_swap(last, top == first ? bottom : top);

		return std::make_pair(first, last);
	}

	template <class T, class TPred>
	Vec2<T>* _ch_jarvis_find_next_vertex_on_chain(array_ptr<Vec2<T>> candidates, Vec2<T> const* lastHullVertex, TPred predicate)
	{
		auto candidatesIterator = filter(candidates.begin(), candidates.end(), predicate);
		auto result = candidatesIterator.current();
		++candidatesIterator;

		while (candidatesIterator != candidatesIterator.end())
		{
			if (compare_polar_same_half_inverse_magnitude(*candidatesIterator.current(), *result, *lastHullVertex))
				result = candidatesIterator.current();

			++candidatesIterator;
		}
		return result;
	}

	template <class T>
	Vec2<T>* _ch_jarvis_find_next_vertex_on_right_chain(array_ptr<Vec2<T>> candidates, Vec2<T> const* lastHullVertex)
	{
		return _ch_jarvis_find_next_vertex_on_chain(candidates, lastHullVertex, _ch_jarvis_above_origin_predicate<T>(lastHullVertex));
	}

	template <class T>
	Vec2<T>* _ch_jarvis_find_next_vertex_on_left_chain(array_ptr<Vec2<T>> candidates, Vec2<T> const* lastHullVertex)
	{
		return _ch_jarvis_find_next_vertex_on_chain(candidates, lastHullVertex, _ch_jarvis_below_origin_predicate<T>(lastHullVertex));
	}

	template <class T>
	Vec2<T>* _ch_jarvis_emplace_right_chain(array_ptr<Vec2<T>> points, Vec2<T> const* top, Vec2<T>* hullEnd)
	{
		while (true)
		{
			auto candidateVertex = _ch_jarvis_find_next_vertex_on_right_chain(make_array_ptr(hullEnd, points.end()), hullEnd - 1);
			std::iter_swap(candidateVertex, hullEnd++);

			if (candidateVertex == top)
				break;
		}
		return hullEnd;
	}

	template <class T>
	Vec2<T>* _ch_jarvis_emplace_left_chain(array_ptr<Vec2<T>> points, Vec2<T> const* bottom, Vec2<T>* hullEnd)
	{
		while (true)
		{
			auto candidateVertex = _ch_jarvis_find_next_vertex_on_left_chain(make_array_ptr(hullEnd, points.end()), hullEnd - 1);
			if (candidateVertex == points.end())
				break;

			if (compare_polar_same_half_inverse_magnitude(*bottom, *candidateVertex, *(hullEnd - 1)))
				break;

			std::iter_swap(candidateVertex, hullEnd++);
		}
		return hullEnd;
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

	virtual array_ptr<Vec2<T>> Run(array_ptr<Vec2<T>> points) override;

private:
	Vec2<T>* _Run(array_ptr<Vec2<T>> points);
};

template <class T>
array_ptr<Vec2<T>> ConvexHullJarvis<T>::Run(array_ptr<Vec2<T>> points)
{
	if (points.size() < 3)
		return points;
	
	auto hullEnd = _Run(points);
	return make_array_ptr(points.begin(), hullEnd);
}

template <class T>
Vec2<T>* ConvexHullJarvis<T>::_Run(array_ptr<Vec2<T>> points)
{
	auto initial = detail::_ch_jarvis_emplace_initial_vertexes(points);
	auto bottom = initial.first;
	auto top = initial.second;
	auto hullEnd = bottom + 1;

	hullEnd = detail::_ch_jarvis_emplace_right_chain(points, top, hullEnd);
	return detail::_ch_jarvis_emplace_left_chain(points, bottom, hullEnd);
}

END_LFRL_CG_NAMESPACE

#endif
