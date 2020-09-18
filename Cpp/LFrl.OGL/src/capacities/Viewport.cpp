#include "Viewport.h"

BEGIN_LFRL_OGL_CAPACITIES_NAMESPACE

Viewport::Snapshot Viewport::Snapshot::Load() noexcept
{
	return Viewport::Get();
}

Viewport::Snapshot::Snapshot() noexcept
	: position({ 0, 0 }), size({ 0, 0 })
{}

Viewport::Snapshot::Snapshot(glm::i32vec2 const& size) noexcept
	: position({ 0, 0 }), size(size)
{}

Viewport::Snapshot::Snapshot(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept
	: position(position), size(size)
{}

void Viewport::Snapshot::Apply() noexcept
{
	Set(*this);
}

Viewport::Snapshot Viewport::Get() noexcept
{
	GLint result[4] = { 0, 0, 0, 0 };
	glGetIntegerv(GL_VIEWPORT, result);
	return Viewport::Snapshot({ result[0], result[1] }, { result[2], result[3] });
}

void Viewport::Set(GLint x, GLint y, GLint width, GLint height) noexcept
{
	glViewport(x, y, width, height);
}

END_LFRL_OGL_CAPACITIES_NAMESPACE
