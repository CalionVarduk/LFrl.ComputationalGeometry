#ifndef __LFRL_OGL_CG_SHADER_STORE_GUARD__
#define __LFRL_OGL_CG_SHADER_STORE_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.OGL/src/ShaderStore.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

ShaderStore& GetShaderStore();

END_LFRL_OGL_CG_NAMESPACE

#define sShaders LFRL_OGL_CG::GetShaderStore()
#define sShaderObjects sShaders.GetObjects()
#define sShaderPrograms sShaders.GetPrograms()

#endif
