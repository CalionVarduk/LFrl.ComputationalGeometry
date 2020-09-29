#ifndef __LFRL_OGL_SHADER_PROGRAM_GUARD__
#define __LFRL_OGL_SHADER_PROGRAM_GUARD__

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "BufferObject.h"
#include "ShaderObject.h"
#include "LFrl.Common/src/memory/array_ptr.h"

BEGIN_LFRL_OGL_NAMESPACE

struct ShaderProgram final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		PROGRAM_GEN_FAILURE = 2,
		INVALID_SHADER_STATE = 3,
		SHADER_ATTACHMENT_FAILURE = 4,
		SHADER_DETACHMENT_FAILURE = 5,
		LINKAGE_FAILURE = 6,
		LINKAGE_VALIDATION_FAILURE = 7,
		ALREADY_DISPOSED = 8,
		NOT_READY = 9
	};

	struct Attribute final
	{
		friend struct ShaderProgram;

		enum struct LoadResult
		{
			OK = 0,
			INVALID_PROGRAM = 1,
			INVALID_INDEX = 2
		};

		struct Type final
		{
			enum struct Code
			{
				UNDEFINED = 0,
				FLOAT = GL_FLOAT,
				FLOAT_VEC2 = GL_FLOAT_VEC2,
				FLOAT_VEC3 = GL_FLOAT_VEC3,
				FLOAT_VEC4 = GL_FLOAT_VEC4,
				FLOAT_MAT2 = GL_FLOAT_MAT2,
				FLOAT_MAT3 = GL_FLOAT_MAT3,
				FLOAT_MAT4 = GL_FLOAT_MAT4,
				FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
				FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
				FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
				FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
				FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
				FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,
				INT = GL_INT,
				INT_VEC2 = GL_INT_VEC2,
				INT_VEC3 = GL_INT_VEC3,
				INT_VEC4 = GL_INT_VEC4,
				UNSIGNED_INT = GL_UNSIGNED_INT,
				UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
				UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
				UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,
				DOUBLE = GL_DOUBLE,
				DOUBLE_VEC2 = GL_DOUBLE_VEC2,
				DOUBLE_VEC3 = GL_DOUBLE_VEC3,
				DOUBLE_VEC4 = GL_DOUBLE_VEC4,
				DOUBLE_MAT2 = GL_DOUBLE_MAT2,
				DOUBLE_MAT3 = GL_DOUBLE_MAT3,
				DOUBLE_MAT4 = GL_DOUBLE_MAT4,
				DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
				DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
				DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
				DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
				DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
				DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3
			};

			static constexpr GLuint GetColumnCount(Code code) noexcept;
			static constexpr GLuint GetRowCount(Code code) noexcept;
			static constexpr GLuint GetScalarCount(Code code) noexcept;
			static constexpr Code GetScalarTypeCode(Code code) noexcept;
			static constexpr GLuint GetScalarSize(Code code) noexcept;
			static constexpr GLuint GetColumnSize(Code code) noexcept { return GetRowCount(code) * GetScalarSize(code); }
			static constexpr GLuint GetRowSize(Code code) noexcept { return GetColumnCount(code) * GetScalarSize(code); }
			static constexpr GLuint GetSize(Code code) noexcept { return GetScalarCount(code) * GetScalarSize(code); }

			static constexpr Type Create(Code code) noexcept;

			template <Code code>
			static constexpr Type Create() noexcept { return Create(code); }

			constexpr Code GetCode() const noexcept { return _code; }
			constexpr GLuint GetColumnCount() const noexcept { return _columnCount; }
			constexpr GLuint GetRowCount() const noexcept { return _rowCount; }
			constexpr GLuint GetScalarCount() const noexcept { return _scalarCount; }
			constexpr Code GetScalarTypeCode() const noexcept { return _scalarTypeCode; }
			constexpr GLuint GetScalarSize() const noexcept { return _scalarSize; }
			constexpr GLuint GetColumnSize() const noexcept { return _columnSize; }
			constexpr GLuint GetRowSize() const noexcept { return _rowSize; }
			constexpr GLuint GetSize() const noexcept { return _size; }

			constexpr Type() noexcept;

		private:
			Code _code;
			GLuint _columnCount;
			GLuint _rowCount;
			GLuint _scalarCount;
			Code _scalarTypeCode;
			GLuint _scalarSize;
			GLuint _columnSize;
			GLuint _rowSize;
			GLuint _size;
		};

		enum struct ConfigurableType
		{
			UNDEFINED = 0,
			BYTE = GL_BYTE,
			UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
			SHORT = GL_SHORT,
			UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
			INT = GL_INT,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			HALF_FLOAT = GL_HALF_FLOAT,
			FLOAT = GL_FLOAT,
			DOUBLE = GL_DOUBLE,
			FIXED = GL_FIXED,
			INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
			UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
			UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
		};

		static ConfigurableType ConvertToConfigurableType(Type::Code code) noexcept;
		static ConfigurableType ConvertToConfigurableType(Type const& type) noexcept;

		Attribute() noexcept;
		Attribute(Attribute const&) = default;
		Attribute(Attribute&&) = default;
		Attribute& operator=(Attribute const&) = default;
		Attribute& operator=(Attribute&&) = default;

		GLuint GetProgramId() const noexcept { return _programId; }
		GLint GetIndex() const noexcept { return _index; }
		GLint GetLocation() const noexcept { return _location; }
		GLuint GetSize() const noexcept { return _size; }
		Type const& GetType() const noexcept { return _type; }
		GLuint GetLength() const noexcept { return _type.GetColumnCount(); }
		std::string const& GetName() const noexcept { return _name; }

		LoadResult Load(GLuint programId, GLuint index);

		GLuint GetDivisor() const { return GetDivisorAt(0); }
		void SetDivisor(GLuint value);
		bool IsInstanced() const { return GetDivisor() != 0; }

		GLuint GetDivisorAt(GLuint index) const;
		void SetDivisorAt(GLuint index, GLuint value);
		bool IsInstancedAt(GLuint index) const { return GetDivisorAt(index) != 0; }

		bool IsEnabled() const { return IsEnabledAt(0); }
		void Enable();
		void Disable();

		bool IsEnabledAt(GLuint index) const;
		void EnableAt(GLuint index);
		void DisableAt(GLuint index);

		GLuint GetConfiguredSizeAt(GLuint index) const;
		ConfigurableType GetConfiguredTypeAt(GLuint index) const;
		bool IsNormalizedAt(GLuint index) const;
		GLuint GetConfiguredStrideAt(GLuint index) const;
		GLuint GetConfiguredOffsetAt(GLuint index) const;
		GLuint GetConfiguredBufferObjectIdAt(GLuint index) const; // TODO: check if this actually returns an id
		BufferObject::Binding GetConfiguredBindingAt(GLuint index) const; // TODO: check if correct enum is used

		GLuint GetConfiguredSize() const { return GetConfiguredSizeAt(0); }
		ConfigurableType GetConfiguredType() const { return GetConfiguredTypeAt(0); }
		bool IsNormalized() const { return IsNormalizedAt(0); }
		GLuint GetConfiguredStride() const { return GetConfiguredStrideAt(0); }
		GLuint GetConfiguredOffset() const { return GetConfiguredOffsetAt(0); }
		GLuint GetConfiguredBufferObjectId() const { return GetConfiguredBufferObjectIdAt(0); }
		BufferObject::Binding GetConfiguredBinding() const { return GetConfiguredBindingAt(0); }

		void ConfigureAt(GLuint index, GLuint stride, GLuint offset = 0);
		void ConfigureAt(GLuint index, GLuint size, ConfigurableType type, GLuint stride, GLuint offset = 0, bool normalized = false);

		void Configure(GLuint stride, GLuint offset = 0);
		void Configure(GLuint size, ConfigurableType type, GLuint stride, GLuint offset = 0, bool normalized = false);

	private:
		GLuint _programId;
		GLint _index;
		GLint _location;
		GLuint _size;
		Type _type;
		std::string _name;

		void _Populate(GLuint programId, GLuint index, LFRL_COMMON::dynamic_buffer<char> const& nameBuffer);
	};

	struct Uniform final
	{
		friend struct ShaderProgram;

		enum struct LoadResult
		{
			OK = 0,
			INVALID_PROGRAM = 1,
			INVALID_INDEX = 2
		};

		enum struct Type
		{
			UNDEFINED = 0,
			FLOAT = GL_FLOAT,
			FLOAT_VEC2 = GL_FLOAT_VEC2,
			FLOAT_VEC3 = GL_FLOAT_VEC3,
			FLOAT_VEC4 = GL_FLOAT_VEC4,
			FLOAT_MAT2 = GL_FLOAT_MAT2,
			FLOAT_MAT3 = GL_FLOAT_MAT3,
			FLOAT_MAT4 = GL_FLOAT_MAT4,
			FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
			FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
			FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
			FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
			FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
			FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,
			INT = GL_INT,
			INT_VEC2 = GL_INT_VEC2,
			INT_VEC3 = GL_INT_VEC3,
			INT_VEC4 = GL_INT_VEC4,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
			UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
			UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,
			BOOL = GL_BOOL,
			BOOL_VEC2 = GL_BOOL_VEC2,
			BOOL_VEC3 = GL_BOOL_VEC3,
			BOOL_VEC4 = GL_BOOL_VEC4,
			DOUBLE = GL_DOUBLE,
			DOUBLE_VEC2 = GL_DOUBLE_VEC2,
			DOUBLE_VEC3 = GL_DOUBLE_VEC3,
			DOUBLE_VEC4 = GL_DOUBLE_VEC4,
			DOUBLE_MAT2 = GL_DOUBLE_MAT2,
			DOUBLE_MAT3 = GL_DOUBLE_MAT3,
			DOUBLE_MAT4 = GL_DOUBLE_MAT4,
			DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
			DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
			DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
			DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
			DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
			DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,
			SAMPLER_1D = GL_SAMPLER_1D,
			SAMPLER_2D = GL_SAMPLER_2D,
			SAMPLER_3D = GL_SAMPLER_3D,
			SAMPLER_CUBE = GL_SAMPLER_CUBE,
			SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,
			SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,
			SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,
			SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,
			SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,
			SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,
			SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE,
			SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
			SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,
			SAMPLER_BUFFER = GL_SAMPLER_BUFFER,
			SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,
			SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,
			INT_SAMPLER_1D = GL_INT_SAMPLER_1D,
			INT_SAMPLER_2D = GL_INT_SAMPLER_2D,
			INT_SAMPLER_3D = GL_INT_SAMPLER_3D,
			INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,
			INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,
			INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,
			INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,
			INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
			INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,
			INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,
			UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,
			UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,
			UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,
			UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,
			UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
			UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
			UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
			UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
			UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,
			UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
			IMAGE_1D = GL_IMAGE_1D,
			IMAGE_2D = GL_IMAGE_2D,
			IMAGE_3D = GL_IMAGE_3D,
			IMAGE_2D_RECT = GL_IMAGE_2D_RECT,
			IMAGE_CUBE = GL_IMAGE_CUBE,
			IMAGE_BUFFER = GL_IMAGE_BUFFER,
			IMAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,
			IMAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,
			IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,
			IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,
			INT_IMAGE_1D = GL_INT_IMAGE_1D,
			INT_IMAGE_2D = GL_INT_IMAGE_2D,
			INT_IMAGE_3D = GL_INT_IMAGE_3D,
			INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,
			INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,
			INT_IMAGE_BUFFER = GL_INT_IMAGE_BUFFER,
			INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,
			INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,
			INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,
			INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
			UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,
			UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,
			UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,
			UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,
			UNSIGNED_INT_IMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE,
			UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,
			UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
			UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
			UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
			UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
			UNSIGNED_INT_ATOMIC_COUNTER = GL_UNSIGNED_INT_ATOMIC_COUNTER
		};

		Uniform() noexcept;
		Uniform(Uniform const&) = default;
		Uniform(Uniform&&) = default;
		Uniform& operator=(Uniform const&) = default;
		Uniform& operator=(Uniform&&) = default;

		GLuint GetProgramId() const noexcept { return _programId; }
		GLint GetIndex() const noexcept { return _index; }
		GLint GetLocation() const noexcept { return _location; }
		GLuint GetSize() const noexcept { return _size; }
		Type GetType() const noexcept { return _type; }
		std::string const& GetName() const noexcept { return _name; }

		LoadResult Load(GLuint programId, GLuint index);

		void Set(GLfloat value);
		void Set(GLint value);
		void Set(GLuint value);
		void Set(bool value);
		void SetVec2(GLfloat x, GLfloat y);
		void SetVec2(glm::vec2 const& value) { SetVec2(value.x, value.y); }
		void SetVec3(GLfloat x, GLfloat y, GLfloat z);
		void SetVec3(glm::vec3 const& value) { SetVec3(value.x, value.y, value.z); }
		void SetVec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void SetVec4(glm::vec4 const& value) { SetVec4(value.x, value.y, value.z, value.w); }
		void SetVec2(GLint x, GLint y);
		void SetVec2(glm::ivec2 const& value) { SetVec2(value.x, value.y); }
		void SetVec3(GLint x, GLint y, GLint z);
		void SetVec3(glm::ivec3 const& value) { SetVec3(value.x, value.y, value.z); }
		void SetVec4(GLint x, GLint y, GLint z, GLint w);
		void SetVec4(glm::ivec4 const& value) { SetVec4(value.x, value.y, value.z, value.w); }
		void SetVec2(GLuint x, GLuint y);
		void SetVec2(glm::uvec2 const& value) { SetVec2(value.x, value.y); }
		void SetVec3(GLuint x, GLuint y, GLuint z);
		void SetVec3(glm::uvec3 const& value) { SetVec3(value.x, value.y, value.z); }
		void SetVec4(GLuint x, GLuint y, GLuint z, GLuint w);
		void SetVec4(glm::uvec4 const& value) { SetVec4(value.x, value.y, value.z, value.w); }
		void SetVec2(bool x, bool y);
		void SetVec2(glm::bvec2 const& value) { SetVec2(value.x, value.y); }
		void SetVec3(bool x, bool y, bool z);
		void SetVec3(glm::bvec3 const& value) { SetVec3(value.x, value.y, value.z); }
		void SetVec4(bool x, bool y, bool z, bool w);
		void SetVec4(glm::bvec4 const& value) { SetVec4(value.x, value.y, value.z, value.w); }
		void SetMat2(glm::mat2 const& value, bool transpose = false);
		void SetMat2x3(glm::mat2x3 const& value, bool transpose = false);
		void SetMat2x4(glm::mat2x4 const& value, bool transpose = false);
		void SetMat3(glm::mat3 const& value, bool transpose = false);
		void SetMat3x2(glm::mat3x2 const& value, bool transpose = false);
		void SetMat3x4(glm::mat3x4 const& value, bool transpose = false);
		void SetMat4(glm::mat4 const& value, bool transpose = false);
		void SetMat4x2(glm::mat4x2 const& value, bool transpose = false);
		void SetMat4x3(glm::mat4x3 const& value, bool transpose = false);

	private:
		GLuint _programId;
		GLint _index;
		GLint _location;
		GLuint _size;
		Type _type;
		std::string _name;

		void _Populate(GLuint programId, GLuint index, LFRL_COMMON::dynamic_buffer<char> const& nameBuffer);
	};

	static void Use(GLuint id);
	static void Unuse() { Use(NULL); }
	static GLuint GetUsedId();
	static bool IsInUse(GLuint id) { return GetUsedId() == id; }
	static bool IsAnyUsed() { return GetUsedId() != NULL; }
	static std::string GetInfoLog(GLuint id);
	static bool IsFlaggedForDeletion(GLuint id);
	static bool AttachShader(GLuint id, GLuint shaderId);
	static bool DetachShader(GLuint id, GLuint shaderId);
	static ActionResult Link(GLuint id);
	static GLuint GetAttachedShaderCount(GLuint id);
	static GLuint GetAttachedShaderIds(GLuint id, LFRL_COMMON::array_ptr<GLuint> buffer);
	static GLuint GetAttributeCount(GLuint id);
	static GLuint GetAttributes(GLuint id, LFRL_COMMON::array_ptr<Attribute> buffer);
	static void BindAttributeLocation(GLuint id, GLuint location, char const* name);
	static void BindAttributeLocation(GLuint id, GLuint location, std::string const& name) { BindAttributeLocation(id, location, name.data()); }
	static GLuint GetUniformCount(GLuint id);
	static GLuint GetUniforms(GLuint id, LFRL_COMMON::array_ptr<Uniform> buffer);

	ShaderProgram(ShaderProgram const&) = delete;
	ShaderProgram& operator=(ShaderProgram const&) = delete;

	ShaderProgram() noexcept;
	ShaderProgram(ShaderProgram&&) noexcept;
	ShaderProgram& operator=(ShaderProgram&&) noexcept;
	~ShaderProgram() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize();
	ActionResult AttachShader(GLuint shaderId);
	ActionResult AttachShader(ShaderObject const& shader);
	ActionResult DetachShader(GLuint shaderId);
	ActionResult DetachShader(ShaderObject const& shader) { return DetachShader(shader.GetId()); }
	ActionResult Link();

	void BindAttributeLocation(GLuint location, char const* name) { BindAttributeLocation(_id, location, name); }
	void BindAttributeLocation(GLuint location, std::string const& name) { BindAttributeLocation(location, name.data()); }
	void BindAttributeLocation(GLuint location, Attribute const& attribute) { BindAttributeLocation(location, attribute.GetName()); }

	GLuint GetAttachedShaderCount() const { return GetAttachedShaderCount(_id); }
	std::vector<GLuint> GetAttachedShaderIds() const;
	std::unordered_set<GLuint> GetAttachedShaderIdsSet() const;
	GLuint GetAttachedShaderIds(LFRL_COMMON::array_ptr<GLuint> buffer) const { return GetAttachedShaderIds(_id, buffer); }
	
	GLuint GetAttributeCount() const { return GetAttributeCount(_id); }
	std::vector<Attribute> GetAttributes() const;
	std::unordered_map<std::string, Attribute> GetAttributesMap() const;
	GLuint GetAttributes(LFRL_COMMON::array_ptr<Attribute> buffer) const { return GetAttributes(_id, buffer); }

	GLuint GetUniformCount() const { return GetUniformCount(_id); }
	std::vector<Uniform> GetUniforms() const;
	std::unordered_map<std::string, Uniform> GetUniformsMap() const;
	GLuint GetUniforms(LFRL_COMMON::array_ptr<Uniform> buffer) const { return GetUniforms(_id, buffer); }

	void Use() { Use(_id); }
	bool IsInUse() const { return IsInUse(_id); }
	std::string GetInfoLog() const { return GetInfoLog(_id); }
	bool IsFlaggedForDeletion() const { return IsFlaggedForDeletion(_id); }

	ActionResult Dispose();

private:
	GLuint _id;
	ObjectState _state;
};

constexpr GLuint ShaderProgram::Attribute::Type::GetColumnCount(ShaderProgram::Attribute::Type::Code code) noexcept
{
	switch (code)
	{
	case Code::FLOAT:
	case Code::FLOAT_VEC2:
	case Code::FLOAT_VEC3:
	case Code::FLOAT_VEC4:
	case Code::INT:
	case Code::INT_VEC2:
	case Code::INT_VEC3:
	case Code::INT_VEC4:
	case Code::UNSIGNED_INT:
	case Code::UNSIGNED_INT_VEC2:
	case Code::UNSIGNED_INT_VEC3:
	case Code::UNSIGNED_INT_VEC4:
	case Code::DOUBLE:
	case Code::DOUBLE_VEC2:
	case Code::DOUBLE_VEC3:
	case Code::DOUBLE_VEC4:
		return 1;
	case Code::FLOAT_MAT2:
	case Code::FLOAT_MAT2x3:
	case Code::FLOAT_MAT2x4:
	case Code::DOUBLE_MAT2:
	case Code::DOUBLE_MAT2x3:
	case Code::DOUBLE_MAT2x4:
		return 2;
	case Code::FLOAT_MAT3:
	case Code::FLOAT_MAT3x2:
	case Code::FLOAT_MAT3x4:
	case Code::DOUBLE_MAT3:
	case Code::DOUBLE_MAT3x2:
	case Code::DOUBLE_MAT3x4:
		return 3;
	case Code::FLOAT_MAT4:
	case Code::FLOAT_MAT4x2:
	case Code::FLOAT_MAT4x3:
	case Code::DOUBLE_MAT4:
	case Code::DOUBLE_MAT4x2:
	case Code::DOUBLE_MAT4x3:
		return 4;
	}
	return 0;
}

constexpr GLuint ShaderProgram::Attribute::Type::GetRowCount(ShaderProgram::Attribute::Type::Code code) noexcept
{
	auto columnCount = GetColumnCount(code);
	return columnCount == 0 ? 0 : GetScalarCount(code) / columnCount;
}

constexpr GLuint ShaderProgram::Attribute::Type::GetScalarCount(ShaderProgram::Attribute::Type::Code code) noexcept
{
	switch (code)
	{
	case Code::FLOAT:
	case Code::INT:
	case Code::UNSIGNED_INT:
	case Code::DOUBLE:
		return 1;
	case Code::FLOAT_VEC2:
	case Code::INT_VEC2:
	case Code::UNSIGNED_INT_VEC2:
	case Code::DOUBLE_VEC2:
		return 2;
	case Code::FLOAT_VEC3:
	case Code::INT_VEC3:
	case Code::UNSIGNED_INT_VEC3:
	case Code::DOUBLE_VEC3:
		return 3;
	case Code::FLOAT_VEC4:
	case Code::FLOAT_MAT2:
	case Code::INT_VEC4:
	case Code::UNSIGNED_INT_VEC4:
	case Code::DOUBLE_VEC4:
	case Code::DOUBLE_MAT2:
		return 4;
	case Code::FLOAT_MAT2x3:
	case Code::FLOAT_MAT3x2:
	case Code::DOUBLE_MAT2x3:
	case Code::DOUBLE_MAT3x2:
		return 6;
	case Code::FLOAT_MAT2x4:
	case Code::FLOAT_MAT4x2:
	case Code::DOUBLE_MAT2x4:
	case Code::DOUBLE_MAT4x2:
		return 8;
	case Code::FLOAT_MAT3:
	case Code::DOUBLE_MAT3:
		return 9;
	case Code::FLOAT_MAT3x4:
	case Code::FLOAT_MAT4x3:
	case Code::DOUBLE_MAT3x4:
	case Code::DOUBLE_MAT4x3:
		return 12;
	case Code::FLOAT_MAT4:
	case Code::DOUBLE_MAT4:
		return 16;
	}
	return 0;
}

constexpr ShaderProgram::Attribute::Type::Code ShaderProgram::Attribute::Type::GetScalarTypeCode(ShaderProgram::Attribute::Type::Code code) noexcept
{
	switch (code)
	{
	case Code::FLOAT:
	case Code::FLOAT_VEC2:
	case Code::FLOAT_VEC3:
	case Code::FLOAT_VEC4:
	case Code::FLOAT_MAT2:
	case Code::FLOAT_MAT3:
	case Code::FLOAT_MAT4:
	case Code::FLOAT_MAT2x3:
	case Code::FLOAT_MAT2x4:
	case Code::FLOAT_MAT3x2:
	case Code::FLOAT_MAT3x4:
	case Code::FLOAT_MAT4x2:
	case Code::FLOAT_MAT4x3:
		return Code::FLOAT;
	case Code::INT:
	case Code::INT_VEC2:
	case Code::INT_VEC3:
	case Code::INT_VEC4:
		return Code::INT;
	case Code::UNSIGNED_INT:
	case Code::UNSIGNED_INT_VEC2:
	case Code::UNSIGNED_INT_VEC3:
	case Code::UNSIGNED_INT_VEC4:
		return Code::UNSIGNED_INT;
	case Code::DOUBLE:
	case Code::DOUBLE_VEC2:
	case Code::DOUBLE_VEC3:
	case Code::DOUBLE_VEC4:
	case Code::DOUBLE_MAT2:
	case Code::DOUBLE_MAT3:
	case Code::DOUBLE_MAT4:
	case Code::DOUBLE_MAT2x3:
	case Code::DOUBLE_MAT2x4:
	case Code::DOUBLE_MAT3x2:
	case Code::DOUBLE_MAT3x4:
	case Code::DOUBLE_MAT4x2:
	case Code::DOUBLE_MAT4x3:
		return Code::DOUBLE;
	}
	return Code::UNDEFINED;
}

constexpr GLuint ShaderProgram::Attribute::Type::GetScalarSize(ShaderProgram::Attribute::Type::Code code) noexcept
{
	switch (code)
	{
	case Code::FLOAT:
	case Code::FLOAT_VEC2:
	case Code::FLOAT_VEC3:
	case Code::FLOAT_VEC4:
	case Code::FLOAT_MAT2:
	case Code::FLOAT_MAT3:
	case Code::FLOAT_MAT4:
	case Code::FLOAT_MAT2x3:
	case Code::FLOAT_MAT2x4:
	case Code::FLOAT_MAT3x2:
	case Code::FLOAT_MAT3x4:
	case Code::FLOAT_MAT4x2:
	case Code::FLOAT_MAT4x3:
		return sizeof(GLfloat);
	case Code::INT:
	case Code::INT_VEC2:
	case Code::INT_VEC3:
	case Code::INT_VEC4:
		return sizeof(GLint);
	case Code::UNSIGNED_INT:
	case Code::UNSIGNED_INT_VEC2:
	case Code::UNSIGNED_INT_VEC3:
	case Code::UNSIGNED_INT_VEC4:
		return sizeof(GLuint);
	case Code::DOUBLE:
	case Code::DOUBLE_VEC2:
	case Code::DOUBLE_VEC3:
	case Code::DOUBLE_VEC4:
	case Code::DOUBLE_MAT2:
	case Code::DOUBLE_MAT3:
	case Code::DOUBLE_MAT4:
	case Code::DOUBLE_MAT2x3:
	case Code::DOUBLE_MAT2x4:
	case Code::DOUBLE_MAT3x2:
	case Code::DOUBLE_MAT3x4:
	case Code::DOUBLE_MAT4x2:
	case Code::DOUBLE_MAT4x3:
		return sizeof(GLdouble);
	}
	return 0;
}

constexpr ShaderProgram::Attribute::Type ShaderProgram::Attribute::Type::Create(ShaderProgram::Attribute::Type::Code code) noexcept
{
	Type result;
	result._code = code;
	result._columnCount = GetColumnCount(code);
	result._rowCount = GetRowCount(code);
	result._scalarCount = GetScalarCount(code);
	result._scalarTypeCode = GetScalarTypeCode(code);
	result._scalarSize = GetScalarSize(code);
	result._columnSize = GetColumnSize(code);
	result._rowSize = GetRowSize(code);
	result._size = GetSize(code);
	return result;
}

constexpr ShaderProgram::Attribute::Type::Type() noexcept
	: _code(Code::UNDEFINED), _columnCount(0), _rowCount(0), _scalarCount(0), _scalarTypeCode(Code::UNDEFINED), _scalarSize(0), _columnSize(0), _rowSize(0), _size(0)
{}

END_LFRL_OGL_NAMESPACE

#endif
