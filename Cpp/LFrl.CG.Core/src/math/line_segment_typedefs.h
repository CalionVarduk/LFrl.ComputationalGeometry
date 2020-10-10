#ifndef __LFRL_CG_CORE_LINE_SEGMENT_TYPEDEFS_GUARD__
#define __LFRL_CG_CORE_LINE_SEGMENT_TYPEDEFS_GUARD__

#include "line_segment_cast.h"

BEGIN_LFRL_CG_NAMESPACE

typedef LineSegment<bool, 1> Seg1B;
typedef LineSegment<bool, 2> Seg2B;
typedef LineSegment<bool, 3> Seg3B;
typedef LineSegment<LFRL::u8, 1> Seg1UC;
typedef LineSegment<LFRL::u8, 2> Seg2UC;
typedef LineSegment<LFRL::u8, 3> Seg3UC;
typedef LineSegment<LFRL::i8, 1> Seg1C;
typedef LineSegment<LFRL::i8, 2> Seg2C;
typedef LineSegment<LFRL::i8, 3> Seg3C;
typedef LineSegment<LFRL::u16, 1> Seg1US;
typedef LineSegment<LFRL::u16, 2> Seg2US;
typedef LineSegment<LFRL::u16, 3> Seg3US;
typedef LineSegment<LFRL::i16, 1> Seg1S;
typedef LineSegment<LFRL::i16, 2> Seg2S;
typedef LineSegment<LFRL::i16, 3> Seg3S;
typedef LineSegment<LFRL::u32, 1> Seg1UI;
typedef LineSegment<LFRL::u32, 2> Seg2UI;
typedef LineSegment<LFRL::u32, 3> Seg3UI;
typedef LineSegment<LFRL::i32, 1> Seg1I;
typedef LineSegment<LFRL::i32, 2> Seg2I;
typedef LineSegment<LFRL::i32, 3> Seg3I;
typedef LineSegment<LFRL::u64, 1> Seg1UL;
typedef LineSegment<LFRL::u64, 2> Seg2UL;
typedef LineSegment<LFRL::u64, 3> Seg3UL;
typedef LineSegment<LFRL::i64, 1> Seg1L;
typedef LineSegment<LFRL::i64, 2> Seg2L;
typedef LineSegment<LFRL::i64, 3> Seg3L;
typedef LineSegment<LFRL::f32, 1> Seg1F;
typedef LineSegment<LFRL::f32, 2> Seg2F;
typedef LineSegment<LFRL::f32, 3> Seg3F;
typedef LineSegment<LFRL::f64, 1> Seg1D;
typedef LineSegment<LFRL::f64, 2> Seg2D;
typedef LineSegment<LFRL::f64, 3> Seg3D;
typedef LineSegment<LFRL::LongDouble, 1> Seg1LD;
typedef LineSegment<LFRL::LongDouble, 2> Seg2LD;
typedef LineSegment<LFRL::LongDouble, 3> Seg3LD;

template <LFRL::u32 dimensions>
using SegB = LineSegment<bool, dimensions>;

template <LFRL::u32 dimensions>
using SegUC = LineSegment<LFRL::u8, dimensions>;

template <LFRL::u32 dimensions>
using SegC = LineSegment<LFRL::i8, dimensions>;

template <LFRL::u32 dimensions>
using SegUS = LineSegment<LFRL::u16, dimensions>;

template <LFRL::u32 dimensions>
using SegS = LineSegment<LFRL::i16, dimensions>;

template <LFRL::u32 dimensions>
using SegUI = LineSegment<LFRL::u32, dimensions>;

template <LFRL::u32 dimensions>
using SegI = LineSegment<LFRL::i32, dimensions>;

template <LFRL::u32 dimensions>
using SegUL = LineSegment<LFRL::u64, dimensions>;

template <LFRL::u32 dimensions>
using SegL = LineSegment<LFRL::i64, dimensions>;

template <LFRL::u32 dimensions>
using SegF = LineSegment<LFRL::f32, dimensions>;

template <LFRL::u32 dimensions>
using SegD = LineSegment<LFRL::f64, dimensions>;

template <LFRL::u32 dimensions>
using SegLD = LineSegment<LFRL::LongDouble, dimensions>;

END_LFRL_CG_NAMESPACE

#endif
