#ifndef __LFRL_OGL_CAPACITIES_LINES_GUARD__
#define __LFRL_OGL_CAPACITIES_LINES_GUARD__

#include "macros.h"
#include "HintType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Lines
{
	LFRL_OGL_DEFINE_CAPACITY_GETTER_F32(Width, GLfloat, GL_LINE_WIDTH)

	void SetWidth(GLfloat value) noexcept;

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Width, GLfloat, 1.0f, GetWidth, SetWidth);

	namespace Smoothing
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Hint, HintType, GL_LINE_SMOOTH_HINT)

		void SetHint(HintType hint) noexcept;
		inline void HintFast() noexcept { SetHint(HintType::FAST); }
		inline void HintNice() noexcept { SetHint(HintType::NICE); }
		inline void HintAny() noexcept { SetHint(HintType::ANY); }

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_LINE_SMOOTH, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Hint, HintType, HintType::ANY, GetHint, SetHint);
		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			HintSnapshot hint;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		WidthSnapshot width;
		Smoothing::Snapshot smoothing;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
