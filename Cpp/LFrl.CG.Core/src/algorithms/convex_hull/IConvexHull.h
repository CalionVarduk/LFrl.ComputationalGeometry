#ifndef __LFRL_CG_CORE_CONVEX_HULL_GUARD__
#define __LFRL_CG_CORE_CONVEX_HULL_GUARD__

#include <vector>
#include "../Utility.h"
#include "LFrl.Common/src/memory/array_ptr.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct IConvexHull
{
	IConvexHull(IConvexHull<T> const&) = delete;
	IConvexHull(IConvexHull<T>&&) = default;
	IConvexHull<T>& operator=(IConvexHull<T> const&) = delete;
	IConvexHull<T>& operator=(IConvexHull<T>&&) = default;

	virtual ~IConvexHull() = default;

	virtual std::vector<Vec2<T>> Run(array_ptr<Vec2<T>> points) = 0; // TODO: replace result with array_ptr

protected:
	IConvexHull() = default;
};

END_LFRL_CG_NAMESPACE

#endif
