#include "Points.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

void Points::SetSize(GLfloat value) noexcept
{
	glPointSize(value);
}

Points::Smoothing::Snapshot Points::Smoothing::Snapshot::Load() noexcept
{
	Points::Smoothing::Snapshot result;
	result.toggle = Points::Smoothing::ToggleSnapshot::Load();
	result.hint = Points::Smoothing::HintSnapshot::Load();
	return result;
}

Points::Smoothing::Snapshot::Snapshot() noexcept
	: toggle(),
	hint()
{}

void Points::Smoothing::Snapshot::Apply() noexcept
{
	toggle.Apply();
	hint.Apply();
}

void Points::Params::SetThresholdSize(GLfloat value) noexcept
{
	glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, value);
}
void Points::Params::SetSpriteOrigin(Points::Params::SpriteOrigin value) noexcept
{
	glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, (GLint)value);
}

Points::Params::Snapshot Points::Params::Snapshot::Load() noexcept
{
	Points::Params::Snapshot result;
	result.thresholdSize = Points::Params::ThresholdSizeSnapshot::Load();
	result.spriteOrigin = Points::Params::SpriteOriginSnapshot::Load();
	return result;
}

Points::Params::Snapshot::Snapshot() noexcept
	: thresholdSize(),
	spriteOrigin()
{}

void Points::Params::Snapshot::Apply() noexcept
{
	thresholdSize.Apply();
	spriteOrigin.Apply();
}

Points::Snapshot Points::Snapshot::Load() noexcept
{
	Points::Snapshot result;
	result.size = Points::SizeSnapshot::Load();
	result.programSize = Points::ProgramSize::Snapshot::Load();
	result.smoothing = Points::Smoothing::Snapshot::Load();
	result.params = Points::Params::Snapshot::Load();
	return result;
}

Points::Snapshot::Snapshot() noexcept
	: size(),
	programSize(),
	smoothing(),
	params()
{}

void Points::Snapshot::Apply() noexcept
{
	size.Apply();
	programSize.Apply();
	smoothing.Apply();
	params.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
