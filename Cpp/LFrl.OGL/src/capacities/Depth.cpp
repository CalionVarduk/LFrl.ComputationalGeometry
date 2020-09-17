#include "Depth.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Depth::IsReadonly() noexcept
{
	GLboolean result;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &result);
	return result;
}

void Depth::MakeWritable() noexcept
{
	glDepthMask(GL_TRUE);
}

void Depth::MakeReadonly() noexcept
{
	glDepthMask(GL_FALSE);
}

GLdouble Depth::GetClearValue() noexcept
{
	GLdouble result;
	glGetDoublev(GL_DEPTH_CLEAR_VALUE, &result);
	return result;
}

void Depth::SetClearValue(GLdouble value) noexcept
{
	glClearDepth(value);
}

bool Depth::Test::IsEnabled() noexcept
{
	return glIsEnabled(GL_DEPTH_TEST);
}

void Depth::Test::Enable() noexcept
{
	glEnable(GL_DEPTH_TEST);
}

void Depth::Test::Disable() noexcept
{
	glDisable(GL_DEPTH_TEST);
}

Depth::Range::data Depth::Range::Get() noexcept
{
	GLdouble result[2] = { 0.0, 0.0 };
	glGetDoublev(GL_DEPTH_RANGE, result);
	return { result[0], result[1] };
}

void Depth::Range::Set(GLdouble zNear, GLdouble zFar) noexcept
{
	glDepthRange(zNear, zFar);
}

bool Depth::Clamping::IsEnabled() noexcept
{
	return glIsEnabled(GL_DEPTH_CLAMP);
}

void Depth::Clamping::Enable() noexcept
{
	glEnable(GL_DEPTH_CLAMP);
}

void Depth::Clamping::Disable() noexcept
{
	glDisable(GL_DEPTH_CLAMP);
}

Depth::Func::Type Depth::Func::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_DEPTH_FUNC, &result);
	return (Depth::Func::Type)result;
}

void Depth::Func::Set(Depth::Func::Type type) noexcept
{
	glDepthFunc((GLenum)type);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
