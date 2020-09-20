#include "ShaderProgram.h"

BEGIN_LFRL_OGL_NAMESPACE

GLuint __get_attribute_max_name_length(GLuint id)
{
	GLint nameLength;
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameLength);
	return static_cast<GLuint>(nameLength);
}

GLuint __get_uniform_max_name_length(GLuint id)
{
	GLint nameLength;
	glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameLength);
	return static_cast<GLuint>(nameLength);
}

ShaderProgram::Attribute::ConfigurableType ShaderProgram::Attribute::ConvertToConfigurableType(ShaderProgram::Attribute::Type::Code code) noexcept
{
	auto scalarTypeCode = Type::GetScalarTypeCode(code);
	return static_cast<ConfigurableType>(scalarTypeCode);
}

ShaderProgram::Attribute::ConfigurableType ShaderProgram::Attribute::ConvertToConfigurableType(ShaderProgram::Attribute::Type const& type) noexcept
{
	return static_cast<ConfigurableType>(type.GetScalarTypeCode());
}

ShaderProgram::Attribute::Attribute() noexcept
	: _programId(0), _index(-1), _location(-1), _size(0), _type(), _name()
{}

ShaderProgram::Attribute::LoadResult ShaderProgram::Attribute::Load(GLuint programId, GLuint index)
{
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
	return static_cast<GLuint>(reinterpret_cast<GLsizeiptr>(result));
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
	glVertexAttribPointer(_location + index, static_cast<GLint>(size), static_cast<GLenum>(type), normalized, stride, reinterpret_cast<void*>(static_cast<GLsizeiptr>(offset)));
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
	glGetActiveAttrib(programId, index, static_cast<GLsizei>(nameBuffer.size()), NULL, &size, &type, nameBuffer.data());
	auto location = glGetAttribLocation(programId, nameBuffer.data());

	_programId = programId;
	_index = static_cast<GLint>(index);
	_location = location;
	_size = static_cast<GLuint>(size);
	_type = Type::Create(static_cast<Type::Code>(type));
	_name = nameBuffer.data();
}

ShaderProgram::Uniform::Uniform() noexcept
	: _programId(0), _index(-1), _location(-1), _size(0), _type(), _name()
{}

ShaderProgram::Uniform::LoadResult ShaderProgram::Uniform::Load(GLuint programId, GLuint index)
{
	if (!glIsProgram(programId))
		return LoadResult::INVALID_PROGRAM;

	auto uniformCount = GetUniformCount(programId);

	if (index >= uniformCount)
		return LoadResult::INVALID_INDEX;

	auto nameLength = __get_uniform_max_name_length(programId);
	LFRL_COMMON::dynamic_buffer<char> buffer(nameLength);

	_Populate(programId, index, buffer);
	return LoadResult::OK;
}

void ShaderProgram::Uniform::Set(GLfloat value)
{
	glUniform1f(_location, value);
}

void ShaderProgram::Uniform::Set(GLint value)
{
	glUniform1i(_location, value);
}

void ShaderProgram::Uniform::Set(GLuint value)
{
	glUniform1ui(_location, value);
}

void ShaderProgram::Uniform::Set(bool value)
{
	glUniform1i(_location, static_cast<GLint>(value));
}

void ShaderProgram::Uniform::SetVec2(GLfloat x, GLfloat y)
{
	glUniform2f(_location, x, y);
}

void ShaderProgram::Uniform::SetVec2(GLint x, GLint y)
{
	glUniform2i(_location, x, y);
}

void ShaderProgram::Uniform::SetVec2(GLuint x, GLuint y)
{
	glUniform2ui(_location, x, y);
}

void ShaderProgram::Uniform::SetVec2(bool x, bool y)
{
	glUniform2i(_location, static_cast<GLint>(x), static_cast<GLint>(y));
}

void ShaderProgram::Uniform::SetVec3(GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(_location, x, y, z);
}

void ShaderProgram::Uniform::SetVec3(GLint x, GLint y, GLint z)
{
	glUniform3i(_location, x, y, z);
}

void ShaderProgram::Uniform::SetVec3(GLuint x, GLuint y, GLuint z)
{
	glUniform3ui(_location, x, y, z);
}

void ShaderProgram::Uniform::SetVec3(bool x, bool y, bool z)
{
	glUniform3i(_location, static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(z));
}

void ShaderProgram::Uniform::SetVec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(_location, x, y, z, w);
}

void ShaderProgram::Uniform::SetVec4(GLint x, GLint y, GLint z, GLint w)
{
	glUniform4i(_location, x, y, z, w);
}

void ShaderProgram::Uniform::SetVec4(GLuint x, GLuint y, GLuint z, GLuint w)
{
	glUniform4ui(_location, x, y, z, w);
}

void ShaderProgram::Uniform::SetVec4(bool x, bool y, bool z, bool w)
{
	glUniform4i(_location, static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(z), static_cast<GLint>(w));
}

void ShaderProgram::Uniform::SetMat2(glm::mat2 const& value, bool transpose)
{
	glUniformMatrix2fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat2x3(glm::mat2x3 const& value, bool transpose)
{
	glUniformMatrix2x3fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat2x4(glm::mat2x4 const& value, bool transpose)
{
	glUniformMatrix2x4fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat3(glm::mat3 const& value, bool transpose)
{
	glUniformMatrix3fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat3x2(glm::mat3x2 const& value, bool transpose)
{
	glUniformMatrix3x2fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat3x4(glm::mat3x4 const& value, bool transpose)
{
	glUniformMatrix3x4fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat4(glm::mat4 const& value, bool transpose)
{
	glUniformMatrix4fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat4x2(glm::mat4x2 const& value, bool transpose)
{
	glUniformMatrix4x2fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::SetMat4x3(glm::mat4x3 const& value, bool transpose)
{
	glUniformMatrix4x3fv(_location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::Uniform::_Populate(GLuint programId, GLuint index, LFRL_COMMON::dynamic_buffer<char> const& nameBuffer)
{
	GLint size;
	GLenum type;
	glGetActiveUniform(programId, index, static_cast<GLsizei>(nameBuffer.size()), NULL, &size, &type, nameBuffer.data());
	auto location = glGetUniformLocation(programId, nameBuffer.data());

	_programId = programId;
	_index = static_cast<GLint>(index);
	_location = location;
	_size = static_cast<GLuint>(size);
	_type = static_cast<Type>(type);
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
	glGetAttachedShaders(id, static_cast<GLsizei>(buffer.size()), &count, buffer.get());
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
	auto read = count > buffer.size() ? static_cast<GLuint>(buffer.size()) : count;

	auto nameLength = __get_attribute_max_name_length(id);
	LFRL_COMMON::dynamic_buffer<char> nameBuffer(nameLength);

	for (GLuint i = 0; i < read; ++i)
	{
		buffer[i]._Populate(id, i, nameBuffer);
		nameBuffer.reset();
	}
	return read;
}

void ShaderProgram::BindAttributeLocation(GLuint id, GLuint location, char const* name)
{
	glBindAttribLocation(id, location, name);
}

GLuint ShaderProgram::GetUniformCount(GLuint id)
{
	GLint result;
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &result);
	return static_cast<GLuint>(result);
}

GLuint ShaderProgram::GetUniforms(GLuint id, LFRL_COMMON::array_ptr<ShaderProgram::Uniform> buffer)
{
	if (buffer.size())
		return 0;

	auto count = GetUniformCount(id);
	auto read = count > buffer.size() ? static_cast<GLuint>(buffer.size()) : count;

	auto nameLength = __get_uniform_max_name_length(id);
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
	std::vector<Attribute> result(count, Attribute());

	auto nameLength = __get_attribute_max_name_length(_id);
	LFRL_COMMON::dynamic_buffer<char> nameBuffer(nameLength);

	for (GLuint i = 0; i < count; ++i)
	{
		result[i]._Populate(_id, i, nameBuffer);
		nameBuffer.reset();
	}
	return result;
}

std::vector<ShaderProgram::Uniform> ShaderProgram::GetUniforms() const
{
	auto count = GetUniformCount(_id);
	std::vector<Uniform> result(count, Uniform());

	auto nameLength = __get_uniform_max_name_length(_id);
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
