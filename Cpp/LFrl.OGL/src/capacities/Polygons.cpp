#include "Polygons.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

Polygons::Mode Polygons::GetMode() noexcept
{
	GLint result;
	glGetIntegerv(GL_POLYGON_MODE, &result);
	return (Polygons::Mode)result;
}

void Polygons::SetMode(Polygons::Mode mode) noexcept
{
	glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
}

Polygons::Offset::data Polygons::Offset::Get() noexcept
{
	GLfloat result[2] = { 0.0f, 0.0f };
	glGetFloatv(GL_POLYGON_OFFSET_FACTOR, result);
	glGetFloatv(GL_POLYGON_OFFSET_UNITS, result + 1);
	return { result[0], result[1] };
}

void Polygons::Offset::Set(GLfloat factor, GLfloat units) noexcept
{
	glPolygonOffset(factor, units);
}

bool Polygons::Offset::Line::IsEnabled() noexcept
{
	return glIsEnabled(GL_POLYGON_OFFSET_LINE);
}

void Polygons::Offset::Line::Enable() noexcept
{
	glEnable(GL_POLYGON_OFFSET_LINE);
}

void Polygons::Offset::Line::Disable() noexcept
{
	glDisable(GL_POLYGON_OFFSET_LINE);
}

bool Polygons::Offset::Point::IsEnabled() noexcept
{
	return glIsEnabled(GL_POLYGON_OFFSET_POINT);
}

void Polygons::Offset::Point::Enable() noexcept
{
	glEnable(GL_POLYGON_OFFSET_POINT);
}

void Polygons::Offset::Point::Disable() noexcept
{
	glDisable(GL_POLYGON_OFFSET_POINT);
}

bool Polygons::Offset::Fill::IsEnabled() noexcept
{
	return glIsEnabled(GL_POLYGON_OFFSET_FILL);
}

void Polygons::Offset::Fill::Enable() noexcept
{
	glEnable(GL_POLYGON_OFFSET_FILL);
}

void Polygons::Offset::Fill::Disable() noexcept
{
	glDisable(GL_POLYGON_OFFSET_FILL);
}

bool Polygons::Smoothing::IsEnabled() noexcept
{
	return glIsEnabled(GL_POLYGON_SMOOTH);
}

void Polygons::Smoothing::Enable() noexcept
{
	glEnable(GL_POLYGON_SMOOTH);
}

void Polygons::Smoothing::Disable() noexcept
{
	glDisable(GL_POLYGON_SMOOTH);
}

Hint Polygons::Smoothing::GetHint() noexcept
{
	GLint result;
	glGetIntegerv(GL_POLYGON_SMOOTH_HINT, &result);
	return (Hint)result;
}

void Polygons::Smoothing::SetHint(Hint hint) noexcept
{
	glHint(GL_POLYGON_SMOOTH_HINT, (GLenum)hint);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
