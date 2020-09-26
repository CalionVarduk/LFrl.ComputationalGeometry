#include "ShaderStore.h"

#include <fstream>

BEGIN_LFRL_OGL_NAMESPACE

ShaderStore::ShaderStore() noexcept
	: _shaderDirectory("./shaders"), _shaderExtension("glsl"), _objects(), _programs()
{}

ShaderStore::ShaderStore(std::string const& shaderDirectory)
	: _shaderDirectory(shaderDirectory), _shaderExtension("glsl"), _objects(), _programs()
{}

ShaderStore::ShaderStore(std::string const& shaderDirectory, std::string const& shaderExtension)
	: _shaderDirectory(shaderDirectory), _shaderExtension(shaderExtension), _objects(), _programs()
{}

ShaderObject* ShaderStore::Load(ShaderObject::Type type, std::string const& fileName)
{
	auto shader = _objects.Get(fileName);
	if (shader != nullptr)
		return shader->GetType() == type ? shader : nullptr;

	auto filePath = _shaderDirectory + "/" + fileName + "." + _shaderExtension;
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

	return _objects.Create(fileName, type, buffer.data());
}

END_LFRL_OGL_NAMESPACE
