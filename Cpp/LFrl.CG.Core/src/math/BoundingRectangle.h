#ifndef __LFRL_CG_CORE_BOUNDING_RECTANGLE_GUARD__
#define __LFRL_CG_CORE_BOUNDING_RECTANGLE_GUARD__

#include "LineSegment2.h"

BEGIN_LFRL_CG_NAMESPACE

template <class T>
struct BoundingRectangle
{
	typedef T type;

	static BoundingRectangle<T> Incr(BoundingRectangle<T> const& rect) { return BoundingRectangle<T>(rect).Incr(); }
	static BoundingRectangle<T> Decr(BoundingRectangle<T> const& rect) { return BoundingRectangle<T>(rect).Decr(); }
	static BoundingRectangle<T> Add(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>(rect).Add(vec); }
	static BoundingRectangle<T> Sub(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>(rect).Sub(vec); }
	static BoundingRectangle<T> Mult(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>(rect).Mult(vec); }
	static BoundingRectangle<T> Div(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>(rect).Div(vec); }
	static BoundingRectangle<T> Mod(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>(rect).Mod(vec); }

	Vector<T, 2> bottomLeft;
	Vector<T, 2> topRight;

	BoundingRectangle();
	BoundingRectangle(BoundingRectangle<T> const& rect) = default;
	BoundingRectangle(BoundingRectangle<T>&& rect);
	BoundingRectangle(Vector<T, 2> const& bottomLeft, Vector<T, 2> const& topRight);

	explicit BoundingRectangle(LineSegment<T, 2> const& seg);

	Vector<T, 2> GetSize() const { return topRight - bottomLeft; }
	BoundingRectangle<T>& SetSize(Vector<T, 2> const& value);

	bool Equals(BoundingRectangle<T> const& rect) const { return bottomLeft.Equals(rect.bottomLeft) && topRight.Equals(rect.topRight); }
	bool Contains(BoundingRectangle<T> const& rect) const;
	bool Intersects(BoundingRectangle<T> const& rect) const;

	BoundingRectangle<T>& Incr();
	BoundingRectangle<T>& Decr();
	BoundingRectangle<T>& Add(Vector<T, 2> const& vec);
	BoundingRectangle<T>& Sub(Vector<T, 2> const& vec);
	BoundingRectangle<T>& Mult(Vector<T, 2> const& vec);
	BoundingRectangle<T>& Div(Vector<T, 2> const& vec);
	BoundingRectangle<T>& Mod(Vector<T, 2> const& vec);

	BoundingRectangle<T>& operator++() { return Incr(); }
	BoundingRectangle<T>& operator--() { return Decr(); }
	BoundingRectangle<T> operator++(int);
	BoundingRectangle<T> operator--(int);

	BoundingRectangle<T>& operator=(BoundingRectangle<T> const& rect) = default;
	BoundingRectangle<T>& operator=(BoundingRectangle<T>&& rect);
	BoundingRectangle<T>& operator+=(Vector<T, 2> const& vec) { return Add(vec); }
	BoundingRectangle<T>& operator-=(Vector<T, 2> const& vec) { return Sub(vec); }
	BoundingRectangle<T>& operator*=(Vector<T, 2> const& vec) { return Mult(vec); }
	BoundingRectangle<T>& operator/=(Vector<T, 2> const& vec) { return Div(vec); }
	BoundingRectangle<T>& operator%=(Vector<T, 2> const& vec) { return Mod(vec); }

	bool operator==(BoundingRectangle<T> const& rect) const { return Equals(rect); }
	bool operator!=(BoundingRectangle<T> const& rect) const { return !Equals(rect); }
};

template <class T>
BoundingRectangle<T>::BoundingRectangle()
	: bottomLeft(), topRight()
{}

template <class T>
BoundingRectangle<T>::BoundingRectangle(BoundingRectangle<T>&& rect)
	: bottomLeft(std::move(rect.bottomLeft)), topRight(std::move(rect.topRight))
{}

template <class T>
BoundingRectangle<T>::BoundingRectangle(Vector<T, 2> const& bottomLeft, Vector<T, 2> const& topRight)
	: bottomLeft(bottomLeft), topRight(topRight)
{}

template <class T>
BoundingRectangle<T>::BoundingRectangle(LineSegment<T, 2> const& seg)
	: bottomLeft(), topRight()
{
	if (seg.start.x < seg.end.x)
	{
		bottomLeft.x = seg.start.x;
		topRight.x = seg.end.x;
	}
	else
	{
		bottomLeft.x = seg.end.x;
		topRight.x = seg.start.x;
	}
	if (seg.start.y < seg.end.y)
	{
		bottomLeft.y = seg.start.y;
		topRight.y = seg.end.y;
	}
	else
	{
		bottomLeft.y = seg.end.y;
		topRight.y = seg.start.y;
	}
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::SetSize(Vector<T, 2> const& value)
{
	topRight = bottomLeft + value;
	return *this;
}

template <class T>
bool BoundingRectangle<T>::Contains(BoundingRectangle<T> const& rect) const
{
	return bottomLeft.x <= rect.bottomLeft.x &&
		rect.topRight.x <= topRight.x &&
		bottomLeft.y <= rect.bottomLeft.y &&
		rect.topRight.y <= topRight.y;
}

template <class T>
bool BoundingRectangle<T>::Intersects(BoundingRectangle<T> const& rect) const
{
	return bottomLeft.x <= rect.topRight.x &&
		rect.bottomLeft.x <= topRight.x &&
		bottomLeft.y <= rect.topRight.y &&
		rect.bottomLeft.y <= topRight.y;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Incr()
{
	bottomLeft.Incr();
	topRight.Incr();
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Decr()
{
	bottomLeft.Decr();
	topRight.Decr();
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Add(Vector<T, 2> const& vec)
{
	bottomLeft.Add(vec);
	topRight.Add(vec);
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Sub(Vector<T, 2> const& vec)
{
	bottomLeft.Sub(vec);
	topRight.Sub(vec);
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Mult(Vector<T, 2> const& vec)
{
	bottomLeft.Mult(vec);
	topRight.Mult(vec);
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Div(Vector<T, 2> const& vec)
{
	bottomLeft.Div(vec);
	topRight.Div(vec);
	return *this;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::Mod(Vector<T, 2> const& vec)
{
	bottomLeft.Mod(vec);
	topRight.Mod(vec);
	return *this;
}

template <class T>
BoundingRectangle<T> BoundingRectangle<T>::operator++(int)
{
	BoundingRectangle<T> result(*this);
	Incr();
	return result;
}

template <class T>
BoundingRectangle<T> BoundingRectangle<T>::operator--(int)
{
	BoundingRectangle<T> result(*this);
	Decr();
	return result;
}

template <class T>
BoundingRectangle<T>& BoundingRectangle<T>::operator=(BoundingRectangle<T>&& rect)
{
	if (this != &rect)
	{
		std::swap(bottomLeft, rect.bottomLeft);
		std::swap(topRight, rect.topRight);
	}
	return *this;
}

template <class T>
BoundingRectangle<T> operator+(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>::Add(vec); }

template <class T>
BoundingRectangle<T> operator-(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>::Sub(vec); }

template <class T>
BoundingRectangle<T> operator*(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>::Mult(vec); }

template <class T>
BoundingRectangle<T> operator/(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>::Div(vec); }

template <class T>
BoundingRectangle<T> operator%(BoundingRectangle<T> const& rect, Vector<T, 2> const& vec) { return BoundingRectangle<T>::Mod(vec); }

END_LFRL_CG_NAMESPACE

#endif
