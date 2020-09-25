#include "ShaderObjectStore.h"

#include <fstream>

BEGIN_LFRL_OGL_NAMESPACE

ShaderObjectStore::ShaderObjectStore() noexcept
	: __detail::object_store_base<ShaderObjectStore, ShaderObject>()
{}

ShaderObject* ShaderObjectStore::Create(ShaderObject::Type type, char const* source)
{
	auto shader = new ShaderObject();
	auto initResult = shader->Initialize(type, source);
	
	if (initResult != ShaderObject::ActionResult::OK)
	{
		delete shader;
		return nullptr;
	}
	Insert(shader);
	return shader;
}

ShaderObject* ShaderObjectStore::Load(ShaderObject::Type type, std::string const& filePath)
{
	auto stream = std::ifstream(filePath);
	if (stream.fail())
		return nullptr;

	stream.seekg(0, stream.end);
	auto length = stream.tellg();
	stream.seekg(0, stream.beg);

	if (length == 0)
		return nullptr;

	LFRL_COMMON::dynamic_buffer<char> buffer(length);
	stream.read(buffer.data(), buffer.size());
	stream.close();

	return Create(type, buffer.data());
}

END_LFRL_OGL_NAMESPACE

