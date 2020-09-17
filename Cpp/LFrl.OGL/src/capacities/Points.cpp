#include "Points.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

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

Hint Points::Smoothing::GetHint() noexcept
{
	GLint result;
	glGetIntegerv(GL_POINT_SMOOTH_HINT, &result);
	return (Hint)result;
}

void Points::Smoothing::SetHint(Hint hint) noexcept
{
	glHint(GL_POINT_SMOOTH_HINT, (GLenum)hint);
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

END_LFRL_OGL_CAPACITIES_NAMESPACE
