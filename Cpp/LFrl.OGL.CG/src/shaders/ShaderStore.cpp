#include "ShaderStore.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

ShaderStore& GetShaderStore()
{
	static ShaderStore store;
	return store;
}

END_LFRL_OGL_CG_NAMESPACE
