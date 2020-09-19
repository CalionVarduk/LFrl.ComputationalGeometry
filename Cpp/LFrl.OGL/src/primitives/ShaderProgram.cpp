#include "ShaderProgram.h"

BEGIN_LFRL_OGL_NAMESPACE

void ShaderProgram::Use(GLuint id)
{
	glUseProgram(id);
}

GLuint ShaderProgram::GetUsedId()
{
	GLint result;
	glGetIntegerv(GL_CURRENT_PROGRAM, &result);
	return static_cast<GLuint>(result);
}

std::string ShaderProgram::GetInfoLog(GLuint id)
{
	if (id == 0)
		return "";

	GLint length;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

	if (length <= 0)
		return "";

	LFRL_COMMON::dynamic_buffer<char> buffer(length);
	glGetProgramInfoLog(id, length, NULL, buffer.data());
	return buffer.data();
}

bool ShaderProgram::IsFlaggedForDeletion(GLuint id)
{
	if (id == 0)
		return false;

	GLint result;
	glGetProgramiv(id, GL_DELETE_STATUS, &result);
	return result != 0;
}

bool ShaderProgram::AttachShader(GLuint id, GLuint shaderId)
{
	if (!glIsShader(shaderId))
		return false;

	glAttachShader(id, shaderId);
	return true;
}

ShaderProgram::ActionResult ShaderProgram::Link(GLuint id)
{
	if (id == 0)
		return ActionResult::NOT_READY;

	glLinkProgram(id);

	GLint ok;
	glGetProgramiv(id, GL_LINK_STATUS, &ok);
	if (!ok)
		return ActionResult::LINKAGE_FAILURE;

	glGetProgramiv(id, GL_VALIDATE_STATUS, &ok);
	return ok != 0 ? ActionResult::OK : ActionResult::LINKAGE_VALIDATION_FAILURE;
}

ShaderProgram::ShaderProgram() noexcept
	: _id(0), _isLinked(false), _state(ObjectState::CREATED)
{}

ShaderProgram::ActionResult ShaderProgram::Initialize()
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	auto id = glCreateProgram();
	if (id == 0)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::PROGRAM_GEN_FAILURE;
	}

	_id = id;
	_state = ObjectState::READY;
	return ActionResult::OK;
}

ShaderProgram::ActionResult ShaderProgram::AttachShader(GLuint shaderId)
{
	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	if (_isLinked)
		return ActionResult::ALREADY_LINKED;

	return AttachShader(_id, shaderId) ? ActionResult::OK : ActionResult::SHADER_ATTACHMENT_FAILURE;
}

ShaderProgram::ActionResult ShaderProgram::AttachShader(ShaderObject const& shader)
{
	if (shader.GetState() != ObjectState::READY)
		return ActionResult::INVALID_SHADER_STATE;

	return AttachShader(shader.GetId());
}

ShaderProgram::ActionResult ShaderProgram::Link()
{
	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	if (_isLinked)
		return ActionResult::ALREADY_LINKED;

	auto linkResult = Link(_id);
	if (linkResult == ActionResult::OK)
		_isLinked = true;

	return linkResult;
}

ShaderProgram::ActionResult ShaderProgram::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	glDeleteProgram(_id);
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
