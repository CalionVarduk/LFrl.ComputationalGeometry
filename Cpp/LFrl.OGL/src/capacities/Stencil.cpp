#include "Stencil.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

void Stencil::SetClearValue(GLint value) noexcept
{
	glClearStencil(value);
}

Stencil::Func::data Stencil::Func::GetFront() noexcept
{
	GLint func;
	GLint ref;
	GLint valueMask;
	glGetIntegerv(GL_STENCIL_FUNC, &func);
	glGetIntegerv(GL_STENCIL_REF, &ref);
	glGetIntegerv(GL_STENCIL_VALUE_MASK, &valueMask);
	return { (FuncType)func, ref, (GLuint)valueMask };
}

Stencil::Func::data Stencil::Func::GetBack() noexcept
{
	GLint func;
	GLint ref;
	GLint valueMask;
	glGetIntegerv(GL_STENCIL_BACK_FUNC, &func);
	glGetIntegerv(GL_STENCIL_BACK_REF, &ref);
	glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, &valueMask);
	return { (FuncType)func, ref, (GLuint)valueMask };
}

void Stencil::Func::Set(FuncType func, GLint ref, GLuint mask) noexcept
{
	glStencilFunc((GLenum)func, ref, mask);
}

void Stencil::Func::SetSeparate(FaceType face, FuncType func, GLint ref, GLuint mask) noexcept
{
	glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
}

Stencil::Func::Snapshot Stencil::Func::Snapshot::Load() noexcept
{
	Stencil::Func::Snapshot result;
	result.front = Stencil::Func::FrontSnapshot::Load();
	result.back = Stencil::Func::BackSnapshot::Load();
	return result;
}

Stencil::Func::Snapshot::Snapshot() noexcept
	: front(),
	back()
{}

void Stencil::Func::Snapshot::Apply() noexcept
{
	front.Apply();
	back.Apply();
}

Stencil::Op::data Stencil::Op::GetFront() noexcept
{
	GLint stencilFail;
	GLint depthFail;
	GLint pass;
	glGetIntegerv(GL_STENCIL_FAIL, &stencilFail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &depthFail);
	glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &pass);
	return { (Stencil::Op::Type)stencilFail, (Stencil::Op::Type)depthFail, (Stencil::Op::Type)pass };
}

Stencil::Op::data Stencil::Op::GetBack() noexcept
{
	GLint stencilFail;
	GLint depthFail;
	GLint pass;
	glGetIntegerv(GL_STENCIL_BACK_FAIL, &stencilFail);
	glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, &depthFail);
	glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, &pass);
	return { (Stencil::Op::Type)stencilFail, (Stencil::Op::Type)depthFail, (Stencil::Op::Type)pass };
}

void Stencil::Op::Set(Stencil::Op::Type sfail, Stencil::Op::Type dpfail, Stencil::Op::Type dppass) noexcept
{
	glStencilOp((GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

void Stencil::Op::SetSeparate(FaceType face, Stencil::Op::Type sfail, Stencil::Op::Type dpfail, Stencil::Op::Type dppass) noexcept
{
	glStencilOpSeparate((GLenum)face, (GLenum)sfail, (GLenum)dpfail, (GLenum)dppass);
}

Stencil::Op::Snapshot Stencil::Op::Snapshot::Load() noexcept
{
	Stencil::Op::Snapshot result;
	result.front = Stencil::Op::FrontSnapshot::Load();
	result.back = Stencil::Op::BackSnapshot::Load();
	return result;
}

Stencil::Op::Snapshot::Snapshot() noexcept
	: front(),
	back()
{}

void Stencil::Op::Snapshot::Apply() noexcept
{
	front.Apply();
	back.Apply();
}

void Stencil::Mask::Set(GLuint mask) noexcept
{
	glStencilMask(mask);
}

void Stencil::Mask::SetSeparate(FaceType face, GLuint mask) noexcept
{
	glStencilMaskSeparate((GLenum)face, mask);
}

Stencil::Mask::Snapshot Stencil::Mask::Snapshot::Load() noexcept
{
	Stencil::Mask::Snapshot result;
	result.front = Stencil::Mask::FrontSnapshot::Load();
	result.back = Stencil::Mask::BackSnapshot::Load();
	return result;
}

Stencil::Mask::Snapshot::Snapshot() noexcept
	: front(),
	back()
{}

void Stencil::Mask::Snapshot::Apply() noexcept
{
	front.Apply();
	back.Apply();
}

Stencil::Snapshot Stencil::Snapshot::Load() noexcept
{
	Stencil::Snapshot result;
	result.clearValue = Stencil::ClearValueSnapshot::Load();
	result.test = Stencil::Test::Snapshot::Load();
	result.func = Stencil::Func::Snapshot::Load();
	result.op = Stencil::Op::Snapshot::Load();
	result.mask = Stencil::Mask::Snapshot::Load();
	return result;
}

Stencil::Snapshot::Snapshot() noexcept
	: clearValue(),
	test(),
	func(),
	op(),
	mask()
{}

void Stencil::Snapshot::Apply() noexcept
{
	clearValue.Apply();
	test.Apply();
	func.Apply();
	op.Apply();
	mask.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
