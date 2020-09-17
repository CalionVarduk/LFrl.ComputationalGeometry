#ifndef __LFRL_OGL_FACE_CULLING_GUARD__
#define __LFRL_OGL_FACE_CULLING_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace FaceCulling
{
	bool IsEnabled() noexcept;
	void Enable(bool enable = true) noexcept;
	void Disable(bool disable = true) noexcept { Enable(!disable); }

	GLenum GetFrontFace() noexcept;
	void SetFrontFaceCw() noexcept;
	void SetFrontFaceCcw() noexcept;

	GLenum GetCullFace() noexcept;
	void SetCullFaceFront() noexcept;
	void SetCullFaceBack() noexcept;
	void SetCullFaceAll() noexcept;
}

END_LFRL_OGL_NAMESPACE

#endif
