#include "Sampling.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Sampling::Multi::IsEnabled() noexcept
{
	return glIsEnabled(GL_MULTISAMPLE);
}

void Sampling::Multi::Enable() noexcept
{
	glEnable(GL_MULTISAMPLE);
}

void Sampling::Multi::Disable() noexcept
{
	glDisable(GL_MULTISAMPLE);
}

bool Sampling::Alpha::ToCoverage::IsEnabled() noexcept
{
	return glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Sampling::Alpha::ToCoverage::Enable() noexcept
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void Sampling::Alpha::ToCoverage::Disable() noexcept
{
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

bool Sampling::Alpha::ToOne::IsEnabled() noexcept
{
	return glIsEnabled(GL_SAMPLE_ALPHA_TO_ONE);
}

void Sampling::Alpha::ToOne::Enable() noexcept
{
	glEnable(GL_SAMPLE_ALPHA_TO_ONE);
}

void Sampling::Alpha::ToOne::Disable() noexcept
{
	glDisable(GL_SAMPLE_ALPHA_TO_ONE);
}

bool Sampling::Coverage::IsEnabled() noexcept
{
	return glIsEnabled(GL_SAMPLE_COVERAGE);
}

void Sampling::Coverage::Enable() noexcept
{
	glEnable(GL_SAMPLE_COVERAGE);
}

void Sampling::Coverage::Disable() noexcept
{
	glDisable(GL_SAMPLE_COVERAGE);
}

GLint Sampling::Coverage::GetSize() noexcept
{
	GLint result;
	glGetIntegerv(GL_SAMPLES, &result);
	return result;
}

GLfloat Sampling::Coverage::GetValue() noexcept
{
	GLfloat result;
	glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, &result);
	return result;
}

bool Sampling::Coverage::IsValueInverted() noexcept
{
	GLboolean result;
	glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT, &result);
	return result;
}

void Sampling::Coverage::SetValue(GLfloat value) noexcept
{
	glSampleCoverage(value, GL_FALSE);
}

void Sampling::Coverage::SetValueInverted(GLfloat value) noexcept
{
	glSampleCoverage(value, GL_TRUE);
}

bool Sampling::Mask::IsEnabled() noexcept
{
	return glIsEnabled(GL_SAMPLE_MASK);
}

void Sampling::Mask::Enable() noexcept
{
	glEnable(GL_SAMPLE_MASK);
}

void Sampling::Mask::Disable() noexcept
{
	glDisable(GL_SAMPLE_MASK);
}

GLbitfield Sampling::Mask::GetMasks() noexcept
{
	GLint result;
	glGetIntegeri_v(GL_SAMPLE_MASK_VALUE, 0, &result);
	return (GLbitfield)result;
}

void Sampling::Mask::SetMasks(GLbitfield value) noexcept
{
	glSampleMaski(0, value);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
