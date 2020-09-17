#include "Lines.h"

BEGIN_LFRL_OGL_NAMESPACE

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

GLenum Lines::Smoothing::GetHint() noexcept
{
	GLint result;
	glGetIntegerv(GL_LINE_SMOOTH_HINT, &result);
	return (GLenum)result;
}

void Lines::Smoothing::HintFast() noexcept
{
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
}

void Lines::Smoothing::HintNice() noexcept
{
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Lines::Smoothing::HintAny() noexcept
{
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
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

END_LFRL_OGL_NAMESPACE
