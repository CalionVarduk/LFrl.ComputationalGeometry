#ifndef __LFRL_OGL_ACCESS_TYPE_GUARD__
#define __LFRL_OGL_ACCESS_TYPE_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_NAMESPACE

enum struct AccessType
{
	READ_ONLY = GL_READ_ONLY,
	WRITE_ONLY = GL_WRITE_ONLY,
	READ_WRITE = GL_READ_WRITE
};

END_LFRL_OGL_NAMESPACE

#endif
