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

Points::Snapshot Points::Snapshot::Load() noexcept
{
	Points::Snapshot result;
	result.size = Points::SizeSnapshot::Load();
	result.programSize = Points::ProgramSize::Snapshot::Load();
	result.smoothing = Points::Smoothing::Snapshot::Load();
	return result;
}

Points::Snapshot::Snapshot() noexcept
	: size(),
	programSize(),
	smoothing()
{}

void Points::Snapshot::Apply() noexcept
{
	size.Apply();
	programSize.Apply();
	smoothing.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
