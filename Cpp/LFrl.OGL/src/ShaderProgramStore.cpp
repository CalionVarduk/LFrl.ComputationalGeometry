#include "ShaderProgramStore.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderProgramStore::ShaderProgramStore() noexcept
	: __detail::object_store_base<ShaderProgramStore, ShaderProgram>()
{}

ShaderProgram* ShaderProgramStore::Create(std::string const& name)
{
	auto program = new ShaderProgram();
	auto initResult = program->Initialize();

	if (initResult != ShaderProgram::ActionResult::OK)
	{
		delete program;
		return nullptr;
	}
	if (!Insert(name, program))
	{
		delete program;
		return nullptr;
	}
	return program;
}

END_LFRL_OGL_NAMESPACE
