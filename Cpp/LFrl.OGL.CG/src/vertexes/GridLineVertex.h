#ifndef __LFRL_OGL_CG_GRID_LINE_VERTEX_GUARD__
#define __LFRL_OGL_CG_GRID_LINE_VERTEX_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

struct GridLineVertex
{
	glm::vec2 positionOffset;
	glm::vec2 axisDirection;
	glm::vec2 lineHalfLength;
	glm::int32 baseLineId;
};

END_LFRL_OGL_CG_NAMESPACE

#endif
