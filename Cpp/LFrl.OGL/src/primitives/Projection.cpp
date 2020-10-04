#include "Projection.h"

BEGIN_LFRL_OGL_NAMESPACE

Projection::Projection() noexcept
	: base()
{}

Projection::Projection(glm::mat4 const& value) noexcept
	: base(value)
{}

void Projection::SetOrthogonal(GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar)
{
	Set(glm::ortho(0.0f, width, 0.0f, height, zNear, zFar));
}

void Projection::SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar)
{
	Set(glm::perspective(fov, width / height, zNear, zFar));
}

END_LFRL_OGL_NAMESPACE
