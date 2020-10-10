#ifndef __LFRL_CG_CORE_LINE_SEGMENT_CAST_GUARD__
#define __LFRL_CG_CORE_LINE_SEGMENT_CAST_GUARD__

#include "LineSegment3.h"
#include "vector_cast.h"

BEGIN_LFRL_CG_NAMESPACE

template <u32 destDimensions, class T, u32 sourceDimensions>
LineSegment<T, destDimensions> line_segment_size_cast(LineSegment<T, sourceDimensions> const& seg)
{
	return LineSegment<T, destDimensions>(vector_size_cast<destDimensions>(seg.start), vector_size_cast<destDimensions>(seg.end));
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
LineSegment<T, 1> line_segment_size_cast(LineSegment<T, 1> const& seg)
{
	return seg;
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
LineSegment<T, 2> line_segment_size_cast(LineSegment<T, 1> const& seg)
{
	return LineSegment<T, 2>(seg);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
LineSegment<T, 3> line_segment_size_cast(LineSegment<T, 1> const& seg)
{
	return LineSegment<T, 3>(seg);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
LineSegment<T, 1> line_segment_size_cast(LineSegment<T, 2> const& seg)
{
	return LineSegment<T, 1>(vector_size_cast<1>(seg.start), vector_size_cast<1>(seg.end));
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
LineSegment<T, 2> line_segment_size_cast(LineSegment<T, 2> const& seg)
{
	return seg;
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
LineSegment<T, 3> line_segment_size_cast(LineSegment<T, 2> const& seg)
{
	return LineSegment<T, 3>(seg);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
LineSegment<T, 1> line_segment_size_cast(LineSegment<T, 3> const& seg)
{
	return LineSegment<T, 1>(vector_size_cast<1>(seg.start), vector_size_cast<1>(seg.end));
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
LineSegment<T, 2> line_segment_size_cast(LineSegment<T, 3> const& seg)
{
	return LineSegment<T, 2>(vector_size_cast<2>(seg.start), vector_size_cast<2>(seg.end));
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
LineSegment<T, 3> line_segment_size_cast(LineSegment<T, 3> const& seg)
{
	return seg;
}

template <class TDest, class TSource, u32 dimensions, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
LineSegment<TDest, dimensions> line_segment_type_cast(LineSegment<TSource, dimensions> const& seg)
{
	return LineSegment<TDest, dimensions>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
LineSegment<TDest, 1> line_segment_type_cast(LineSegment<TSource, 1> const& seg)
{
	return LineSegment<TDest, 1>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
LineSegment<TDest, 2> line_segment_type_cast(LineSegment<TSource, 2> const& seg)
{
	return LineSegment<TDest, 2>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
LineSegment<TDest, 3> line_segment_type_cast(LineSegment<TSource, 3> const& seg)
{
	return LineSegment<TDest, 3>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, u32 sourceDimensions, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
LineSegment<TDest, destDimensions> line_segment_cast(LineSegment<TSource, sourceDimensions> const& seg)
{
	return LineSegment<TDest, destDimensions>(vector_cast<TDest, destDimensions>(seg.start), vector_cast<TDest, destDimensions>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
LineSegment<TDest, 1> line_segment_cast(LineSegment<TSource, 1> const& seg)
{
	return LineSegment<TDest, 1>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
LineSegment<TDest, 2> line_segment_cast(LineSegment<TSource, 1> const& seg)
{
	return LineSegment<TDest, 2>(vector_cast<TDest, 2>(seg.start), vector_cast<TDest, 2>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
LineSegment<TDest, 3> line_segment_cast(LineSegment<TSource, 1> const& seg)
{
	return LineSegment<TDest, 3>(vector_cast<TDest, 3>(seg.start), vector_cast<TDest, 3>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
LineSegment<TDest, 1> line_segment_cast(LineSegment<TSource, 2> const& seg)
{
	return LineSegment<TDest, 1>(vector_cast<TDest, 1>(seg.start), vector_cast<TDest, 1>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
LineSegment<TDest, 2> line_segment_cast(LineSegment<TSource, 2> const& seg)
{
	return LineSegment<TDest, 2>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
LineSegment<TDest, 3> line_segment_cast(LineSegment<TSource, 2> const& seg)
{
	return LineSegment<TDest, 3>(vector_cast<TDest, 3>(seg.start), vector_cast<TDest, 3>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
LineSegment<TDest, 1> line_segment_cast(LineSegment<TSource, 3> const& seg)
{
	return LineSegment<TDest, 1>(vector_cast<TDest, 1>(seg.start), vector_cast<TDest, 1>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
LineSegment<TDest, 2> line_segment_cast(LineSegment<TSource, 3> const& seg)
{
	return LineSegment<TDest, 2>(vector_cast<TDest, 2>(seg.start), vector_cast<TDest, 2>(seg.end));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
LineSegment<TDest, 3> line_segment_cast(LineSegment<TSource, 3> const& seg)
{
	return LineSegment<TDest, 3>(vector_type_cast<TDest>(seg.start), vector_type_cast<TDest>(seg.end));
}

END_LFRL_CG_NAMESPACE

#endif
