#ifndef __LFRL_CG_CORE_BOUNDING_RECTANGLE_CAST_GUARD__
#define __LFRL_CG_CORE_BOUNDING_RECTANGLE_CAST_GUARD__

#include "BoundingRectangle.h"
#include "vector_cast.h"

BEGIN_LFRL_CG_NAMESPACE

template <class TDest, class TSource>
BoundingRectangle<TDest> bounding_rectangle_cast(BoundingRectangle<TSource> const& rect)
{
	return BoundingRectangle<TDest>(vector_type_cast<TDest>(rect.bottomLeft), vector_type_cast<TDest>(rect.topRight));
}

END_LFRL_CG_NAMESPACE

#endif
