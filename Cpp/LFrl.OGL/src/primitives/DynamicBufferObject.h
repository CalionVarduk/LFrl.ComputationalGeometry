#ifndef __LFRL_OGL_DYNAMIC_BUFFER_OBJECT_GUARD__
#define __LFRL_OGL_DYNAMIC_BUFFER_OBJECT_GUARD__

#include "BufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

enum struct DynamicBufferObjectActionResult
{
	OK = 0,
	RESIZE_BUFFER_INITIALIZATION_FAILURE = 1,
	RESIZE_TRIVIAL_DATA_COPY_FAILURE = 2,
	RESIZE_CRITICAL_DATA_COPY_FAILURE = 3
};

template <class T>
struct DynamicBufferObject final
{
	typedef T type;
	static constexpr GLuint MIN_CAPACITY = 16U;
	static constexpr GLuint GROWTH_COEFFICIENT = 2U;
	static constexpr GLuint OBJECT_SIZE = static_cast<GLuint>(sizeof(T));

	DynamicBufferObject(DynamicBufferObject<T> const&) = delete;
	DynamicBufferObject<T>& operator=(DynamicBufferObject<T> const&) = delete;

	DynamicBufferObject() noexcept;
	explicit DynamicBufferObject(BufferObject::Target target) noexcept;
	DynamicBufferObject(BufferObject::Target target, BufferObject::Usage usage) noexcept;
	DynamicBufferObject(DynamicBufferObject<T>&&) noexcept;
	DynamicBufferObject<T>& operator=(DynamicBufferObject<T>&&) noexcept;
	~DynamicBufferObject() { Dispose(); }

	GLuint GetSize() const noexcept { return _size; }
	GLuint GetCapacity() const noexcept { return _capacity; }
	GLuint GetId() const noexcept { return _bo.GetId(); }
	ObjectState GetState() const noexcept { return _bo.GetState(); }
	
	BufferObject& GetUnderlyingObject() noexcept { return _bo; }
	BufferObject const& GetUnderlyingObject() const noexcept { return _bo; }

	BufferObject::ActionResult Initalize();

	void Bind() { _bo.Bind(); }
	void Unbind() { _bo.Unbind(); }

	DynamicBufferObjectActionResult Push(T const& obj);
	DynamicBufferObjectActionResult PushRange(array_ptr<const T> objs);
	DynamicBufferObjectActionResult PushRange(array_ptr<T> objs) { return PushRange(objs.to_const()); }

	GLuint Pop(GLuint count = 1);

	void Replace(GLuint index, T const& obj);
	GLuint ReplaceRange(GLuint index, array_ptr<const T> objs);
	GLuint ReplaceRange(GLuint index, array_ptr<T> objs) { return ReplaceRange(index, objs.to_const()); }

	bool Swap(GLuint index1, GLuint index2);

	void Clear();
	void Set(array_ptr<const T> objs);
	void Set(array_ptr<T> objs) { Set(objs.to_const()); }
	DynamicBufferObjectActionResult Reserve(GLuint minCapacity);
	DynamicBufferObjectActionResult ShrinkToFit();

	BufferObject::ActionResult Dispose();

private:
	GLuint _size;
	GLuint _capacity;
	BufferObject _bo;

	DynamicBufferObjectActionResult _ResizeBegin(GLuint capacity);
	void _ResizeEnd();
};

template <class T>
DynamicBufferObject<T>::DynamicBufferObject() noexcept
	: _size(0), _capacity(0), _bo(BufferObject::Target::ARRAY_BUFFER, BufferObject::Usage::DYNAMIC_DRAW)
{}

template <class T>
DynamicBufferObject<T>::DynamicBufferObject(BufferObject::Target target) noexcept
	: _size(0), _capacity(0), _bo(target, BufferObject::Usage::DYNAMIC_DRAW)
{}

template <class T>
DynamicBufferObject<T>::DynamicBufferObject(BufferObject::Target target, BufferObject::Usage usage) noexcept
	: _size(0), _capacity(0), _bo(target, usage)
{}

template <class T>
DynamicBufferObject<T>::DynamicBufferObject(DynamicBufferObject<T>&& other) noexcept
	: _size(0), _capacity(0), _bo()
{
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
	std::swap(_bo, other._bo);
}

template <class T>
DynamicBufferObject<T>& DynamicBufferObject<T>::operator= (DynamicBufferObject<T>&& other) noexcept
{
	if (this != &other)
	{
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_bo, other._bo);
	}
	return *this;
}

template <class T>
BufferObject::ActionResult DynamicBufferObject<T>::Initalize()
{
	auto result = _bo.Initialize();
	if (result == BufferObject::ActionResult::OK)
	{
		_size = 0;
		_capacity = 0;
	}
	return result;
}

template <class T>
DynamicBufferObjectActionResult DynamicBufferObject<T>::Push(T const& obj)
{
	if (_size == _capacity)
	{
		auto result = _ResizeBegin(_capacity * GROWTH_COEFFICIENT);

		if (result == DynamicBufferObjectActionResult::OK)
			_bo.SetSubData(_size++, obj);

		_ResizeEnd();
		return result;
	}

	_bo.SetSubData(_size++, obj);
	return DynamicBufferObjectActionResult::OK;
}

template <class T>
DynamicBufferObjectActionResult DynamicBufferObject<T>::PushRange(array_ptr<const T> objs)
{
	if (objs.size() == 0)
		return DynamicBufferObjectActionResult::OK;

	auto newSize = _size + objs.size();
	if (newSize > _capacity)
	{
		auto capacity = _capacity;
		while (newSize > capacity)
			capacity *= GROWTH_COEFFICIENT;

		auto result = _ResizeBegin(capacity);

		if (result == DynamicBufferObjectActionResult::OK)
		{
			_bo.SetSubData(_size, objs);
			_size = newSize;
		}
		_ResizeEnd();
		return result;
	}

	_bo.SetSubData(_size, objs);
	_size = newSize;
	return DynamicBufferObjectActionResult::OK;
}

template <class T>
GLuint DynamicBufferObject<T>::Pop(GLuint count)
{
	if (count > _size)
		count = _size;

	_size -= count;
	return count;
}

template <class T>
void DynamicBufferObject<T>::Replace(GLuint index, T const& obj)
{
	assert(index < _size);
	_bo.SetSubData(index, obj);
}

template <class T>
GLuint DynamicBufferObject<T>::ReplaceRange(GLuint index, array_ptr<const T> objs)
{
	assert(index < _size);

	auto endIndex = index + objs.size();
	if (endIndex > _size)
		endIndex = _size;

	auto replaceCount = endIndex - index;
	if (replaceCount > 0)
		_bo.SetSubData(index, objs);

	return replaceCount;
}

template <class T>
bool DynamicBufferObject<T>::Swap(GLuint index1, GLuint index2)
{
	assert(index1 < _size);
	assert(index2 < _size);
	if (index1 == index2)
		return;

	auto offset1 = OBJECT_SIZE * index1;
	auto offset2 = OBJECT_SIZE * index2;

	auto ptr = _bo.MapRange(offset1, OBJECT_SIZE, AccessFlag::READ);
	if (ptr == nullptr)
		return false;

	char buffer[OBJECT_SIZE];
	memcpy(buffer, ptr, OBJECT_SIZE);
	_bo.Unmap();

	ptr = _bo.MapRange(offset2, OBJECT_SIZE, AccessFlag::READ);
	if (ptr == nullptr)
		return false;

	_bo.SetSubData(offset1, OBJECT_SIZE, ptr);
	_bo.Unmap();

	_bo.SetSubData(offset2, OBJECT_SIZE, static_cast<void*>(buffer));
	return true;
}

template <class T>
void DynamicBufferObject<T>::Clear()
{
	_size = 0;
	_capacity = MIN_CAPACITY;
	_bo.Reserve(_capacity);
}

template <class T>
void DynamicBufferObject<T>::Set(array_ptr<const T> objs)
{
	_size = objs.size();
	if (_size == 0)
		return;

	if (_size > _capacity)
	{
		auto capacity = _capacity;
		while (_size > capacity)
			capacity *= GROWTH_COEFFICIENT;

		_capacity = capacity;
		_bo.Reserve(_capacity);
	}
	_bo.SetSubData(0, objs);
}

template <class T>
DynamicBufferObjectActionResult DynamicBufferObject<T>::Reserve(GLuint minCapacity)
{
	auto capacity = MIN_CAPACITY;
	while (minCapacity > capacity)
		capacity *= GROWTH_COEFFICIENT;

	if (_capacity >= capacity)
		return DynamicBufferObjectActionResult::OK;

	if (_size == 0)
	{
		_capacity = capacity;
		_bo.Reserve(_capacity);
		return DynamicBufferObjectActionResult::OK;
	}

	auto result = _ResizeBegin(capacity);
	_ResizeEnd();
	return result;
}

template <class T>
DynamicBufferObjectActionResult DynamicBufferObject<T>::ShrinkToFit()
{
	auto capacity = _capacity;
	auto minCapacity = std::max(_size, MIN_CAPACITY);

	while (capacity > minCapacity)
		capacity /= GROWTH_COEFFICIENT;

	if (capacity < _size)
		capacity *= GROWTH_COEFFICIENT;

	if (capacity == _capacity)
		return DynamicBufferObjectActionResult::OK;

	auto result = _ResizeBegin(capacity);
	_ResizeEnd();
	return result;
}

template <class T>
BufferObject::ActionResult DynamicBufferObject<T>::Dispose()
{
	auto result = _bo.Dispose();
	if (result == BufferObject::ActionResult::OK)
	{
		_size = 0;
		_capacity = 0;
	}
	return result;
}

template <class T>
DynamicBufferObjectActionResult DynamicBufferObject<T>::_ResizeBegin(GLuint capacity)
{
	BufferObject tempBo(BufferObject::Target::COPY_WRITE_BUFFER, BufferObject::Usage::STATIC_COPY);
	if (tempBo.Initialize() != BufferObject::ActionResult::OK)
		return DynamicBufferObjectActionResult::RESIZE_BUFFER_INITIALIZATION_FAILURE;

	auto usedCapacity = OBJECT_SIZE * _size;

	tempBo.Bind();
	BufferObject::Bind(BufferObject::Target::COPY_READ_BUFFER, _bo.GetId());

	tempBo.Reserve(usedCapacity);
	if (!tempBo.CopySubData(_bo, 0, 0, usedCapacity))
	{
		tempBo.Unbind();
		return DynamicBufferObjectActionResult::RESIZE_TRIVIAL_DATA_COPY_FAILURE;
	}

	tempBo.SetTarget(BufferObject::Target::COPY_READ_BUFFER);

	tempBo.Bind();
	BufferObject::Bind(BufferObject::Target::COPY_WRITE_BUFFER, _bo.GetId());

	_capacity = capacity;
	_bo.Reserve(_capacity);

	auto result = _bo.CopySubData(tempBo, 0, 0, usedCapacity) ?
		DynamicBufferObjectActionResult::OK :
		DynamicBufferObjectActionResult::RESIZE_CRITICAL_DATA_COPY_FAILURE;

	tempBo.Unbind();
	return result;
}

template <class T>
void DynamicBufferObject<T>::_ResizeEnd()
{
	BufferObject::Unbind(BufferObject::Target::COPY_WRITE_BUFFER);
}

END_LFRL_OGL_NAMESPACE

#endif
