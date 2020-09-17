#include "Stencil.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

GLint Stencil::GetClearValue() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &result);
	return result;
}

void Stencil::SetClearValue(GLint value) noexcept
{
	glClearStencil(value);
}

bool Stencil::Test::IsEnabled() noexcept
{
	return glIsEnabled(GL_STENCIL_TEST);
}

void Stencil::Test::Enable() noexcept
{
	glEnable(GL_STENCIL_TEST);
}

void Stencil::Test::Disable() noexcept
{
	glDisable(GL_STENCIL_TEST);
}

FuncType Stencil::Func::GetFront() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_FUNC, &result);
	return (FuncType)result;
}

GLint Stencil::Func::GetFrontRef() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_REF, &result);
	return result;
}

GLuint Stencil::Func::GetFrontValueMask() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_VALUE_MASK, &result);
	return (GLuint)result;
}

FuncType Stencil::Func::GetBack() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_FUNC, &result);
	return (FuncType)result;
}

GLint Stencil::Func::GetBackRef() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_REF, &result);
	return result;
}

GLuint Stencil::Func::GetBackValueMask() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, &result);
	return (GLuint)result;
}

void Stencil::Func::Set(FuncType func, GLint ref, GLuint mask) noexcept
{
	glStencilFunc((GLenum)func, ref, mask);
}

void Stencil::Func::SetSeparate(FaceType face, FuncType func, GLint ref, GLuint mask) noexcept
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
}

Stencil::Op::Type Stencil::Op::GetFrontStencilFail() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_FAIL, &result);
	return (Stencil::Op::Type)result;
}

Stencil::Op::Type Stencil::Op::GetFrontDepthFail() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &result);
	return (Stencil::Op::Type)result;
}

Stencil::Op::Type Stencil::Op::GetFrontPass() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &result);
	return (Stencil::Op::Type)result;
}

Stencil::Op::Type Stencil::Op::GetBackStencilFail() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_FAIL, &result);
	return (Stencil::Op::Type)result;
}

Stencil::Op::Type Stencil::Op::GetBackDepthFail() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, &result);
	return (Stencil::Op::Type)result;
}

Stencil::Op::Type Stencil::Op::GetBackPass() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, &result);
	return (Stencil::Op::Type)result;
}

void Stencil::Op::Set(Stencil::Op::Type sfail, Stencil::Op::Type dpfail, Stencil::Op::Type dppass) noexcept
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

void Stencil::Op::SetSeparate(FaceType face, Stencil::Op::Type sfail, Stencil::Op::Type dpfail, Stencil::Op::Type dppass) noexcept
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

GLuint Stencil::Mask::GetFront() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_WRITEMASK, &result);
	return (GLuint)result;
}

GLuint Stencil::Mask::GetBack() noexcept
{
	GLint result;
	glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, &result);
	return (GLuint)result;
}

void Stencil::Mask::Set(GLuint mask) noexcept
{
	glStencilMask(mask);
}

void Stencil::Mask::SetSeparate(FaceType face, GLuint mask) noexcept
{
	glStencilMaskSeparate((GLenum)face, mask);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
