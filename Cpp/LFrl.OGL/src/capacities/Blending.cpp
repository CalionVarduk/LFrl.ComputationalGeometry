#include "Blending.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

glm::vec4 Blending::GetColor() noexcept
{
	GLfloat result[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glGetFloatv(GL_BLEND_COLOR, result);
	return glm::vec4(result[0], result[1], result[2], result[3]);
}

void Blending::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) noexcept
{
	glBlendColor(r, g, b, a);
}

void Blending::Func::Set(Blending::Func::Factor sfactor, Blending::Func::Factor dfactor) noexcept
{
	glBlendFunc(static_cast<GLenum>(sfactor), static_cast<GLenum>(dfactor));
}

void Blending::Func::SetSeparate(Blending::Func::Factor sfactorRgb, Blending::Func::Factor dfactorRgb, Blending::Func::Factor sfactorAlpha, Blending::Func::Factor dfactorAlpha) noexcept
{
	glBlendFuncSeparate(static_cast<GLenum>(sfactorRgb), static_cast<GLenum>(dfactorRgb), static_cast<GLenum>(sfactorAlpha), static_cast<GLenum>(dfactorAlpha));
}

Blending::Func::Snapshot Blending::Func::Snapshot::Load() noexcept
{
	Blending::Func::Snapshot result;
	result.sourceRgbFactor = Blending::Func::GetSourceRgbFactor();
	result.destinationRgbFactor = Blending::Func::GetDestinationRgbFactor();
	result.sourceAlphaFactor = Blending::Func::GetSourceAlphaFactor();
	result.destinationAlphaFactor = Blending::Func::GetDestinationAlphaFactor();
	return result;
}

Blending::Func::Snapshot::Snapshot() noexcept
	: sourceRgbFactor(Blending::Func::Factor::ONE),
	destinationRgbFactor(Blending::Func::Factor::ZERO),
	sourceAlphaFactor(Blending::Func::Factor::ONE),
	destinationAlphaFactor(Blending::Func::Factor::ZERO)
{}

void Blending::Func::Snapshot::Apply() noexcept
{
	Blending::Func::SetSeparate(sourceRgbFactor, destinationRgbFactor, sourceAlphaFactor, destinationAlphaFactor);
}

void Blending::Equation::Set(Blending::Equation::Mode mode) noexcept
{
	glBlendEquation(static_cast<GLenum>(mode));
}

void Blending::Equation::SetSeparate(Blending::Equation::Mode rgb, Blending::Equation::Mode alpha) noexcept
{
	glBlendEquationSeparate(static_cast<GLenum>(rgb), static_cast<GLenum>(alpha));
}

Blending::Equation::Snapshot Blending::Equation::Snapshot::Load() noexcept
{
	Blending::Equation::Snapshot result;
	result.rgbMode = Blending::Equation::GetRbgMode();
	result.alphaMode = Blending::Equation::GetAlphaMode();
	return result;
}

Blending::Equation::Snapshot::Snapshot() noexcept
	: rgbMode(Blending::Equation::Mode::FUNC_ADD),
	alphaMode(Blending::Equation::Mode::FUNC_ADD)
{}

void Blending::Equation::Snapshot::Apply() noexcept
{
	Blending::Equation::SetSeparate(rgbMode, alphaMode);
}

void Blending::LogicOp::Set(Blending::LogicOp::Code code) noexcept
{
	glLogicOp(static_cast<GLenum>(code));
}

Blending::LogicOp::Snapshot Blending::LogicOp::Snapshot::Load() noexcept
{
	Blending::LogicOp::Snapshot result;
	result.toggle = Blending::LogicOp::ToggleSnapshot::Load();
	result.code = Blending::LogicOp::CodeSnapshot::Load();
	return result;
}

Blending::LogicOp::Snapshot::Snapshot() noexcept
	: toggle(),
	code()
{}

void Blending::LogicOp::Snapshot::Apply() noexcept
{
	toggle.Apply();
	code.Apply();
}

Blending::Snapshot Blending::Snapshot::Load() noexcept
{
	Blending::Snapshot result;
	result.toggle = Blending::ToggleSnapshot::Load();
	result.color = Blending::ColorSnapshot::Load();
	result.func = Blending::Func::Snapshot::Load();
	result.equation = Blending::Equation::Snapshot::Load();
	result.logicOp = Blending::LogicOp::Snapshot::Load();
	return result;
}

Blending::Snapshot::Snapshot() noexcept
	: toggle(),
	color(),
	func(),
	equation(),
	logicOp()
{}

void Blending::Snapshot::Apply() noexcept
{
	toggle.Apply();
	color.Apply();
	func.Apply();
	equation.Apply();
	logicOp.Apply();
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
