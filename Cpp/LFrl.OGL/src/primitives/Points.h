#ifndef __LFRL_OGL_POINTS_GUARD__
#define __LFRL_OGL_POINTS_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

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

		GLenum GetHint() noexcept;
		void HintFast() noexcept;
		void HintNice() noexcept;
		void HintAny() noexcept;
	}

	GLfloat GetSize() noexcept;
	void SetSize(GLfloat value) noexcept;
}

END_LFRL_OGL_NAMESPACE

#endif
