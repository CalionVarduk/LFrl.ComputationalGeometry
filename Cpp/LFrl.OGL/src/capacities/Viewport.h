#ifndef __LFRL_OGL_CAPACITIES_VIEWPORT_GUARD__
#define __LFRL_OGL_CAPACITIES_VIEWPORT_GUARD__

#include "macros.h"
#include "../internal/namespace_macros.h"

#define __LFRL_OGL_VIEWPORT_CAPACITY_DEFAULT_VALUE { { 0, 0 }, { 0, 0 } }

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Viewport
{
	struct data final
	{
		glm::i32vec2 position;
		glm::i32vec2 size;
	};

	data Get() noexcept;
	void Set(GLint x, GLint y, GLint width, GLint height) noexcept;
	void Set(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept { Set(position.x, position.y, size.x, size.y); }
	void Set(data value) noexcept { Set(value.position, value.size); }

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(, data, __LFRL_OGL_VIEWPORT_CAPACITY_DEFAULT_VALUE, Get, Set);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_VIEWPORT_CAPACITY_DEFAULT_VALUE

#endif
