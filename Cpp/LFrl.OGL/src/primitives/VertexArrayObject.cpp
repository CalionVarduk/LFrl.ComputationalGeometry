#include "VertexArrayObject.h"

BEGIN_LFRL_OGL_NAMESPACE

void VertexArrayObject::Bind(GLuint id)
{
	glBindVertexArray(id);
}

GLuint VertexArrayObject::GetBoundId()
{
	GLint result;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &result);
	return static_cast<GLuint>(result);
}

VertexArrayObject::VertexArrayObject() noexcept
	: _id(0), _state(ObjectState::CREATED)
{}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept
	: _id(0), _state(ObjectState::CREATED)
{
	std::swap(_id, other._id);
	std::swap(_state, other._state);
}

VertexArrayObject& VertexArrayObject::operator= (VertexArrayObject&& other) noexcept
{
	if (this != &other)
	{
		std::swap(_id, other._id);
		std::swap(_state, other._state);
	}
	return *this;
}

VertexArrayObject::ActionResult VertexArrayObject::Initialize()
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	glGenVertexArrays(1, &_id);
	if (_id == 0)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::ARRAY_GEN_FAILURE;
	}

	_state = ObjectState::READY;
	return ActionResult::OK;
}

VertexArrayObject::ActionResult VertexArrayObject::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	glDeleteVertexArrays(1, &_id);
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
