#include "ShaderProgramStore.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderProgramStore::ShaderProgramStore() noexcept
	: __detail::object_store_base<ShaderProgramStore, ShaderProgram>()
{}

ShaderProgram* ShaderProgramStore::Create()
{
	auto program = new ShaderProgram();
	auto initResult = program->Initialize();

	if (initResult != ShaderProgram::ActionResult::OK)
	{
		delete program;
		return nullptr;
	}
	Insert(program);
	return program;
}

END_LFRL_OGL_NAMESPACE
