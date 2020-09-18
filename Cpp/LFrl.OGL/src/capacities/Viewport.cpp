#include "Viewport.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

Viewport::data Viewport::Get() noexcept
{
	GLint result[4] = { 0, 0, 0, 0 };
	glGetIntegerv(GL_VIEWPORT, result);
	return { { result[0], result[1] }, { result[2], result[3] } };
}

void Viewport::Set(GLint x, GLint y, GLint width, GLint height) noexcept
{
	glViewport(x, y, width, height);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
