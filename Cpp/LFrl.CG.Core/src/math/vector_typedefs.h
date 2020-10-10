#ifndef __LFRL_CG_CORE_VECTOR_TYPEDEFS_GUARD__
#define __LFRL_CG_CORE_VECTOR_TYPEDEFS_GUARD__

#include "vector_cast.h"

BEGIN_LFRL_CG_NAMESPACE

typedef Vector<bool, 1> Vec1B;
typedef Vector<bool, 2> Vec2B;
typedef Vector<bool, 3> Vec3B;
typedef Vector<LFRL::u8, 1> Vec1UC;
typedef Vector<LFRL::u8, 2> Vec2UC;
typedef Vector<LFRL::u8, 3> Vec3UC;
typedef Vector<LFRL::i8, 1> Vec1C;
typedef Vector<LFRL::i8, 2> Vec2C;
typedef Vector<LFRL::i8, 3> Vec3C;
typedef Vector<LFRL::u16, 1> Vec1US;
typedef Vector<LFRL::u16, 2> Vec2US;
typedef Vector<LFRL::u16, 3> Vec3US;
typedef Vector<LFRL::i16, 1> Vec1S;
typedef Vector<LFRL::i16, 2> Vec2S;
typedef Vector<LFRL::i16, 3> Vec3S;
typedef Vector<LFRL::u32, 1> Vec1UI;
typedef Vector<LFRL::u32, 2> Vec2UI;
typedef Vector<LFRL::u32, 3> Vec3UI;
typedef Vector<LFRL::i32, 1> Vec1I;
typedef Vector<LFRL::i32, 2> Vec2I;
typedef Vector<LFRL::i32, 3> Vec3I;
typedef Vector<LFRL::u64, 1> Vec1UL;
typedef Vector<LFRL::u64, 2> Vec2UL;
typedef Vector<LFRL::u64, 3> Vec3UL;
typedef Vector<LFRL::i64, 1> Vec1L;
typedef Vector<LFRL::i64, 2> Vec2L;
typedef Vector<LFRL::i64, 3> Vec3L;
typedef Vector<LFRL::f32, 1> Vec1F;
typedef Vector<LFRL::f32, 2> Vec2F;
typedef Vector<LFRL::f32, 3> Vec3F;
typedef Vector<LFRL::f64, 1> Vec1D;
typedef Vector<LFRL::f64, 2> Vec2D;
typedef Vector<LFRL::f64, 3> Vec3D;
typedef Vector<LFRL::LongDouble, 1> Vec1LD;
typedef Vector<LFRL::LongDouble, 2> Vec2LD;
typedef Vector<LFRL::LongDouble, 3> Vec3LD;

template <LFRL::u32 dimensions>
using VecB = Vector<bool, dimensions>;

template <LFRL::u32 dimensions>
using VecUC = Vector<LFRL::u8, dimensions>;

template <LFRL::u32 dimensions>
using VecC = Vector<LFRL::i8, dimensions>;

template <LFRL::u32 dimensions>
using VecUS = Vector<LFRL::u16, dimensions>;

template <LFRL::u32 dimensions>
using VecS = Vector<LFRL::i16, dimensions>;

template <LFRL::u32 dimensions>
using VecUI = Vector<LFRL::u32, dimensions>;

template <LFRL::u32 dimensions>
using VecI = Vector<LFRL::i32, dimensions>;

template <LFRL::u32 dimensions>
using VecUL = Vector<LFRL::u64, dimensions>;

template <LFRL::u32 dimensions>
using VecL = Vector<LFRL::i64, dimensions>;

template <LFRL::u32 dimensions>
using VecF = Vector<LFRL::f32, dimensions>;

template <LFRL::u32 dimensions>
using VecD = Vector<LFRL::f64, dimensions>;

template <LFRL::u32 dimensions>
using VecLD = Vector<LFRL::LongDouble, dimensions>;

END_LFRL_CG_NAMESPACE

#endif
