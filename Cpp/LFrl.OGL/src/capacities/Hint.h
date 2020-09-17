#ifndef __LFRL_OGL_CAPACITIES_HINT_GUARD__
#define __LFRL_OGL_CAPACITIES_HINT_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

enum struct Hint
{
	FAST = GL_FASTEST,
	NICE = GL_NICEST,
	ANY = GL_DONT_CARE
};

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
