#include "Lines.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

void Lines::SetWidth(GLfloat value) noexcept
{
	glLineWidth(value);
}

void Lines::Smoothing::SetHint(HintType hint) noexcept
{
	glHint(GL_LINE_SMOOTH_HINT, (GLenum)hint);
}

Lines::Smoothing::Snapshot Lines::Smoothing::Snapshot::Load() noexcept
{
	Lines::Smoothing::Snapshot result;
	result.toggle = Lines::Smoothing::ToggleSnapshot::Load();
	result.hint = Lines::Smoothing::HintSnapshot::Load();
	return result;
}

Lines::Smoothing::Snapshot::Snapshot() noexcept
	: toggle(),
	hint()
{}

void Lines::Smoothing::Snapshot::Apply() noexcept
{
	toggle.Apply();
	hint.Apply();
}

Lines::Snapshot Lines::Snapshot::Load() noexcept
{
	Lines::Snapshot result;
	result.width = Lines::WidthSnapshot::Load();
	result.smoothing = Lines::Smoothing::Snapshot::Load();
	return result;
}

Lines::Snapshot::Snapshot() noexcept
	: width(),
	smoothing()
{}

void Lines::Snapshot::Apply() noexcept
{
	width.Apply();
	smoothing.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
