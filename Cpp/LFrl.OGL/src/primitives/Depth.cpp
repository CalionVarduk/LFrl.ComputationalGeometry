#include "Depth.h"

BEGIN_LFRL_OGL_NAMESPACE

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

Depth::Range::value Depth::Range::Get() noexcept
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

GLenum Depth::Func::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_DEPTH_FUNC, &result);
	return (GLenum)result;
}

void Depth::Func::SetNever() noexcept
{
	glDepthFunc(GL_NEVER);
}

void Depth::Func::SetLt() noexcept
{
	glDepthFunc(GL_LESS);
}

void Depth::Func::SetEq() noexcept
{
	glDepthFunc(GL_EQUAL);
}

void Depth::Func::SetLe() noexcept
{
	glDepthFunc(GL_LEQUAL);
}

void Depth::Func::SetGt() noexcept
{
	glDepthFunc(GL_GREATER);
}

void Depth::Func::SetNe() noexcept
{
	glDepthFunc(GL_NOTEQUAL);
}

void Depth::Func::SetGe() noexcept
{
	glDepthFunc(GL_GEQUAL);
}

void Depth::Func::SetAlways() noexcept
{
	glDepthFunc(GL_ALWAYS);
}

END_LFRL_OGL_NAMESPACE
