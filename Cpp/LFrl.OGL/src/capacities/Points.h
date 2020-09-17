#ifndef __LFRL_OGL_CAPACITIES_POINTS_GUARD__
#define __LFRL_OGL_CAPACITIES_POINTS_GUARD__

#include "Hint.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Points
{
	namespace ProgramSize
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;
	}

	namespace Smoothing
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		Hint GetHint() noexcept;
		void SetHint(Hint hint) noexcept;
		void HintFast() noexcept { SetHint(Hint::FAST); }
		void HintNice() noexcept { SetHint(Hint::NICE); }
		void HintAny() noexcept { SetHint(Hint::ANY); }
	}

	GLfloat GetSize() noexcept;
	void SetSize(GLfloat value) noexcept;
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
