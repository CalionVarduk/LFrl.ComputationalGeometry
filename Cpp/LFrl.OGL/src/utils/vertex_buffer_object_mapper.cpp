#include "vertex_buffer_object_mapper.h"

BEGIN_LFRL_OGL_NAMESPACE

void __init_buffer_mapper(VertexBufferObject::Target target, AccessType access, void*& ptr)
{
	ptr = VertexBufferObject::Map(target, access);
}

vertex_buffer_object_mapper::vertex_buffer_object_mapper() noexcept
	: _ptr(nullptr), _target(VertexBufferObject::Target::UNDEFINED), _access(AccessType::READ_WRITE)
{}

vertex_buffer_object_mapper::vertex_buffer_object_mapper(VertexBufferObject::Target target, AccessType access)
	: _ptr(nullptr), _target(target), _access(access)
{
	__init_buffer_mapper(_target, _access, _ptr);
}

vertex_buffer_object_mapper::vertex_buffer_object_mapper(VertexBufferObject const& obj, AccessType access)
	: _ptr(nullptr), _target(obj.GetTarget()), _access(access)
{
	__init_buffer_mapper(_target, _access, _ptr);
}

vertex_buffer_object_mapper::vertex_buffer_object_mapper(vertex_buffer_object_mapper&& other) noexcept
	: _ptr(other._ptr), _target(other._target), _access(other._access)
{
	other._ptr = nullptr;
	other._target = VertexBufferObject::Target::UNDEFINED;
	other._access = AccessType::READ_WRITE;
}

vertex_buffer_object_mapper& vertex_buffer_object_mapper::operator=(vertex_buffer_object_mapper&& other)
{
	if (this != &other)
	{
		std::swap(_ptr, other._ptr);
		std::swap(_target, other._target);
		std::swap(_access, other._access);
	}
	return *this;
}

bool vertex_buffer_object_mapper::unmap()
{
	if (mapped())
	{
		VertexBufferObject::Unmap(_target);
		_ptr = nullptr;
		return true;
	}
	return false;
}

END_LFRL_OGL_NAMESPACE
