#ifndef __LFRL_OGL_BUFFER_OBJECT_GUARD__
#define __LFRL_OGL_BUFFER_OBJECT_GUARD__

#include <array>
#include "LFrl.Common/src/memory/array_ptr.h"
#include "LFrl.Common/src/utils/requires.h"
#include "LFrl.Common/src/utils/is_iterable.h"
#include "LFrl.Common/src/utils/dynamic_buffer.h"
#include "AccessType.h"
#include "AccessFlag.h"
#include "../ObjectState.h"

BEGIN_LFRL_OGL_NAMESPACE

struct BufferObject final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		BUFFER_GEN_FAILURE = 2,
		ALREADY_DISPOSED = 3,
		NOT_READY = 4
	};

	enum struct Target
	{
		UNDEFINED = 0,
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
		COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
		COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
		DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
		QUERY_BUFFER = GL_QUERY_BUFFER,
		SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
		TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM_BUFFER = GL_UNIFORM_BUFFER
	};

	enum struct Binding
	{
		UNDEFINED = 0,
		ARRAY_BUFFER = GL_ARRAY_BUFFER_BINDING,
		ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER_BINDING,
		COPY_READ_BUFFER = GL_COPY_READ_BUFFER_BINDING,
		COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER_BINDING,
		DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER_BINDING,
		DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER_BINDING,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER_BINDING,
		PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER_BINDING,
		PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER_BINDING,
		SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER_BINDING,
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
		UNIFORM_BUFFER = GL_UNIFORM_BUFFER_BINDING
	};

	enum struct Usage
	{
		UNDEFINED = 0,
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

	static void Bind(Target target, GLuint id);
	static void Unbind(Target target) { Bind(target, NULL); }
	static GLuint GetBoundId(Binding binding);
	static bool IsAnyBound(Binding binding) { return GetBoundId(binding) != NULL; }
	static void SetData(Target target, GLuint size, void const* data, Usage usage);
	static void SetSubData(Target target, GLint offset, GLuint size, void const* data);
	static bool CopySubData(Target source, Target destination, GLint readOffset, GLint writeOffset, GLuint size);
	static void* Map(Target target, AccessType access);
	static void* MapRange(Target target, GLint offset, GLuint size, GLbitfield access);
	static void* MapRange(Target target, GLint offset, GLuint size, AccessFlag access) { return MapRange(target, offset, size, static_cast<GLbitfield>(access)); }
	static void FlushMappedRange(Target target, GLint offset, GLuint size);
	static bool Unmap(Target target);
	
	template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, BufferObject*>::value> = 0>
	static void InitializeRange(TIterable const& iterable);

	template <GLuint count, LFRL::requires<!(count <= 0)> = 0>
	static void InitializeRange(std::array<BufferObject*, count>& buffers);

	template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, BufferObject*>::value> = 0>
	static void DisposeRange(TIterable const& iterable);

	template <GLuint count, LFRL::requires<!(count <= 0)> = 0>
	static void DisposeRange(std::array<BufferObject*, count>& buffers);

	template <class T>
	static void SetData(Target target, array_ptr<const T> data, Usage usage) { SetData(target, static_cast<GLuint>(data.size() * sizeof(T)), data.begin(), usage); }

	template <class T>
	static void SetData(Target target, array_ptr<T> data, Usage usage) { SetData(target, data.to_const(), usage); }

	template <class T>
	static void SetData(Target target, T const& data, Usage usage) { SetData(target, static_cast<GLuint>(sizeof(T)), &data, usage); }

	template <class T>
	static void SetSubData(Target target, GLint index, array_ptr<const T> data) { SetSubData(target, static_cast<GLint>(index * sizeof(T)), static_cast<GLuint>(data.size() * sizeof(T)), data.begin()); }

	template <class T>
	static void SetSubData(Target target, GLint index, array_ptr<T> data) { SetSubData(target, index, data.to_const()); }

	template <class T>
	static void SetSubData(Target target, GLint index, T const& data) { SetSubData(target, static_cast<GLint>(index * sizeof(T)), static_cast<GLuint>(sizeof(T)), &data); }

	BufferObject(BufferObject const&) = delete;
	BufferObject& operator=(BufferObject const&) = delete;

	BufferObject() noexcept;
	explicit BufferObject(Target target) noexcept;
	BufferObject(Target target, Usage usage) noexcept;
	BufferObject(BufferObject&&) noexcept;
	BufferObject& operator=(BufferObject&&) noexcept;
	~BufferObject() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	ObjectState GetState() const noexcept { return _state; }

	Target GetTarget() const noexcept { return _target; }
	void SetTarget(Target value) noexcept { _target = value; }

	Usage GetUsage() const noexcept { return _usage; }
	void SetUsage(Usage value) noexcept { _usage = value; }

	ActionResult Initialize();

	void Bind() { Bind(_target, _id); }
	void Unbind() { Unbind(_target); }
	bool IsBoundAs(Binding binding) const { return GetBoundId(binding) == _id; }

	void SetData(GLuint size, void const* data) { SetData(_target, size, data, _usage); }
	void Reserve(GLuint size) { SetData(size, NULL); }
	void SetSubData(GLint offset, GLuint size, void const* data) { SetSubData(_target, offset, size, data); }
	bool CopySubData(BufferObject const& source, GLint readOffset, GLint writeOffset, GLuint size) { return CopySubData(source._target, _target, readOffset, writeOffset, size); }
	void* Map(AccessType access) { return Map(_target, access); }
	void* MapRange(GLint offset, GLuint size, GLbitfield access) { return MapRange(_target, offset, size, access); }
	void* MapRange(GLint offset, GLuint size, AccessFlag access) { return MapRange(_target, offset, size, access); }
	void FlushMappedRange(GLint offset, GLuint size) { FlushMappedRange(_target, offset, size); }
	bool Unmap() { return Unmap(_target); }

	template <class T>
	void SetData(array_ptr<const T> data) { SetData<T>(_target, data, _usage); }

	template <class T>
	void SetData(array_ptr<T> data) { SetData<T>(_target, data, _usage); }

	template <class T>
	void SetData(T const& data) { SetData<T>(_target, data, _usage); }

	template <class T>
	void SetSubData(GLint index, array_ptr<const T> data) { SetSubData<T>(_target, index, data); }

	template <class T>
	void SetSubData(GLint index, array_ptr<T> data) { SetSubData<T>(_target, index, data); }

	template <class T>
	void SetSubData(GLint index, T const& data) { SetSubData<T>(_target, index, data); }

	ActionResult Dispose();

private:
	GLuint _id;
	Target _target;
	Usage _usage;
	ObjectState _state;
};

template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, BufferObject*>::value>>
void BufferObject::InitializeRange(TIterable const& iterable)
{
	auto count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current)
		++count;

	if (count <= 0)
		return;

	LFRL::dynamic_buffer<GLuint> ids(count);
	glGenBuffers(count, ids.data());

	count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current, ++count)
	{
		current->_id = ids[count];
		current->_state = current->_id == 0 ? ObjectState::INIT_FAILURE : ObjectState::READY;
	}
}

template <GLuint count, LFRL::requires<!(count <= 0)>>
void BufferObject::InitializeRange(std::array<BufferObject*, count>& buffers)
{
	std::array<GLuint, count> ids;
	glGenBuffers(count, ids.data());

	for (GLsizei i = 0; i < count; ++i)
	{
		buffers[i]->_id = ids[i];
		buffers[i]->_state = buffers[i]->_id == 0 ? ObjectState::INIT_FAILURE : ObjectState::READY;
	}
}

template <class TIterable, LFRL::requires<LFRL::is_iterable_of<TIterable, BufferObject*>::value>>
void BufferObject::DisposeRange(TIterable const& iterable)
{
	auto count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current)
		++count;

	if (count <= 0)
		return;

	LFRL::dynamic_buffer<GLuint> ids(count);

	count = 0;
	for (auto current = iterable.begin(); current != iterable.end(); ++current, ++count)
	{
		ids[count] = current->_id;
		current->_id = 0;
		current->_state = ObjectState::DISPOSED;
	}
	glDeleteBuffers(ids.size(), ids.data());
}

template <GLuint count, LFRL::requires<!(count <= 0)>>
void BufferObject::DisposeRange(std::array<BufferObject*, count>& buffers)
{
	std::array<GLuint, count> ids;

	for (GLsizei i = 0; i < count; ++i)
	{
		ids[i] = buffers[i]->_id;
		buffers[i]->_id = 0;
		buffers[i]->_state = ObjectState::DISPOSED;
	}
	glDeleteBuffers(count, ids.data());
}

END_LFRL_OGL_NAMESPACE

#endif
