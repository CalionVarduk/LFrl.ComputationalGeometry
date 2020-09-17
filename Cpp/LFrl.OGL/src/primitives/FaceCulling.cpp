#include "FaceCulling.h"

BEGIN_LFRL_OGL_NAMESPACE

bool FaceCulling::IsEnabled() noexcept
{
	return glIsEnabled(GL_CULL_FACE);
}

void FaceCulling::Enable(bool enable) noexcept
{
	if (enable)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

GLenum FaceCulling::GetFrontFace() noexcept
{
	GLint result;
	glGetIntegerv(GL_FRONT_FACE, &result);
	return result;
}

void FaceCulling::SetFrontFaceCw() noexcept
{
	glFrontFace(GL_CW);
}

void FaceCulling::SetFrontFaceCcw() noexcept
{
	glFrontFace(GL_CCW);
}

GLenum FaceCulling::GetCullFace() noexcept
{
	GLint result;
	glGetIntegerv(GL_CULL_FACE_MODE, &result);
	return result;
}

void FaceCulling::SetCullFaceFront() noexcept
{
	glCullFace(GL_FRONT);
}

void FaceCulling::SetCullFaceBack() noexcept
{
	glCullFace(GL_BACK);
}

void FaceCulling::SetCullFaceAll() noexcept
{
	glCullFace(GL_FRONT_AND_BACK);
}

END_LFRL_OGL_NAMESPACE
