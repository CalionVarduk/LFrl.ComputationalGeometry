#ifndef __LFRL_OGL_SHADER_PROGRAM_STORE_GUARD__
#define __LFRL_OGL_SHADER_PROGRAM_STORE_GUARD__

#include "utils/object_store_base.h"
#include "primitives/ShaderProgram.h"

BEGIN_LFRL_OGL_NAMESPACE

class ShaderProgramStore : public __detail::object_store_base<ShaderProgramStore, ShaderProgram>
{
	typedef __detail::object_store_base<ShaderProgramStore, ShaderProgram> base;
	friend class __detail::object_store_base<ShaderProgramStore, ShaderProgram>;

public:
	ShaderProgramStore(ShaderProgramStore const&) = delete;
	ShaderProgramStore& operator=(ShaderProgramStore const&) = delete;

	ShaderProgramStore();
	ShaderProgramStore(ShaderProgramStore&&);
	ShaderProgramStore& operator=(ShaderProgramStore&&);

	ShaderProgram* Create(std::string const& name);
	ShaderProgram* GetOrCreate(std::string const& name);

private:
	static ObjectState GetState(ShaderProgram* program) noexcept { return program->GetState(); }
	static GLuint GetId(ShaderProgram* program) noexcept { return program->GetId(); }
};

END_LFRL_OGL_NAMESPACE

#endif