#include "vertex_buffer_object_range_mapper.h"

BEGIN_LFRL_OGL_NAMESPACE

void __init_buffer_range_mapper(VertexBufferObject::Target target, GLint offset, GLuint size, GLbitfield access, void*& ptr)
{
	ptr = VertexBufferObject::MapRange(target, offset, size, access);
}

vertex_buffer_object_range_mapper::vertex_buffer_object_range_mapper() noexcept
	: _ptr(nullptr), _target(VertexBufferObject::Target::UNDEFINED), _offset(0), _size(0), _access(0)
{}

vertex_buffer_object_range_mapper::vertex_buffer_object_range_mapper(VertexBufferObject::Target target, GLint offset, GLuint size, GLbitfield access)
	: _ptr(nullptr), _target(target), _offset(offset), _size(size), _access(access)
{
	__init_buffer_range_mapper(_target, _offset, _size, _access, _ptr);
}

vertex_buffer_object_range_mapper::vertex_buffer_object_range_mapper(VertexBufferObject const& obj, GLint offset, GLuint size, GLbitfield access)
	: _ptr(nullptr), _target(obj.GetTarget()), _offset(offset), _size(size), _access(access)
{
	__init_buffer_range_mapper(_target, _offset, _size, _access, _ptr);
}

vertex_buffer_object_range_mapper::vertex_buffer_object_range_mapper(vertex_buffer_object_range_mapper&& other) noexcept
	: _ptr(other._ptr), _target(other._target), _offset(other._offset), _size(other._size), _access(other._access)
{
	other._ptr = nullptr;
	other._target = VertexBufferObject::Target::UNDEFINED;
	other._offset = 0;
	other._size = 0;
	other._access = 0;
}

vertex_buffer_object_range_mapper& vertex_buffer_object_range_mapper::operator=(vertex_buffer_object_range_mapper&& other)
{
	if (this != &other)
	{
		std::swap(_ptr, other._ptr);
		std::swap(_target, other._target);
		std::swap(_offset, other._offset);
		std::swap(_size, other._size);
		std::swap(_access, other._access);
	}
	return *this;
}

void vertex_buffer_object_range_mapper::flush()
{
	VertexBufferObject::FlushMappedRange(_target, _offset, _size);
}

bool vertex_buffer_object_range_mapper::unmap()
{
	if (mapped())
	{
		flush();
		VertexBufferObject::Unmap(_target);
		_ptr = nullptr;
		return true;
	}
	return false;
}

END_LFRL_OGL_NAMESPACE
