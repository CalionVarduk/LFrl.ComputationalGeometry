#ifndef __LFRL_OGL_SHADER_PROGRAM_GUARD__
#define __LFRL_OGL_SHADER_PROGRAM_GUARD__

#include <vector>
#include "BufferObject.h"
#include "ShaderObject.h"
#include "ShaderVariableType.h"
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
		friend class ShaderProgram;

		enum struct LoadResult
		{
			OK = 0,
			ALREADY_LOADED = 1,
			INVALID_PROGRAM = 2,
			INVALID_INDEX = 3
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

		static ConfigurableType ConvertToConfigurableType(ShaderVariableType::Code code) noexcept;
		static ConfigurableType ConvertToConfigurableType(ShaderVariableType const& type) noexcept;

		Attribute() noexcept;
		Attribute(Attribute const&) = default;
		Attribute(Attribute&&) = default;
		Attribute& operator=(Attribute const&) = default;
		Attribute& operator=(Attribute&&) = default;

		bool IsLoaded() const noexcept { return _index >= 0; }
		GLuint GetProgramId() const noexcept { return _programId; }
		GLint GetIndex() const noexcept { return _index; }
		GLint GetLocation() const noexcept { return _location; }
		GLuint GetSize() const noexcept { return _size; }
		ShaderVariableType const& GetType() const noexcept { return _type; }
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

		// TODO: provide multiple overrides, some automatically attempt to fill in parameters based on type
		// NOTE: GL_DOUBLE required separate implementation
		// size means number of rows (1,2,3,4) + RBGA (or whatever)?
		// type means scalar type + some additional options
		// old has location_size -> row size
		// stride = full object size
		// offset = if object has multiple attributes, this tells where to put specific attribs, kinda like class member offset

		void ConfigureAt(GLuint index, GLuint stride, GLuint offset = 0);
		void ConfigureAt(GLuint index, GLuint size, ConfigurableType type, GLuint stride, GLuint offset = 0, bool normalized = false);

		void Configure(GLuint stride, GLuint offset = 0);
		void Configure(GLuint size, ConfigurableType type, GLuint stride, GLuint offset = 0, bool normalized = false);

	private:
		GLuint _programId;
		GLint _index;
		GLint _location;
		GLuint _size;
		ShaderVariableType _type;
		std::string _name;

		void _Populate(GLuint programId, GLuint index, LFRL_COMMON::dynamic_buffer<char> const& nameBuffer);
	};

	// TODO: add Uniform struct

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
	// TODO: add possibility to bind location (glBindAttribLocation), + non-static version

	ShaderProgram(ShaderProgram const&) = delete;
	ShaderProgram(ShaderProgram&&) = default;
	ShaderProgram& operator=(ShaderProgram const&) = delete;
	ShaderProgram& operator=(ShaderProgram&&) = default;

	ShaderProgram() noexcept;
	~ShaderProgram() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize();
	ActionResult AttachShader(GLuint shaderId);
	ActionResult AttachShader(ShaderObject const& shader);
	ActionResult DetachShader(GLuint shaderId);
	ActionResult DetachShader(ShaderObject const& shader) { return DetachShader(shader.GetId()); }
	ActionResult Link();

	GLuint GetAttachedShaderCount() const { return GetAttachedShaderCount(_id); }
	std::vector<GLuint> GetAttachedShaderIds() const;
	GLuint GetAttachedShaderIds(LFRL_COMMON::array_ptr<GLuint> buffer) const { return GetAttachedShaderIds(_id, buffer); }
	
	GLuint GetAttributeCount() const { return GetAttributeCount(_id); }
	std::vector<Attribute> GetAttributes() const;
	GLuint GetAttributes(LFRL_COMMON::array_ptr<Attribute> buffer) const { return GetAttributes(_id, buffer); }

	void Use() { Use(_id); }
	bool IsInUse() const { return IsInUse(_id); }
	std::string GetInfoLog() const { return GetInfoLog(_id); }
	bool IsFlaggedForDeletion() const { return IsFlaggedForDeletion(_id); }

	ActionResult Dispose();

private:
	GLuint _id;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
