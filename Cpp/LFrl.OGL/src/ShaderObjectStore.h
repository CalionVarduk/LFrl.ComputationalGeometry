#ifndef __LFRL_OGL_SHADER_OBJECT_STORE_GUARD__
#define __LFRL_OGL_SHADER_OBJECT_STORE_GUARD__

#include "utils/object_store_base.h"
#include "primitives/ShaderObject.h"

BEGIN_LFRL_OGL_NAMESPACE

class ShaderObjectStore : public __detail::object_store_base<ShaderObjectStore, ShaderObject>
{
	typedef __detail::object_store_base<ShaderObjectStore, ShaderObject> base;
	friend class __detail::object_store_base<ShaderObjectStore, ShaderObject>;

public:
	ShaderObjectStore(ShaderObjectStore const&) = delete;
	ShaderObjectStore& operator=(ShaderObjectStore const&) = delete;

	ShaderObjectStore();
	ShaderObjectStore(ShaderObjectStore&&);
	ShaderObjectStore& operator=(ShaderObjectStore&&);

	ShaderObject* Create(std::string const& name);
	ShaderObject* Create(std::string const& name, ShaderObject::Type type, char const* source);
	ShaderObject* Create(std::string const& name, ShaderObject::Type type, std::string const& source) { return Create(name, type, source.data()); }

	ShaderObject* GetOrCreate(std::string const& name);

private:
	static ObjectState GetState(ShaderObject* shader) noexcept { return shader->GetState(); }
	static GLuint GetId(ShaderObject* shader) noexcept { return shader->GetId(); }
};

END_LFRL_OGL_NAMESPACE

#endif