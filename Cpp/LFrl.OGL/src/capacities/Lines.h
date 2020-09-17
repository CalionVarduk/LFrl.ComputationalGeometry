#ifndef __LFRL_OGL_CAPACITIES_LINES_GUARD__
#define __LFRL_OGL_CAPACITIES_LINES_GUARD__

#include "HintType.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Lines
{
	namespace Smoothing
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		HintType GetHint() noexcept;
		void SetHint(HintType hint) noexcept;
		void HintFast() noexcept { SetHint(HintType::FAST); }
		void HintNice() noexcept { SetHint(HintType::NICE); }
		void HintAny() noexcept { SetHint(HintType::ANY); }
	}

	GLfloat GetWidth() noexcept;
	void SetWidth(GLfloat value) noexcept;
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
