#ifndef __LFRL_OGL_CAPACITIES_VIEWPORT_GUARD__
#define __LFRL_OGL_CAPACITIES_VIEWPORT_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Viewport
{
	struct Snapshot final
	{
		static Snapshot Load() noexcept;

		glm::i32vec2 position;
		glm::i32vec2 size;

		Snapshot() noexcept;
		explicit Snapshot(glm::i32vec2 const& size) noexcept;
		Snapshot(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept;

		void Apply() noexcept;
	};

	Snapshot Get() noexcept;
	void Set(GLint x, GLint y, GLint width, GLint height) noexcept;
	void Set(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept { Set(position.x, position.y, size.x, size.y); }
	void Set(Snapshot const& value) noexcept { Set(value.position, value.size); }
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
