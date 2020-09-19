#ifndef __LFRL_OGL_SHADER_PROGRAM_GUARD__
#define __LFRL_OGL_SHADER_PROGRAM_GUARD__

#include <vector>
#include "ShaderObject.h"

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
		ALREADY_LINKED = 5,
		LINKAGE_FAILURE = 6,
		LINKAGE_VALIDATION_FAILURE = 7,
		ALREADY_DISPOSED = 8,
		NOT_READY = 9
	};

	static void Use(GLuint id);
	static void Unuse() { Use(NULL); }
	static GLuint GetUsedId();
	static bool IsInUse(GLuint id) { return GetUsedId() == id; }
	static bool IsAnyUsed() { return GetUsedId() != NULL; }
	static std::string GetInfoLog(GLuint id);
	static bool IsFlaggedForDeletion(GLuint id);
	static bool AttachShader(GLuint id, GLuint shaderId);
	static ActionResult Link(GLuint id);

	ShaderProgram(ShaderProgram const&) = delete;
	ShaderProgram(ShaderProgram&&) = default;
	ShaderProgram& operator=(ShaderProgram const&) = delete;
	ShaderProgram& operator=(ShaderProgram&&) = default;

	ShaderProgram() noexcept;
	~ShaderProgram() { Dispose(); }

	GLuint GetId() const noexcept { return _id; }
	bool IsLinked() const noexcept { return _isLinked; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize();
	ActionResult AttachShader(GLuint shaderId);
	ActionResult AttachShader(ShaderObject const& shader);
	ActionResult Link();

	void Use() { Use(_id); }
	bool IsInUse() const { return IsInUse(_id); }
	std::string GetInfoLog() const { return GetInfoLog(_id); }
	bool IsFlaggedForDeletion() const { return IsFlaggedForDeletion(_id); }

	ActionResult Dispose();

private:
	GLuint _id;
	bool _isLinked;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
