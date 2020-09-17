#include "Blending.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

bool Blending::IsEnabled() noexcept
{
	return glIsEnabled(GL_BLEND);
}

void Blending::Enable() noexcept
{
	glEnable(GL_BLEND);
}

void Blending::Disable() noexcept
{
	glDisable(GL_BLEND);
}

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

Blending::Func::Factor Blending::Func::GetSourceRgbFactor() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_SRC_RGB, &result);
	return (Blending::Func::Factor)result;
}

Blending::Func::Factor Blending::Func::GetDestinationRgbFactor() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_DST_RGB, &result);
	return (Blending::Func::Factor)result;
}

Blending::Func::Factor Blending::Func::GetSourceAlphaFactor() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &result);
	return (Blending::Func::Factor)result;
}

Blending::Func::Factor Blending::Func::GetDestinationAlphaFactor() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_DST_ALPHA, &result);
	return (Blending::Func::Factor)result;
}

void Blending::Func::Set(Blending::Func::Factor sfactor, Blending::Func::Factor dfactor) noexcept
{
	glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
}

void Blending::Func::SetSeparate(Blending::Func::Factor sfactorRgb, Blending::Func::Factor dfactorRgb, Blending::Func::Factor sfactorAlpha, Blending::Func::Factor dfactorAlpha) noexcept
{
	glBlendFuncSeparate((GLenum)sfactorRgb, (GLenum)dfactorRgb, (GLenum)sfactorAlpha, (GLenum)dfactorAlpha);
}

Blending::Equation::Mode Blending::Equation::GetRbgMode() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_EQUATION_RGB, &result);
	return (Blending::Equation::Mode)result;
}

Blending::Equation::Mode Blending::Equation::GetAlphaMode() noexcept
{
	GLint result;
	glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &result);
	return (Blending::Equation::Mode)result;
}

void Blending::Equation::Set(Blending::Equation::Mode mode) noexcept
{
	glBlendEquation((GLenum)mode);
}

void Blending::Equation::SetSeparate(Blending::Equation::Mode rgb, Blending::Equation::Mode alpha) noexcept
{
	glBlendEquationSeparate((GLenum)rgb, (GLenum)alpha);
}

bool Blending::LogicOp::IsEnabled() noexcept
{
	return glIsEnabled(GL_COLOR_LOGIC_OP);
}

void Blending::LogicOp::Enable() noexcept
{
	glEnable(GL_COLOR_LOGIC_OP);
}

void Blending::LogicOp::Disable() noexcept
{
	glDisable(GL_COLOR_LOGIC_OP);
}

Blending::LogicOp::Code Blending::LogicOp::Get() noexcept
{
	GLint result;
	glGetIntegerv(GL_LOGIC_OP_MODE, &result);
	return (Blending::LogicOp::Code)result;
}

void Blending::LogicOp::Set(Blending::LogicOp::Code code) noexcept
{
	glLogicOp((GLenum)code);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
