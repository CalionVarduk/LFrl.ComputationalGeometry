#include "Lines.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Lines::Smoothing::IsEnabled() noexcept
{
	return glIsEnabled(GL_LINE_SMOOTH);
}

void Lines::Smoothing::Enable() noexcept
{
	glEnable(GL_LINE_SMOOTH);
}

void Lines::Smoothing::Disable() noexcept
{
	glDisable(GL_LINE_SMOOTH);
}

Hint Lines::Smoothing::GetHint() noexcept
{
	GLint result;
	glGetIntegerv(GL_LINE_SMOOTH_HINT, &result);
	return (Hint)result;
}

void Lines::Smoothing::SetHint(Hint hint) noexcept
{
	glHint(GL_LINE_SMOOTH_HINT, (GLenum)hint);
}

GLfloat Lines::GetWidth() noexcept
{
	GLfloat result;
	glGetFloatv(GL_LINE_WIDTH, &result);
	return result;
}

void Lines::SetWidth(GLfloat value) noexcept
{
	glLineWidth(value);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
