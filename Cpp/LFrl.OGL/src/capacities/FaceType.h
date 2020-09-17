#ifndef __LFRL_OGL_CAPACITIES_FACE_TYPE_GUARD__
#define __LFRL_OGL_CAPACITIES_FACE_TYPE_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

enum struct FaceType
{
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	ALL = GL_FRONT_AND_BACK
};

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
