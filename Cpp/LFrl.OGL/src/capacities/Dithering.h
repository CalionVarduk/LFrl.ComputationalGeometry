#ifndef __LFRL_OGL_CAPACITIES_DITHERING_GUARD__
#define __LFRL_OGL_CAPACITIES_DITHERING_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

namespace Dithering
{
	bool IsEnabled() noexcept;
	void Enable() noexcept;
	void Disable() noexcept;
}

END_LFRL_OGL_CAPACITIES_NAMESPACE

#endif
