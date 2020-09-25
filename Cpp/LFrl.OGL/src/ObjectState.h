#ifndef __LFRL_OGL_OBJECT_STATE_GUARD__
#define __LFRL_OGL_OBJECT_STATE_GUARD__

#include "internal/namespace_macros.h"

BEGIN_LFRL_OGL_NAMESPACE

enum struct ObjectState
{
	CREATED = 0,
	INIT_FAILURE = 1,
	READY = 2,
	DISPOSED = 3
};

END_LFRL_OGL_NAMESPACE

#endif
