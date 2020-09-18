#ifndef __LFRL_OGL_CAPACITIES_POINTS_GUARD__
#define __LFRL_OGL_CAPACITIES_POINTS_GUARD__

#include "macros.h"
#include "HintType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Points
{
	LFRL_OGL_DEFINE_CAPACITY_GETTER_F32(Size, GLfloat, GL_POINT_SIZE)

	void SetSize(GLfloat value) noexcept;

	LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Size, GLfloat, 1.0f, GetSize, SetSize);

	namespace ProgramSize
	{
		LFRL_OGL_DEFINE_BOOL_CAPACITY_SNAPSHOT_STRUCT(, GL_PROGRAM_POINT_SIZE, false);
	}

	namespace Smoothing
	{
		LFRL_OGL_DEFINE_CAPACITY_GETTER_I32(Hint, HintType, GL_POINT_SMOOTH_HINT)

		void SetHint(HintType hint) noexcept;
		void HintFast() noexcept { SetHint(HintType::FAST); }
		void HintNice() noexcept { SetHint(HintType::NICE); }
		void HintAny() noexcept { SetHint(HintType::ANY); }

		LFRL_OGL_DEFINE_TOGGLE_CAPACITY_SNAPSHOT_STRUCT(GL_POINT_SMOOTH, false);
		LFRL_OGL_DEFINE_CAPACITY_SNAPSHOT_STRUCT(Hint, HintType, HintType::ANY, GetHint, SetHint);
		LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
			ToggleSnapshot toggle;
			HintSnapshot hint;);
	}

	LFRL_OGL_DECLARE_COMPLEX_CAPACITY_SNAPSHOT_STRUCT(
		SizeSnapshot size;
		ProgramSize::Snapshot programSize;
		Smoothing::Snapshot smoothing;);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif