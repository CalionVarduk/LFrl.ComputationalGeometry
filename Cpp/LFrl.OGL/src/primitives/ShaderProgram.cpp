#include "ShaderProgram.h"

BEGIN_LFRL_OGL_NAMESPACE

GLuint __get_attribute_max_name_length(GLuint id)
{
	GLint nameLength;
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameLength);
	return static_cast<GLuint>(nameLength);
}

ShaderProgram::Attribute::ConfigurableType ShaderProgram::Attribute::ConvertToConfigurableType(ShaderVariableType::Code code) noexcept
{
	auto scalarTypeCode = ShaderVariableType::GetScalarTypeCode(code);
	return static_cast<ConfigurableType>(scalarTypeCode);
}

ShaderProgram::Attribute::ConfigurableType ShaderProgram::Attribute::ConvertToConfigurableType(ShaderVariableType const& type) noexcept
{
	return static_cast<ConfigurableType>(type.GetScalarTypeCode());
}

ShaderProgram::Attribute::Attribute() noexcept
	: _programId(0), _index(-1), _location(-1), _size(0), _type(), _name()
{}

ShaderProgram::Attribute::LoadResult ShaderProgram::Attribute::Load(GLuint programId, GLuint index)
{
	if (IsLoaded())
		return LoadResult::ALREADY_LOADED;

	if (!glIsProgram(programId))
		return LoadResult::INVALID_PROGRAM;

	auto attribCount = GetAttributeCount(programId);

	if (index >= attribCount)
		return LoadResult::INVALID_INDEX;

	auto nameLength = __get_attribute_max_name_length(programId);
	LFRL_COMMON::dynamic_buffer<char> buffer(nameLength);

	_Populate(programId, index, buffer);
	return LoadResult::OK;
}

void ShaderProgram::Attribute::SetDivisor(GLuint value)
{
	auto length = GetLength();
	for (GLuint i = 0; i < length; ++i)
		SetDivisorAt(i, value);
}

GLuint ShaderProgram::Attribute::GetDivisorAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &result);
	return result;
}

void ShaderProgram::Attribute::SetDivisorAt(GLuint index, GLuint value)
{
	glVertexAttribDivisor(_location + index, value);
}

void ShaderProgram::Attribute::Enable()
{
	auto length = GetLength();
	for (GLuint i = 0; i < length; ++i)
		EnableAt(i);
}

void ShaderProgram::Attribute::Disable()
{
	auto length = GetLength();
	for (GLuint i = 0; i < length; ++i)
		DisableAt(i);
}

bool ShaderProgram::Attribute::IsEnabledAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &result);
	return result != 0;
}

void ShaderProgram::Attribute::EnableAt(GLuint index)
{
	glEnableVertexAttribArray(_location + index);
}

void ShaderProgram::Attribute::DisableAt(GLuint index)
{
	glDisableVertexAttribArray(_location + index);
}

GLuint ShaderProgram::Attribute::GetConfiguredSizeAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &result);
	return result;
}

ShaderProgram::Attribute::ConfigurableType ShaderProgram::Attribute::GetConfiguredTypeAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &result);
	return static_cast<ShaderProgram::Attribute::ConfigurableType>(result);
}

bool ShaderProgram::Attribute::IsNormalizedAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &result);
	return result != 0;
}

GLuint ShaderProgram::Attribute::GetConfiguredStrideAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &result);
	return result;
}

GLuint ShaderProgram::Attribute::GetConfiguredOffsetAt(GLuint index) const
{
	void* result;
	glGetVertexAttribPointerv(_location + index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &result);
	return reinterpret_cast<GLuint>(result);
}

GLuint ShaderProgram::Attribute::GetConfiguredBufferObjectIdAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &result);
	return static_cast<GLuint>(result);
}

BufferObject::Binding ShaderProgram::Attribute::GetConfiguredBindingAt(GLuint index) const
{
	GLint result;
	glGetVertexAttribiv(_location + index, GL_VERTEX_ATTRIB_BINDING, &result);
	return static_cast<BufferObject::Binding>(result);
}

void ShaderProgram::Attribute::ConfigureAt(GLuint index, GLuint stride, GLuint offset)
{
	auto size = _type.GetRowCount();
	auto type = ConvertToConfigurableType(_type);
	ConfigureAt(index, size, type, stride, offset + index * _type.GetRowSize(), false);
}

void ShaderProgram::Attribute::ConfigureAt(GLuint index, GLuint size, ShaderProgram::Attribute::ConfigurableType type, GLuint stride, GLuint offset, bool normalized)
{
	glVertexAttribPointer(_location + index, static_cast<GLint>(size), static_cast<GLenum>(type), normalized, stride, reinterpret_cast<void*>(offset));
}

void ShaderProgram::Attribute::Configure(GLuint stride, GLuint offset)
{
	auto length = GetLength();
	for (GLuint i = 0; i < length; ++i)
		ConfigureAt(i, stride, offset);
}

void ShaderProgram::Attribute::Configure(GLuint size, ShaderProgram::Attribute::ConfigurableType type, GLuint stride, GLuint offset, bool normalized)
{
	auto length = GetLength();
	for (GLuint i = 0; i < length; ++i)
		ConfigureAt(i, size, type, stride, offset, normalized);
}

void ShaderProgram::Attribute::_Populate(GLuint programId, GLuint index, LFRL_COMMON::dynamic_buffer<char> const& nameBuffer)
{
	GLint size;
	GLenum type;
	glGetActiveAttrib(programId, index, nameBuffer.size(), NULL, &size, &type, nameBuffer.data());
	auto location = glGetAttribLocation(programId, nameBuffer.data());

	_programId = programId;
	_index = static_cast<GLint>(index);
	_location = location;
	_size = static_cast<GLuint>(size);
	_type = ShaderVariableType::Create(static_cast<ShaderVariableType::Code>(type));
	_name = nameBuffer.data();
}

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

bool ShaderProgram::DetachShader(GLuint id, GLuint shaderId)
{
	if (!glIsShader(shaderId))
		return false;

	glDetachShader(id, shaderId);
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

GLuint ShaderProgram::GetAttachedShaderCount(GLuint id)
{
	GLint result;
	glGetProgramiv(id, GL_ATTACHED_SHADERS, &result);
	return static_cast<GLuint>(result);
}

GLuint ShaderProgram::GetAttachedShaderIds(GLuint id, LFRL_COMMON::array_ptr<GLuint> buffer)
{
	if (buffer.size() == 0)
		return 0;

	GLint count;
	glGetAttachedShaders(id, buffer.size(), &count, buffer.get());
	return count;
}

GLuint ShaderProgram::GetAttributeCount(GLuint id)
{
	GLint result;
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &result);
	return static_cast<GLuint>(result);
}

GLuint ShaderProgram::GetAttributes(GLuint id, LFRL_COMMON::array_ptr<ShaderProgram::Attribute> buffer)
{
	if (buffer.size())
		return 0;

	auto count = GetAttributeCount(id);
	auto read = count > buffer.size() ? buffer.size() : count;

	auto nameLength = __get_attribute_max_name_length(id);
	LFRL_COMMON::dynamic_buffer<char> nameBuffer(nameLength);

	for (GLuint i = 0; i < read; ++i)
	{
		buffer[i]._Populate(id, i, nameBuffer);
		nameBuffer.reset();
	}
	return read;
}

ShaderProgram::ShaderProgram() noexcept
	: _id(0), _state(ObjectState::CREATED)
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

	return AttachShader(_id, shaderId) ? ActionResult::OK : ActionResult::SHADER_ATTACHMENT_FAILURE;
}

ShaderProgram::ActionResult ShaderProgram::AttachShader(ShaderObject const& shader)
{
	if (shader.GetState() != ObjectState::READY)
		return ActionResult::INVALID_SHADER_STATE;

	return AttachShader(shader.GetId());
}

ShaderProgram::ActionResult ShaderProgram::DetachShader(GLuint shaderId)
{
	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	return DetachShader(_id, shaderId) ? ActionResult::OK : ActionResult::SHADER_DETACHMENT_FAILURE;
}

ShaderProgram::ActionResult ShaderProgram::Link()
{
	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	return Link(_id);
}

std::vector<GLuint> ShaderProgram::GetAttachedShaderIds() const
{
	auto count = GetAttachedShaderCount();
	std::vector<GLuint> result(count, 0);
	GetAttachedShaderIds(LFRL_COMMON::array_ptr<GLuint>(result.data(), result.size()));
	return result;
}

std::vector<ShaderProgram::Attribute> ShaderProgram::GetAttributes() const
{
	auto count = GetAttributeCount(_id);
	std::vector<ShaderProgram::Attribute> result(count, ShaderProgram::Attribute());

	auto nameLength = __get_attribute_max_name_length(_id);
	LFRL_COMMON::dynamic_buffer<char> nameBuffer(nameLength);

	for (GLuint i = 0; i < count; ++i)
	{
		result[i]._Populate(_id, i, nameBuffer);
		nameBuffer.reset();
	}
	return result;
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
