#include "FaceCulling.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

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

FaceCulling::Front::Type FaceCulling::Front::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_FRONT_FACE, &result);
	return (FaceCulling::Front::Type)result;
}

void FaceCulling::Front::Set(FaceCulling::Front::Type type) noexcept
{
	glFrontFace((GLenum)type);
}

FaceCulling::Cull::Type FaceCulling::Cull::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_CULL_FACE_MODE, &result);
	return (FaceCulling::Cull::Type)result;
}

void FaceCulling::Cull::Set(FaceCulling::Cull::Type type) noexcept
{
	glCullFace((GLenum)type);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
