#include "FaceCulling.h"

BEGIN_LFRL_OGL_NAMESPACE

bool FaceCulling::IsEnabled() noexcept
{
	return glIsEnabled(GL_CULL_FACE);
}

void FaceCulling::Enable() noexcept
{
	glEnable(GL_CULL_FACE);
}

void FaceCulling::Disable() noexcept
{
	glDisable(GL_CULL_FACE);
}

GLenum FaceCulling::Front::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_FRONT_FACE, &result);
	return (GLenum)result;
}

void FaceCulling::Front::SetCw() noexcept
{
	glFrontFace(GL_CW);
}

void FaceCulling::Front::SetCcw() noexcept
{
	glFrontFace(GL_CCW);
}

GLenum FaceCulling::Cull::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_CULL_FACE_MODE, &result);
	return (GLenum)result;
}

void FaceCulling::Cull::SetFront() noexcept
{
	glCullFace(GL_FRONT);
}

void FaceCulling::Cull::SetBack() noexcept
{
	glCullFace(GL_BACK);
}

void FaceCulling::Cull::SetAll() noexcept
{
	glCullFace(GL_FRONT_AND_BACK);
}

END_LFRL_OGL_NAMESPACE
