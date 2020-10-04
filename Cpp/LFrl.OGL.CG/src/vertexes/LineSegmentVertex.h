#ifndef __LFRL_OGL_CG_LINE_SEGMENT_VERTEX_GUARD__
#define __LFRL_OGL_CG_LINE_SEGMENT_VERTEX_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

struct LineSegmentVertex
{
	glm::vec3 start;
	glm::vec2 direction;
	glm::f32 length;
	glm::f32 size;
	glm::vec4 color;
};

END_LFRL_OGL_CG_NAMESPACE

#endif
