#ifndef __LFRL_OGL_BUFFER_OBJECT_RANGE_MAPPER_GUARD__
#define __LFRL_OGL_BUFFER_OBJECT_RANGE_MAPPER_GUARD__

#include "../primitives/BufferObject.h"

BEGIN_LFRL_OGL_NAMESPACE

struct buffer_object_range_mapper final
{
	buffer_object_range_mapper(buffer_object_range_mapper const&) = delete;
	buffer_object_range_mapper& operator=(buffer_object_range_mapper const&) = delete;

	buffer_object_range_mapper() noexcept;
	buffer_object_range_mapper(BufferObject::Target target, GLint offset, GLuint size, GLbitfield access);
	buffer_object_range_mapper(BufferObject const& obj, GLint offset, GLuint size, GLbitfield access);
	buffer_object_range_mapper(buffer_object_range_mapper&&) noexcept;
	buffer_object_range_mapper& operator=(buffer_object_range_mapper&&);
	~buffer_object_range_mapper() { unmap(); }

	bool mapped() const noexcept { return _ptr != nullptr; }
	void* ptr() const noexcept { return _ptr; }
	BufferObject::Target target() const noexcept { return _target; }
	GLint offset() const noexcept { return _offset; }
	GLuint size() const noexcept { return _size; }
	GLbitfield access() const noexcept { return _access; }

	void flush();
	bool unmap();

private:
	void* _ptr;
	BufferObject::Target _target;
	GLint _offset;
	GLuint _size;
	GLbitfield _access;
};

END_LFRL_OGL_NAMESPACE

#endif
