#include "ShaderObjectStore.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderObjectStore::ShaderObjectStore()
	: base()
{}

ShaderObjectStore::ShaderObjectStore(ShaderObjectStore&& other)
	: base(std::move(other))
{}

ShaderObjectStore& ShaderObjectStore::operator= (ShaderObjectStore&& other)
{
	base::operator=(std::move(other));
	return *this;
}

ShaderObject* ShaderObjectStore::Create(std::string const& name)
{
	auto shader = new ShaderObject();
	if (!Insert(name, shader))
	{
		delete shader;
		return nullptr;
	}
	return shader;
}

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

ShaderObject* ShaderObjectStore::GetOrCreate(std::string const& name)
{
	auto shader = Get(name);
	return shader == nullptr ? Create(name) : shader;
}

END_LFRL_OGL_NAMESPACE

