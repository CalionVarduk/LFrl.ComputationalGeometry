#include "Transform.h"

BEGIN_LFRL_OGL_NAMESPACE

Transform::Transform() noexcept
	: _value(glm::identity<glm::mat4>())
{}

Transform::Transform(glm::mat4 const& value) noexcept
	: _value(value)
{}

void Transform::Reset() noexcept
{
	_value = glm::identity<glm::mat4>();
}

void Transform::Translate(glm::vec3 const& translate) noexcept
{
	_value = glm::translate(_value, translate);
}

void Transform::Scale(glm::vec3 const& scale) noexcept
{
	_value = glm::scale(_value, scale);
}

void Transform::Rotate(GLfloat angle, glm::vec3 const& rotate) noexcept
{
	_value = glm::rotate(_value, angle, rotate);
}

void Transform::RotateAround(GLfloat angle, glm::vec3 const& origin, glm::vec3 const& rotate) noexcept
{
	Translate(-origin);
	Rotate(angle, rotate);
	Translate(origin);
}

END_LFRL_OGL_NAMESPACE
