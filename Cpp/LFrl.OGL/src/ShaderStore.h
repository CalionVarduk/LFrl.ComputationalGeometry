#ifndef __LFRL_OGL_SHADER_STORE_GUARD__
#define __LFRL_OGL_SHADER_STORE_GUARD__

#include "ShaderObjectStore.h"
#include "ShaderProgramStore.h"

BEGIN_LFRL_OGL_NAMESPACE

class ShaderStore
{
public:
	ShaderStore(ShaderStore const&) = delete;
	ShaderStore(ShaderStore&&) = default;
	ShaderStore& operator=(ShaderStore const&) = delete;
	ShaderStore& operator=(ShaderStore&&) = default;

	ShaderStore() noexcept;
	explicit ShaderStore(std::string const& shaderDirectory);
	ShaderStore(std::string const& shaderDirectory, std::string const& shaderExtension);

	ShaderObjectStore& GetObjects() noexcept { return _objects; }
	ShaderObjectStore const& GetObjects() const noexcept { return _objects; }
	ShaderProgramStore& GetPrograms() noexcept { return _programs; }
	ShaderProgramStore const& GetPrograms() const noexcept { return _programs; }

	std::string const& GetShaderDirectory() const noexcept { return _shaderDirectory; }
	void SetShaderDirectory(std::string const& value) { _shaderDirectory = value; }

	std::string const& GetShaderExtension() const noexcept { return _shaderExtension; }
	void SetShaderExtension(std::string const& value) { _shaderExtension = value; }

	ShaderObject* Load(ShaderObject::Type type, std::string const& fileName);

private:
	std::string _shaderDirectory;
	std::string _shaderExtension;
	ShaderObjectStore _objects;
	ShaderProgramStore _programs;
};

END_LFRL_OGL_NAMESPACE

#endif
