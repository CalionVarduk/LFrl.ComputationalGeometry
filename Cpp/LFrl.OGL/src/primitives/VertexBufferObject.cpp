#include "VertexBufferObject.h"

#define INITIALIZE(TARGET, USAGE) _id(0), _target(TARGET), _usage(USAGE), _state(ObjectState::CREATED)

BEGIN_LFRL_OGL_NAMESPACE

void VertexBufferObject::Bind(VertexBufferObject::Target target, GLuint id)
{
	glBindBuffer(static_cast<GLenum>(target), id);
}

GLuint VertexBufferObject::GetBoundId(VertexBufferObject::Binding binding)
{
	GLint result;
	glGetIntegerv(static_cast<GLenum>(binding), &result);
	return static_cast<GLuint>(result);
}

void VertexBufferObject::SetData(VertexBufferObject::Target target, GLuint size, void const* data, VertexBufferObject::Usage usage)
{
	glBufferData(static_cast<GLenum>(target), static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
}

void VertexBufferObject::SetSubData(VertexBufferObject::Target target, GLint offset, GLuint size, void const* data)
{
	glBufferSubData(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

bool VertexBufferObject::CopySubData(VertexBufferObject::Target source, VertexBufferObject::Target destination, GLint readOffset, GLint writeOffset, GLuint size)
{
	if (source == destination)
		return false;

	glCopyBufferSubData(static_cast<GLenum>(source), static_cast<GLenum>(destination), static_cast<GLintptr>(readOffset), static_cast<GLintptr>(writeOffset), static_cast<GLsizeiptr>(size));
	return true;
}

void* VertexBufferObject::Map(VertexBufferObject::Target target, AccessType access)
{
	return glMapBuffer(static_cast<GLenum>(target), static_cast<GLenum>(access));
}

void* VertexBufferObject::MapRange(VertexBufferObject::Target target, GLint offset, GLuint size, GLbitfield access)
{
	return glMapBufferRange(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), access);
}

void VertexBufferObject::FlushMappedRange(VertexBufferObject::Target target, GLint offset, GLuint size)
{
	glFlushMappedBufferRange(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size));
}

bool VertexBufferObject::Unmap(VertexBufferObject::Target target)
{
	return glUnmapBuffer(static_cast<GLenum>(target));
}

VertexBufferObject::VertexBufferObject() noexcept
	: INITIALIZE(Target::ARRAY_BUFFER, Usage::STATIC_DRAW)
{}

VertexBufferObject::VertexBufferObject(VertexBufferObject::Target target) noexcept
	: INITIALIZE(target, Usage::STATIC_DRAW)
{}

VertexBufferObject::VertexBufferObject(VertexBufferObject::Target target, VertexBufferObject::Usage usage) noexcept
	: INITIALIZE(target, usage)
{}

VertexBufferObject::VertexBufferObject(VertexBufferObject&& other) noexcept
	: INITIALIZE(Target::ARRAY_BUFFER, Usage::STATIC_DRAW)
{
	std::swap(_id, other._id);
	std::swap(_target, other._target);
	std::swap(_usage, other._usage);
	std::swap(_state, other._state);
}

VertexBufferObject& VertexBufferObject::operator= (VertexBufferObject&& other) noexcept
{
	if (this != &other)
	{
		std::swap(_id, other._id);
		std::swap(_target, other._target);
		std::swap(_usage, other._usage);
		std::swap(_state, other._state);
	}
	return *this;
}

VertexBufferObject::ActionResult VertexBufferObject::Initialize()
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

VertexBufferObject::ActionResult VertexBufferObject::Dispose()
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
