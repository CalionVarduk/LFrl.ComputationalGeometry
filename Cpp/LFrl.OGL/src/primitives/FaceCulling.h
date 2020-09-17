#ifndef __LFRL_OGL_FACE_CULLING_GUARD__
#define __LFRL_OGL_FACE_CULLING_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace FaceCulling
{
	bool IsEnabled() noexcept;
	void Enable() noexcept;
	void Disable() noexcept;

	namespace Front
	{
		GLenum Get() noexcept;
		void SetCw() noexcept;
		void SetCcw() noexcept;
	}

	namespace Cull
	{
		GLenum Get() noexcept;
		void SetFront() noexcept;
		void SetBack() noexcept;
		void SetAll() noexcept;
	}
}

END_LFRL_OGL_NAMESPACE

#endif
