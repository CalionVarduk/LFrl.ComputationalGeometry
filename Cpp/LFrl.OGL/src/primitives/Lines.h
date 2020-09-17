#ifndef __LFRL_OGL_LINES_GUARD__
#define __LFRL_OGL_LINES_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace Lines
{
	namespace Smoothing
	{
		bool IsEnabled() noexcept;
		void Enable() noexcept;
		void Disable() noexcept;

		GLenum GetHint() noexcept;
		void HintFast() noexcept;
		void HintNice() noexcept;
		void HintAny() noexcept;
	}

	GLfloat GetWidth() noexcept;
	void SetWidth(GLfloat value) noexcept;
}

END_LFRL_OGL_NAMESPACE

#endif
