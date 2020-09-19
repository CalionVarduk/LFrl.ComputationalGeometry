#ifndef __LFRL_OGL_SHADER_OBJECT_GUARD__
#define __LFRL_OGL_SHADER_OBJECT_GUARD__

#include <array>
#include "../ObjectState.h"
#include "LFrl.Common/src/utils/dynamic_buffer.h"

BEGIN_LFRL_OGL_NAMESPACE

struct ShaderObject final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		UNDEFINED_TYPE = 2,
		NULL_SOURCE = 3,
		SHADER_GEN_FAILURE = 4,
		COMPILATION_FAILURE = 5,
		ALREADY_DISPOSED = 6,
		NOT_READY = 7
	};

	enum struct Type
	{
		UNDEFINED = 0,
		VERTEX = GL_VERTEX_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};

	static Type GetType(GLuint id);
	static std::string GetSource(GLuint id);
	static std::string GetInfoLog(GLuint id);
	static bool Compile(GLuint id);
	static bool IsFlaggedForDeletion(GLuint id);

	ShaderObject(ShaderObject const&) = delete;
	ShaderObject(ShaderObject&&) = default;
	ShaderObject& operator=(ShaderObject const&) = delete;
	ShaderObject& operator=(ShaderObject&&) = default;

	ShaderObject() noexcept;
	~ShaderObject() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	ObjectState GetState() const noexcept { return _state; }
	Type GetType() const noexcept { return _type; }

	ActionResult Initialize(Type type, char const* source);
	ActionResult Initialize(Type type, std::string const& source) { return Initialize(type, source.data()); }
	
	std::string GetSource() const { return GetSource(_id); }
	std::string GetInfoLog() const { return GetInfoLog(_id); }
	bool IsFlaggedForDeletion() const { return IsFlaggedForDeletion(_id); }
	
	ActionResult Dispose();

private:
	GLuint _id;
	Type _type;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
