#include "BufferObject.h"

#define INITIALIZE(TARGET, USAGE) _id(0), _target(TARGET), _usage(USAGE), _state(ObjectState::CREATED)

BEGIN_LFRL_OGL_NAMESPACE

void BufferObject::Bind(BufferObject::Target target, GLuint id)
{
	glBindBuffer(static_cast<GLenum>(target), id);
}

GLuint BufferObject::GetBoundId(BufferObject::Binding binding)
{
	GLint result;
	glGetIntegerv(static_cast<GLenum>(binding), &result);
	return static_cast<GLuint>(result);
}

void BufferObject::SetData(BufferObject::Target target, GLuint size, void const* data, BufferObject::Usage usage)
{
	glBufferData(static_cast<GLenum>(target), static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
}

void BufferObject::SetSubData(BufferObject::Target target, GLint offset, GLuint size, void const* data)
{
	glBufferSubData(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

bool BufferObject::CopySubData(BufferObject::Target source, BufferObject::Target destination, GLint readOffset, GLint writeOffset, GLuint size)
{
	if (source == destination)
		return false;

	glCopyBufferSubData(static_cast<GLenum>(source), static_cast<GLenum>(destination), static_cast<GLintptr>(readOffset), static_cast<GLintptr>(writeOffset), static_cast<GLsizeiptr>(size));
	return true;
}

void* BufferObject::Map(BufferObject::Target target, AccessType access)
{
	return glMapBuffer(static_cast<GLenum>(target), static_cast<GLenum>(access));
}

void* BufferObject::MapRange(BufferObject::Target target, GLint offset, GLuint size, GLbitfield access)
{
	return glMapBufferRange(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), access);
}

void BufferObject::FlushMappedRange(BufferObject::Target target, GLint offset, GLuint size)
{
	glFlushMappedBufferRange(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size));
}

bool BufferObject::Unmap(BufferObject::Target target)
{
	return glUnmapBuffer(static_cast<GLenum>(target));
}

BufferObject::BufferObject() noexcept
	: INITIALIZE(Target::ARRAY_BUFFER, Usage::STATIC_DRAW)
{}

BufferObject::BufferObject(BufferObject::Target target) noexcept
	: INITIALIZE(target, Usage::STATIC_DRAW)
{}

BufferObject::BufferObject(BufferObject::Target target, BufferObject::Usage usage) noexcept
	: INITIALIZE(target, usage)
{}

BufferObject::ActionResult BufferObject::Initialize()
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	glGenBuffers(1, &_id);
	if (_id == 0)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::BUFFER_GEN_FAILURE;
	}

	_state = ObjectState::READY;
	return ActionResult::OK;
}

BufferObject::ActionResult BufferObject::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	glDeleteBuffers(1, &_id);
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
