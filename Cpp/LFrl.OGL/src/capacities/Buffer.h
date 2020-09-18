#ifndef __LFRL_OGL_CAPACITIES_BUFFER_GUARD__
#define __LFRL_OGL_CAPACITIES_BUFFER_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Buffer
{
	enum struct Type
	{
		COLOR = GL_COLOR_BUFFER_BIT,
		DEPTH = GL_DEPTH_BUFFER_BIT,
		ACCUM = GL_ACCUM_BUFFER_BIT,
		STENCIL = GL_STENCIL_BUFFER_BIT
	};

	void Clear(GLbitfield buffers) noexcept;

	GLbitfield operator| (Type l, Type r) noexcept { return (GLbitfield)l | (GLbitfield)r; }
	GLbitfield operator| (Type l, GLbitfield r) noexcept { return (GLbitfield)l | r; }
	GLbitfield operator| (GLbitfield l, Type r) noexcept { return l | (GLbitfield)r; }
	GLbitfield operator|= (GLbitfield l, Type r) noexcept { return l | (GLbitfield)r; }
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
