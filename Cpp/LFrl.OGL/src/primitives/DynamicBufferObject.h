#ifndef __LFRL_OGL_DYNAMIC_BUFFER_OBJECT_GUARD__
#define __LFRL_OGL_DYNAMIC_BUFFER_OBJECT_GUARD__

#include "LFrl.Common/src/memory/array_ptr.h"
#include "BufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

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

	bool Push(T const& obj);
	GLuint PushRange(array_ptr<const T> objs);
	GLuint PushRange(array_ptr<T> objs) { return PushRange(objs.to_const()); }

	template <sz size>
	GLuint PushRange(std::array<T, size> const& objs) { return PushRange(make_array_ptr(objs.data(), size)); }

	GLuint Pop(GLuint count = 1);

	void Replace(GLuint index, T const& obj);
	GLuint ReplaceRange(GLuint index, array_ptr<const T> objs);
	GLuint ReplaceRange(GLuint index, array_ptr<T> objs) { return ReplaceRange(index, objs.to_const()); }
	
	template <sz size>
	GLuint ReplaceRange(GLuint index, std::array<T, size> const& objs) { return ReplaceRange(index, make_array_ptr(objs.data(), size)); }

	void Swap(GLuint index1, GLuint index2);

	void Clear();
	bool Reserve(GLuint minCapacity);

	BufferObject::ActionResult Dispose();

private:
	GLuint _size;
	GLuint _capacity;
	BufferObject _bo;

	bool _Resize(GLuint capacity);
};

template <class T>
DynamicBufferObject<T>::DynamicBufferObject() noexcept
	: _size(0), _capacity(0), _bo()
{}

template <class T>
DynamicBufferObject<T>::DynamicBufferObject(BufferObject::Target target) noexcept
	: _size(0), _capacity(0), _bo(target)
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
bool DynamicBufferObject<T>::Push(T const& obj)
{
	if (_size == _capacity)
	{
		auto target = _bo.GetTarget();
		auto result = _Resize(_capacity * GROWTH_COEFFICIENT);

		if (result)
			_bo.SetSubData(OBJECT_SIZE * _size++, obj);

		_bo.Unbind();
		_bo.SetTarget(target);
		return result;
	}

	_bo.SetSubData(OBJECT_SIZE * _size++, obj);
	return true;
}

template <class T>
GLuint DynamicBufferObject<T>::PushRange(array_ptr<const T> objs)
{
	if (objs.size() == 0)
		return 0;

	auto newSize = _size + objs.size();
	if (newSize > _capacity)
	{
		auto capacity = _capacity;
		while (newSize > capacity)
			capacity *= GROWTH_COEFFICIENT;

		auto target = _bo.GetTarget();
		auto result = _Resize(capacity);

		if (result)
		{
			_bo.SetSubData(OBJECT_SIZE * _size, OBJECT_SIZE * objs.size(), static_cast<void*>(objs.begin()));
			_size = newSize;
		}
		_bo.Unbind();
		_bo.SetTarget(target);
		return result ? objs.size() : 0;
	}

	_bo.SetSubData(OBJECT_SIZE * _size, OBJECT_SIZE * objs.size(), static_cast<void*>(objs.begin()));
	_size = newSize;
	return objs.size();
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
	auto offset = OBJECT_SIZE * index;
	_bo.SetSubData(offset, obj);
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
		_bo.SetSubData(OBJECT_SIZE * index, OBJECT_SIZE * replaceCount, static_cast<void*>(objs.begin()));

	return replaceCount;
}

template <class T>
void DynamicBufferObject<T>::Swap(GLuint index1, GLuint index2)
{
	assert(index1 < _size);
	assert(index2 < _size);
	if (index1 == index2)
		return;

	auto offset1 = OBJECT_SIZE * index1;
	auto offset2 = OBJECT_SIZE * index2;

	char buffer[OBJECT_SIZE];
	memcpy(buffer, _bo.MapRange(offset1, OBJECT_SIZE, AccessFlag::READ), OBJECT_SIZE);
	_bo.Unmap();
	_bo.SetSubData(offset1, OBJECT_SIZE, _bo.MapRange(offset2, OBJECT_SIZE, AccessFlag::READ));
	_bo.Unmap();
	_bo.SetSubData(offset2, OBJECT_SIZE, static_cast<void*>(buffer));
}

template <class T>
void DynamicBufferObject<T>::Clear()
{
	_size = 0;
	_capacity = MIN_CAPACITY;
	_bo.Reserve(_capacity);
}

template <class T>
bool DynamicBufferObject<T>::Reserve(GLuint minCapacity)
{
	auto capacity = MIN_CAPACITY;
	while (minCapacity > capacity)
		capacity *= GROWTH_COEFFICIENT;

	if (_capacity >= capacity)
		return true;

	if (_size == 0)
	{
		_capacity = capacity;
		_bo.Reserve(_capacity);
		return true;
	}

	auto target = _bo.GetTarget();
	auto result = _Resize(capacity);
	_bo.Unbind();
	_bo.SetTarget(target);
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
bool DynamicBufferObject<T>::_Resize(GLuint capacity)
{
	BufferObject tempBo(BufferObject::Target::COPY_WRITE_BUFFER, _bo.GetUsage());
	if (tempBo.Initialize() != BufferObject::ActionResult::OK)
		return false;

	auto usedCapacity = OBJECT_SIZE * _size;

	_bo.SetTarget(BufferObject::Target::COPY_READ_BUFFER);
	tempBo.Bind();
	_bo.Bind();

	tempBo.Reserve(usedCapacity);
	if (!tempBo.CopySubData(_bo, 0, 0, usedCapacity))
	{
		tempBo.Unbind();
		return false;
	}

	tempBo.SetTarget(BufferObject::Target::COPY_READ_BUFFER);
	_bo.SetTarget(BufferObject::Target::COPY_WRITE_BUFFER);

	tempBo.Bind();
	_bo.Bind();

	_capacity = capacity;
	_bo.Reserve(_capacity);

	auto result = _bo.CopySubData(tempBo, 0, 0, usedCapacity);
	// false result here is really bad, since we've already reserved a new memory block
	// there is no easy way to fix this, it might be possible to move tempBo into _bo, although it's capacity is potentially incorrect
	tempBo.Unbind();
	return result;
}

END_LFRL_OGL_NAMESPACE

#endif
