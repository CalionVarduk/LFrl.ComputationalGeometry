#include "Background.h"

BEGIN_LFRL_OGL_NAMESPACE

Background::Background() noexcept
	: _color({ 0.0f, 0.0f, 0.0f, 1.0f }), _flags(0)
{}

Background::Background(glm::vec4 const& color, GLbitfield flags) noexcept
	: _color(color), _flags(flags)
{}

void Background::Clear() noexcept
{
	ClearColor();
	if (_flags != 0)
		ClearFlags();
}

void Background::ClearColor() noexcept
{
	glClearColor(_color.r, _color.g, _color.b, _color.a);
}

void Background::ClearFlags() noexcept
{
	glClear(_flags);
}

END_LFRL_OGL_NAMESPACE
