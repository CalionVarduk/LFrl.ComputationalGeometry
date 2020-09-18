#include "Polygons.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

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

Polygons::Offset::Snapshot Polygons::Offset::Snapshot::Load() noexcept
{
	Polygons::Offset::Snapshot result;
	result.offset = Polygons::Offset::OffsetSnapshot::Load();
	result.line = Polygons::Offset::Line::Snapshot::Load();
	result.point = Polygons::Offset::Point::Snapshot::Load();
	result.fill = Polygons::Offset::Fill::Snapshot::Load();
	return result;
}

Polygons::Offset::Snapshot::Snapshot() noexcept
	: offset(),
	line(),
	point(),
	fill()
{}

void Polygons::Offset::Snapshot::Apply() noexcept
{
	offset.Apply();
	line.Apply();
	point.Apply();
	fill.Apply();
}

void Polygons::Smoothing::SetHint(HintType hint) noexcept
{
	glHint(GL_POLYGON_SMOOTH_HINT, (GLenum)hint);
}

Polygons::Smoothing::Snapshot Polygons::Smoothing::Snapshot::Load() noexcept
{
	Polygons::Smoothing::Snapshot result;
	result.toggle = Polygons::Smoothing::ToggleSnapshot::Load();
	result.hint = Polygons::Smoothing::HintSnapshot::Load();
	return result;
}

Polygons::Smoothing::Snapshot::Snapshot() noexcept
	: toggle(),
	hint()
{}

void Polygons::Smoothing::Snapshot::Apply() noexcept
{
	toggle.Apply();
	hint.Apply();
}

Polygons::Snapshot Polygons::Snapshot::Load() noexcept
{
	Polygons::Snapshot result;
	result.mode = Polygons::ModeSnapshot::Load();
	result.offset = Polygons::Offset::Snapshot::Load();
	result.smoothing = Polygons::Smoothing::Snapshot::Load();
	return result;
}

Polygons::Snapshot::Snapshot() noexcept
	: mode(),
	offset(),
	smoothing()
{}

void Polygons::Snapshot::Apply() noexcept
{
	mode.Apply();
	offset.Apply();
	smoothing.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
