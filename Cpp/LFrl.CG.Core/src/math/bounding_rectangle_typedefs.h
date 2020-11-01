#ifndef __LFRL_CG_CORE_BOUNDING_RECTANGLE_TYPEDEFS_GUARD__
#define __LFRL_CG_CORE_BOUNDING_RECTANGLE_TYPEDEFS_GUARD__

#include "bounding_rectangle_cast.h"

BEGIN_LFRL_CG_NAMESPACE

typedef BoundingRectangle<bool> RectB;
typedef BoundingRectangle<LFRL::u8> RectUC;
typedef BoundingRectangle<LFRL::i8> RectC;
typedef BoundingRectangle<LFRL::u16> RectUS;
typedef BoundingRectangle<LFRL::i16> RectS;
typedef BoundingRectangle<LFRL::u32> RectUI;
typedef BoundingRectangle<LFRL::i32> RectI;
typedef BoundingRectangle<LFRL::u64> RectUL;
typedef BoundingRectangle<LFRL::i64> RectL;
typedef BoundingRectangle<LFRL::f32> RectF;
typedef BoundingRectangle<LFRL::f64> RectD;
typedef BoundingRectangle<LFRL::LongDouble> RectLD;

END_LFRL_CG_NAMESPACE

#endif
