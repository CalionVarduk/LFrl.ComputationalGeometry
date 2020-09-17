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

FaceCulling::FrontOrientation::Type FaceCulling::FrontOrientation::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_FRONT_FACE, &result);
	return (FaceCulling::FrontOrientation::Type)result;
}

void FaceCulling::FrontOrientation::Set(FaceCulling::FrontOrientation::Type type) noexcept
{
	glFrontFace((GLenum)type);
}

FaceType FaceCulling::Cull::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_CULL_FACE_MODE, &result);
	return (FaceType)result;
}

void FaceCulling::Cull::Set(FaceType face) noexcept
{
	glCullFace((GLenum)face);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
