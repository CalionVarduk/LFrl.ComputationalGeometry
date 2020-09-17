#include "Points.h"

BEGIN_LFRL_OGL_NAMESPACE

bool Points::ProgramSize::IsEnabled() noexcept
{
	return glIsEnabled(GL_PROGRAM_POINT_SIZE);
}

void Points::ProgramSize::Enable() noexcept
{
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void Points::ProgramSize::Disable() noexcept
{
	glDisable(GL_PROGRAM_POINT_SIZE);
}

bool Points::Smoothing::IsEnabled() noexcept
{
	return glIsEnabled(GL_POINT_SMOOTH);
}

void Points::Smoothing::Enable() noexcept
{
	glEnable(GL_POINT_SMOOTH);
}

void Points::Smoothing::Disable() noexcept
{
	glDisable(GL_POINT_SMOOTH);
}

GLenum Points::Smoothing::GetHint() noexcept
{
	GLint result;
	glGetIntegerv(GL_POINT_SMOOTH_HINT, &result);
	return (GLenum)result;
}

void Points::Smoothing::HintFast() noexcept
{
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
}

void Points::Smoothing::HintNice() noexcept
{
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void Points::Smoothing::HintAny() noexcept
{
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
}

GLfloat Points::GetSize() noexcept
{
	GLfloat result;
	glGetFloatv(GL_POINT_SIZE, &result);
	return result;
}

void Points::SetSize(GLfloat value) noexcept
{
	glPointSize(value);
}

END_LFRL_OGL_NAMESPACE
