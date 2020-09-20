#ifndef __LFRL_OGL_SHADER_OBJECT_STORE_GUARD__
#define __LFRL_OGL_SHADER_OBJECT_STORE_GUARD__

#include "utils/object_store_base.h"
#include "primitives/ShaderObject.h"

BEGIN_LFRL_OGL_NAMESPACE

class ShaderObjectStore : public __detail::object_store_base<ShaderObjectStore, ShaderObject>
{
	friend class __detail::object_store_base<ShaderObjectStore, ShaderObject>;

public:
	ShaderObjectStore(ShaderObjectStore const&) = delete;
	ShaderObjectStore(ShaderObjectStore&&) = default;
	ShaderObjectStore& operator=(ShaderObjectStore const&) = delete;
	ShaderObjectStore& operator=(ShaderObjectStore&&) = default;

	ShaderObjectStore() noexcept;

	ShaderObject* Create(ShaderObject::Type type, char const* source);
	ShaderObject* Create(ShaderObject::Type type, std::string const& source) { return Create(type, source.data()); }
	ShaderObject* Load(ShaderObject::Type type, std::string const& filePath);

private:
	static ObjectState GetState(ShaderObject* shader) noexcept { return shader->GetState(); }
	static GLuint GetId(ShaderObject* shader) noexcept { return shader->GetId(); }
};

END_LFRL_OGL_NAMESPACE

#endif