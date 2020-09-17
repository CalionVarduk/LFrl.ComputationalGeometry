#include "Viewport.h"

BEGIN_LFRL_OGL_NAMESPACE

Viewport Viewport::GetActive() noexcept
{
	GLint* result;
	glGetIntegerv(GL_VIEWPORT, result);
	if (result == NULL)
		return Viewport();

	return Viewport({ result[0], result[1] }, { result[2], result[3] });
}

Viewport::Viewport() noexcept
	: _position({ 0, 0 }), _size({ 0, 0 })
{}

Viewport::Viewport(glm::i32vec2 const& size) noexcept
	: _position({ 0, 0 }), _size(size)
{}

Viewport::Viewport(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept
	: _position(position), _size(size)
{}

void Viewport::Set(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept
{
	SetPosition(position);
	SetSize(size);
}

bool Viewport::IsActive() const noexcept
{
	auto active = GetActive();
	return _position == active._position && _size == active._size;
}

void Viewport::Activate() noexcept
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
}

END_LFRL_OGL_NAMESPACE
