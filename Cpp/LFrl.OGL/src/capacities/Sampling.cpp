#include "Sampling.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

Sampling::Coverage::data Sampling::Coverage::GetValue() noexcept
{
	GLfloat value;
	GLboolean isInverted;
	glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, &value);
	glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT, &isInverted);
	return { value, (bool)isInverted };
}

void Sampling::Coverage::SetValue(GLfloat value, bool isInverted) noexcept
{
	glSampleCoverage(value, isInverted);
}

Sampling::Coverage::Snapshot Sampling::Coverage::Snapshot::Load() noexcept
{
	Sampling::Coverage::Snapshot result;
	result.toggle = Sampling::Coverage::ToggleSnapshot::Load();
	result.value = Sampling::Coverage::ValueSnapshot::Load();
	return result;
}

Sampling::Coverage::Snapshot::Snapshot() noexcept
	: toggle(),
	value()
{}

void Sampling::Coverage::Snapshot::Apply() noexcept
{
	toggle.Apply();
	value.Apply();
}

GLbitfield Sampling::Mask::GetMask() noexcept
{
	GLint result;
	glGetIntegeri_v(GL_SAMPLE_MASK_VALUE, 0, &result);
	return (GLbitfield)result;
}

void Sampling::Mask::SetMask(GLbitfield value) noexcept
{
	glSampleMaski(0, value);
}

Sampling::Mask::Snapshot Sampling::Mask::Snapshot::Load() noexcept
{
	Sampling::Mask::Snapshot result;
	result.toggle = Sampling::Mask::ToggleSnapshot::Load();
	result.value = Sampling::Mask::ValueSnapshot::Load();
	return result;
}

Sampling::Mask::Snapshot::Snapshot() noexcept
	: toggle(),
	value()
{}

void Sampling::Mask::Snapshot::Apply() noexcept
{
	toggle.Apply();
	value.Apply();
}

Sampling::Snapshot Sampling::Snapshot::Load() noexcept
{
	Sampling::Snapshot result;
	result.multi = Sampling::Multi::Snapshot::Load();
	result.alphaToCoverage = Sampling::Alpha::ToCoverage::Snapshot::Load();
	result.alphaToOne = Sampling::Alpha::ToOne::Snapshot::Load();
	result.coverage = Sampling::Coverage::Snapshot::Load();
	result.mask = Sampling::Mask::Snapshot::Load();
	return result;
}

Sampling::Snapshot::Snapshot() noexcept
	: multi(),
	alphaToCoverage(),
	alphaToOne(),
	coverage(),
	mask()
{}

void Sampling::Snapshot::Apply() noexcept
{
	multi.Apply();
	alphaToCoverage.Apply();
	alphaToOne.Apply();
	coverage.Apply();
	mask.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
