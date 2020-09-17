#include "Dithering.h"

BEGIN_LFRL_OGL_NAMESPACE

bool Dithering::IsEnabled() noexcept
{
	return glIsEnabled(GL_DITHER);
}

void Dithering::Enable() noexcept
{
	glEnable(GL_DITHER);
}

void Dithering::Disable() noexcept
{
	glDisable(GL_DITHER);
}

END_LFRL_OGL_NAMESPACE
