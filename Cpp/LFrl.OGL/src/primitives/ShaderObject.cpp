#include "ShaderObject.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderObject::Type ShaderObject::GetType(GLuint id)
{
	if (id == 0)
		return Type::UNDEFINED;

	GLint result;
	glGetIntegerv(GL_SHADER_TYPE, &result);
	return static_cast<Type>(result);
}

std::string ShaderObject::GetSource(GLuint id)
{
	if (id == 0)
		return "";

	GLint length;
	glGetShaderiv(id, GL_SHADER_SOURCE_LENGTH, &length);

	if (length <= 0)
		return "";

	LFRL_COMMON::dynamic_buffer<char> buffer(length);
	glGetShaderSource(id, length, NULL, buffer.data());
	return buffer.data();
}

std::string ShaderObject::GetInfoLog(GLuint id)
{
	if (id == 0)
		return "";

	GLint length;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

	if (length <= 0)
		return "";

	LFRL_COMMON::dynamic_buffer<char> buffer(length);
	glGetShaderInfoLog(id, length, NULL, buffer.data());
	return buffer.data();
}

bool ShaderObject::Compile(GLuint id)
{
	if (id == 0)
		return false;

	glCompileShader(id);

	GLint ok;
	glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
	return ok != 0;
}

bool ShaderObject::IsFlaggedForDeletion(GLuint id)
{
	if (id == 0)
		return false;

	GLint result;
	glGetShaderiv(id, GL_DELETE_STATUS, &result);
	return result != 0;
}

ShaderObject::ShaderObject() noexcept
	: _id(0), _type(Type::UNDEFINED), _state(ObjectState::CREATED)
{}

ShaderObject::ActionResult ShaderObject::Initialize(ShaderObject::Type type, const char* source)
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	if (type == Type::UNDEFINED)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::UNDEFINED_TYPE;
	}

	if (source == nullptr)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::NULL_SOURCE;
	}

	auto id = glCreateShader(static_cast<GLenum>(type));
	if (id == 0)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::SHADER_GEN_FAILURE;
	}

	char const* sources[1] = { source };
	glShaderSource(id, 1, sources, NULL);

	if (!Compile(id))
	{
		glDeleteShader(id);
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::COMPILATION_FAILURE;
	}

	_id = id;
	_type = type;
	_state = ObjectState::READY;
	return ActionResult::OK;
}

ShaderObject::ActionResult ShaderObject::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	glDeleteShader(_id);
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
