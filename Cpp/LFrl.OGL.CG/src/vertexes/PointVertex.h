#ifndef __LFRL_OGL_CG_POINT_VERTEX_GUARD__
#define __LFRL_OGL_CG_POINT_VERTEX_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

struct PointVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::f32 size;
};

END_LFRL_OGL_CG_NAMESPACE

#endif
