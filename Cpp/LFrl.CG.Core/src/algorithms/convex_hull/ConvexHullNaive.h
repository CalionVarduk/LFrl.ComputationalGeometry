#ifndef __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__
#define __LFRL_CG_CORE_NAIVE_CONVEX_HULL_GUARD__

#include <algorithm>
#include "IConvexHull.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct NaiveConvexHull : public IConvexHull<T>
{
	NaiveConvexHull() = default;
	NaiveConvexHull(NaiveConvexHull<T> const&) = delete;
	NaiveConvexHull(NaiveConvexHull<T>&&) = default;
	NaiveConvexHull<T>& operator=(NaiveConvexHull<T> const&) = delete;
	NaiveConvexHull<T>& operator=(NaiveConvexHull<T>&&) = default;

	~NaiveConvexHull() = default;

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> const& points) override;

private:
	void _Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> const& points);
	Vec2<T> const* _FindNextHullVertex(array_ptr<Vec2<T>> const& points, Vec2<T> const* current);
	bool _IsHullVertex(array_ptr<Vec2<T>> const& points, Vec2<T> const* current, Vec2<T> const* point);
};

template <class T>
std::vector<Vec2<T>> NaiveConvexHull<T>::Run(array_ptr<Vec2<T>> const& points)
{
	std::vector<Vec2<T>> result;
	if (points.size() > 0)
	{
		if (points.size() < 3)
			result.insert(result.end(), points.begin(), points.end());
		else
			_Run(result, points);
	}
	return result;
}

template <class T>
void NaiveConvexHull<T>::_Run(std::vector<Vec2<T>>& result, array_ptr<Vec2<T>> const& points)
{
	auto start = std::min_element(points.begin(), points.end(), vector2_comparer_yx<T>());
	auto current = start;

	do
	{
		auto next = _FindNextHullVertex(points, current);
		result.push_back(*next);
		current = next;
	} while (current != start);
}

template <class T>
Vec2<T> const* NaiveConvexHull<T>::_FindNextHullVertex(array_ptr<Vec2<T>> const& points, Vec2<T> const* current)
{
	for (auto p = points.begin(); p < points.end() : ++p)
	{
		if (p == current)
			continue;

		if (_IsHullVertex(points, current, p))
			return p;
	}
	return nullptr;
}

template <class T>
bool NaiveConvexHull<T>::_IsHullVertex(array_ptr<Vec2<T>> const& points, Vec2<T> const* current, Vec2<T> const* point)
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

END_LFRL_CG_NAMESPACE

#endif
