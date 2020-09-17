#ifndef __LFRL_OGL_CAPACITIES_LINES_GUARD__
#define __LFRL_OGL_CAPACITIES_LINES_GUARD__

#include "Hint.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Lines
{
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

	GLfloat GetWidth() noexcept;
	void SetWidth(GLfloat value) noexcept;
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
