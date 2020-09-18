#include "Buffer.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

void Buffer::Clear(GLbitfield buffers) noexcept
{
	glClear(buffers);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
