#include "ShaderObjectStore.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderObjectStore::ShaderObjectStore() noexcept
	: __detail::object_store_base<ShaderObjectStore, ShaderObject>()
{}

ShaderObject* ShaderObjectStore::Create(std::string const& name, ShaderObject::Type type, char const* source)
{
	auto shader = new ShaderObject();
	auto initResult = shader->Initialize(type, source);
	
	if (initResult != ShaderObject::ActionResult::OK)
	{
		delete shader;
		return nullptr;
	}
	if (!Insert(name, shader))
	{
		delete shader;
		return nullptr;
	}
	return shader;
}

END_LFRL_OGL_NAMESPACE

