#include "Projection.h"

BEGIN_LFRL_OGL_NAMESPACE

Projection::Projection() noexcept
	: _value(glm::identity<glm::mat4>())
{}

void Projection::SetOrthogonal(GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar)
{
	_value = glm::ortho(0.0f, width, height, 0.0f, zNear, zFar);
}

void Projection::SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar)
{
	_value = glm::perspective(fov, width / height, zNear, zFar);
}

void Projection::Reset() noexcept
{
	_value = glm::identity<glm::mat4>();
}

void Projection::Translate(glm::vec3 const& translate) noexcept
{
	_value = glm::translate(_value, translate);
}

void Projection::Scale(glm::vec3 const& scale) noexcept
{
	_value = glm::scale(_value, scale);
}

void Projection::Rotate(GLfloat angle, glm::vec3 const& rotate) noexcept
{
	_value = glm::rotate(_value, angle, rotate);
}

void Projection::RotateAround(GLfloat angle, glm::vec3 const& origin, glm::vec3 const& rotate) noexcept
{
	Translate(-origin);
	Rotate(angle, rotate);
	Translate(origin);
}

END_LFRL_OGL_NAMESPACE
