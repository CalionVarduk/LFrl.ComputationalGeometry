#ifndef __LFRL_OGL_CAPACITIES_COLOR_GUARD__
#define __LFRL_OGL_CAPACITIES_COLOR_GUARD__

#include "macros.h"
#include "../internal/namespace_macros.h"

#define __LFRL_OGL_COLOR_CLEAR_VALUE_CAPACITY_DEFAULT_VALUE { 0.0f, 0.0f, 0.0f, 0.0f }
#define __LFRL_OGL_COLOR_MASK_CAPACITY_DEFAULT_VALUE { true, true, true, true }

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Color
{
	glm::vec4 GetClearValue() noexcept;
	void SetClearValue(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept;
	void SetClearValue(glm::vec4 const& color) noexcept { SetClearValue(color.r, color.g, color.b, color.a); }
	void SetClearValue(GLubyte r, GLubyte g, GLubyte b, GLubyte a) noexcept { SetClearValue(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(ClearValue, glm::vec4, __LFRL_OGL_COLOR_CLEAR_VALUE_CAPACITY_DEFAULT_VALUE, GetClearValue, SetClearValue);

	namespace Mask
	{
		glm::bvec4 Get() noexcept;
		void Set(bool red, bool green, bool blue, bool alpha) noexcept;
		void Set(glm::bvec4 const& value) noexcept { Set(value.r, value.g, value.b, value.a); }

		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(, glm::bvec4, __LFRL_OGL_COLOR_MASK_CAPACITY_DEFAULT_VALUE, Get, Set);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		ClearValueSnapshot clearValue;
		Mask::Snapshot mask;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#undef __LFRL_OGL_COLOR_CLEAR_VALUE_CAPACITY_DEFAULT_VALUE
#undef __LFRL_OGL_COLOR_MASK_CAPACITY_DEFAULT_VALUE

#endif
