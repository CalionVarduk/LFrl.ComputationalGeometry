#include "buffer_object_mapper.h"

BEGIN_LFRL_OGL_NAMESPACE

void __init_buffer_mapper(BufferObject::Target target, AccessType access, void*& ptr)
{
	ptr = BufferObject::Map(target, access);
}

buffer_object_mapper::buffer_object_mapper()
	: _ptr(nullptr), _target(BufferObject::Target::UNDEFINED), _access(AccessType::READ_WRITE)
{}

buffer_object_mapper::buffer_object_mapper(BufferObject::Target target, AccessType access)
	: _ptr(nullptr), _target(target), _access(access)
{
	__init_buffer_mapper(_target, _access, _ptr);
}

buffer_object_mapper::buffer_object_mapper(BufferObject const& obj, AccessType access)
	: _ptr(nullptr), _target(obj.GetTarget()), _access(access)
{
	__init_buffer_mapper(_target, _access, _ptr);
}

buffer_object_mapper::buffer_object_mapper(buffer_object_mapper&& other) noexcept
	: _ptr(other._ptr), _target(other._target), _access(other._access)
{
	other._ptr = nullptr;
	other._target = BufferObject::Target::UNDEFINED;
	other._access = AccessType::READ_WRITE;
}

buffer_object_mapper& buffer_object_mapper::operator=(buffer_object_mapper&& other)
{
	if (this != &other)
	{
		std::swap(_ptr, other._ptr);
		std::swap(_target, other._target);
		std::swap(_access, other._access);
	}
	return *this;
}

bool buffer_object_mapper::unmap()
{
	if (mapped())
	{
		BufferObject::Unmap(_target);
		_ptr = nullptr;
		return true;
	}
	return false;
}

END_LFRL_OGL_NAMESPACE
