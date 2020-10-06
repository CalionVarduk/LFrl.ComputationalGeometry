#ifndef __LFRL_CG_CORE_VECTOR_CAST_GUARD__
#define __LFRL_CG_CORE_VECTOR_CAST_GUARD__

#include "vector3.h"

BEGIN_LFRL_CG_NAMESPACE

template <u32 destSize, class T, u32 sourceSize>
Vector<T, destSize> vector_size_cast(Vector<T, sourceSize> const& vec)
{
	Vector<T, destSize> result;
	auto sz = LFRL::min(destSize, sourceSize);
	for (u32 i = 0; i < sz; ++i)
		result.SetScalar(i, vec.GetScalar(i));
	return result;
}

template <u32 destSize, class T, LFRL::requires<destSize == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 1> const& vec)
{
	return vec;
}

template <u32 destSize, class T, LFRL::requires<destSize == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 1> const& vec)
{
	return Vector<T, 2>(vec);
}

template <u32 destSize, class T, LFRL::requires<destSize == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 1> const& vec)
{
	return Vector<T, 3>(vec);
}

template <u32 destSize, class T, LFRL::requires<destSize == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 2> const& vec)
{
	return Vector<T, 1>(vec.x);
}

template <u32 destSize, class T, LFRL::requires<destSize == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 2> const& vec)
{
	return vec;
}

template <u32 destSize, class T, LFRL::requires<destSize == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 2> const& vec)
{
	return Vector<T, 3>(vec);
}

template <u32 destSize, class T, LFRL::requires<destSize == 1U> = 0>
Vector<T, 1> vector_size_cast(Vector<T, 3> const& vec)
{
	return Vector<T, 1>(vec.x);
}

template <u32 destSize, class T, LFRL::requires<destSize == 2U> = 0>
Vector<T, 2> vector_size_cast(Vector<T, 3> const& vec)
{
	return Vector<T, 2>(vec.x, vec.y);
}

template <u32 destSize, class T, LFRL::requires<destSize == 3U> = 0>
Vector<T, 3> vector_size_cast(Vector<T, 3> const& vec)
{
	return vec;
}

template <class TDest, class TSource, u32 size, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, size> vector_type_cast(Vector<TSource, size> const& vec)
{
	Vector<TDest, size> result;
	for (u32 i = 0; i < size; ++i)
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

template <class TDest, u32 destSize, class TSource, u32 sourceSize, LFRL::requires<std::is_convertible<TSource, TDest>::value> = 0>
Vector<TDest, destSize> vector_cast(Vector<TSource, sourceSize> const& vec)
{
	Vector<TDest, destSize> result;
	auto sz = LFRL::min(destSize, sourceSize);
	for (u32 i = 0; i < sz; ++i)
		result.SetScalar(i, static_cast<TDest>(vec.GetScalar(i)));
	return result;
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), TDest());
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 1> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), TDest(), TDest());
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y));
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 2> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y), TDest());
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 1U> = 0>
Vector<TDest, 1> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 1>(static_cast<TDest>(vec.x));
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 2U> = 0>
Vector<TDest, 2> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 2>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y));
}

template <class TDest, u32 destSize, class TSource, LFRL::requires_all<std::is_convertible<TSource, TDest>::value, destSize == 3U> = 0>
Vector<TDest, 3> vector_cast(Vector<TSource, 3> const& vec)
{
	return Vector<TDest, 3>(static_cast<TDest>(vec.x), static_cast<TDest>(vec.y), static_cast<TDest>(vec.z));
}

END_LFRL_CG_NAMESPACE

#endif
