#ifndef __LFRL_OGL_VERTEX_BUFFER_OBJECT_MAPPER_GUARD__
#define __LFRL_OGL_VERTEX_BUFFER_OBJECT_MAPPER_GUARD__

#include "../primitives/VertexBufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

struct vertex_buffer_object_mapper final
{
	vertex_buffer_object_mapper(vertex_buffer_object_mapper const&) = delete;
	vertex_buffer_object_mapper& operator=(vertex_buffer_object_mapper const&) = delete;

	vertex_buffer_object_mapper() noexcept;
	explicit vertex_buffer_object_mapper(VertexBufferObject::Target target, AccessType access);
	vertex_buffer_object_mapper(VertexBufferObject const& obj, AccessType access);
	vertex_buffer_object_mapper(vertex_buffer_object_mapper&&) noexcept;
	vertex_buffer_object_mapper& operator=(vertex_buffer_object_mapper&&);
	~vertex_buffer_object_mapper() { unmap(); }

	bool mapped() const noexcept { return _ptr != nullptr; }
	void* ptr() const noexcept { return _ptr; }
	VertexBufferObject::Target target() const noexcept { return _target; }
	AccessType access() const noexcept { return _access; }

	bool unmap();

private:
	void* _ptr;
	VertexBufferObject::Target _target;
	AccessType _access;
};

END_LFRL_OGL_NAMESPACE

#endif
