#ifndef __LFRL_OGL_BUFFER_OBJECT_MAPPER_GUARD__
#define __LFRL_OGL_BUFFER_OBJECT_MAPPER_GUARD__

#include "../primitives/BufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

struct buffer_object_mapper final
{
	buffer_object_mapper(buffer_object_mapper const&) = delete;
	buffer_object_mapper& operator=(buffer_object_mapper const&) = delete;

	buffer_object_mapper();
	explicit buffer_object_mapper(BufferObject::Target target, AccessType access);
	buffer_object_mapper(BufferObject const& obj, AccessType access);
	buffer_object_mapper(buffer_object_mapper&&) noexcept;
	buffer_object_mapper& operator=(buffer_object_mapper&&);
	~buffer_object_mapper() { unmap(); }

	bool mapped() const noexcept { return _ptr != nullptr; }
	void* ptr() const noexcept { return _ptr; }
	BufferObject::Target target() const noexcept { return _target; }
	AccessType access() const noexcept { return _access; }

	bool unmap();

private:
	void* _ptr;
	BufferObject::Target _target;
	AccessType _access;
};

END_LFRL_OGL_NAMESPACE

#endif
