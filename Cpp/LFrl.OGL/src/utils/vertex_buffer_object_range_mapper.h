#ifndef __LFRL_OGL_VERTEX_BUFFER_OBJECT_RANGE_MAPPER_GUARD__
#define __LFRL_OGL_VERTEX_BUFFER_OBJECT_RANGE_MAPPER_GUARD__

#include "../primitives/VertexBufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

struct vertex_buffer_object_range_mapper final
{
	vertex_buffer_object_range_mapper(vertex_buffer_object_range_mapper const&) = delete;
	vertex_buffer_object_range_mapper& operator=(vertex_buffer_object_range_mapper const&) = delete;

	vertex_buffer_object_range_mapper() noexcept;
	vertex_buffer_object_range_mapper(VertexBufferObject::Target target, GLint offset, GLuint size, GLbitfield access);
	vertex_buffer_object_range_mapper(VertexBufferObject const& obj, GLint offset, GLuint size, GLbitfield access);
	vertex_buffer_object_range_mapper(vertex_buffer_object_range_mapper&&) noexcept;
	vertex_buffer_object_range_mapper& operator=(vertex_buffer_object_range_mapper&&);
	~vertex_buffer_object_range_mapper() { unmap(); }

	bool mapped() const noexcept { return _ptr != nullptr; }
	void* ptr() const noexcept { return _ptr; }
	VertexBufferObject::Target target() const noexcept { return _target; }
	GLint offset() const noexcept { return _offset; }
	GLuint size() const noexcept { return _size; }
	GLbitfield access() const noexcept { return _access; }

	void flush();
	bool unmap();

private:
	void* _ptr;
	VertexBufferObject::Target _target;
	GLint _offset;
	GLuint _size;
	GLbitfield _access;
};

END_LFRL_OGL_NAMESPACE

#endif
