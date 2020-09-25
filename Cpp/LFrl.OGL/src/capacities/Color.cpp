#include "Color.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

glm::vec4 Color::GetClearValue() noexcept
{
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glGetFloatv(GL_COLOR_CLEAR_VALUE, result);
	return { result[0], result[1], result[2], result[3] };
}

void Color::SetClearValue(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept
{
	glClearColor(r, g, b, a);
}

glm::bvec4 Color::Mask::Get() noexcept
{
	GLboolean result[4] = { false, false, false, false };
	glGetBooleanv(GL_COLOR_WRITEMASK, result);
	return { result[0], result[1], result[2], result[3] };
}

void Color::Mask::Set(bool red, bool green, bool blue, bool alpha) noexcept
{
	glColorMask(red, green, blue, alpha);
}

Color::Snapshot Color::Snapshot::Load() noexcept
{
	Color::Snapshot result;
	result.clearValue = Color::ClearValueSnapshot::Load();
	result.mask = Color::Mask::Snapshot::Load();
	return result;
}

Color::Snapshot::Snapshot() noexcept
	: clearValue(),
	mask()
{}

void Color::Snapshot::Apply() noexcept
{
	clearValue.Apply();
	mask.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
