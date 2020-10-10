#ifndef __LFRL_CG_CORE_VECTOR_CAST_GUARD__
#define __LFRL_CG_CORE_VECTOR_CAST_GUARD__

#include "vector3.h"

BEGIN_LFRL_CG_NAMESPACE

template <u32 destDimensions, class T, u32 sourceDimensions>
Vector<T, destDimensions> vector_size_cast(Vector<T, sourceDimensions> const& vec)
{
	Vector<T, destDimensions> result;
	auto sz = LFRL::min(destDimensions, sourceDimensions);
	for (u32 i = 0; i < sz; ++i)
		result.SetScalar(i, vec.GetScalar(i));
	return result;
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 1> const& vec)
{
	return vec;
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 1> const& vec)
{
	return Vector<T, 2>(vec);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 1> const& vec)
{
	return Vector<T, 3>(vec);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 2> const& vec)
{
	return Vector<T, 1>(vec.x);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 2> const& vec)
{
	return vec;
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 2> const& vec)
{
	return Vector<T, 3>(vec);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 3> const& vec)
{
	return Vector<T, 1>(vec.x);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 3> const& vec)
{
	return Vector<T, 2>(vec.x, vec.y);
}

template <u32 destDimensions, class T, LFRL::requires<destDimensions == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 3> const& vec)
{
	return vec;
}

template <class TDest, class TSource, u32 dimensions, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, dimensions> vector_type_cast(Vector<TSource, dimensions> const& vec)
{
	Vector<TDest, dimensions> result;
	for (u32 i = 0; i < dimensions; ++i)
		result.SetScalar(i, static_cast<TDest>(vec.GetScalar(i)));
	return result;
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, 1> vector_type_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, 2> vector_type_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y));
}

template <class TDest, class TSource, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, 3> vector_type_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y), static_cast<TDest>(vec.z));
}

template <class TDest, u32 destDimensions, class TSource, u32 sourceDimensions, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, destDimensions> vector_cast(Vector<TSource, sourceDimensions> const& vec)
{
	Vector<TDest, destDimensions> result;
	auto sz = LFRL::min(destDimensions, sourceDimensions);
	for (u32 i = 0; i < sz; ++i)
		result.SetScalar(i, static_cast<TDest>(vec.GetScalar(i)));
	return result;
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), TDest());
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), TDest(), TDest());
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y), TDest());
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y));
}

template <class TDest, u32 destDimensions, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destDimensions == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y), static_cast<TDest>(vec.z));
}

END_LFRL_CG_NAMESPACE

#endif
