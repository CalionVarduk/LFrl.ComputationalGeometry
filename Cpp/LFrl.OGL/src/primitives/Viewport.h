#ifndef __LFRL_OGL_VIEWPORT_GUARD__
#define __LFRL_OGL_VIEWPORT_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

struct Viewport final
{
	static Viewport GetActive() noexcept;

	Viewport(Viewport const&) noexcept = default;
	Viewport(Viewport&&) noexcept = default;
	Viewport& operator= (Viewport const&) noexcept = default;
	Viewport& operator= (Viewport&&) noexcept = default;

	Viewport() noexcept;
	explicit Viewport(glm::i32vec2 const& size) noexcept;
	Viewport(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept;

	glm::i32vec2 const& GetPosition() const noexcept { return _position; }
	void SetPosition(glm::i32vec2 const& value) noexcept { _position = value; }

	glm::i32vec2 const& GetSize() const noexcept { return _size; }
	void SetSize(glm::i32vec2 const& value) noexcept { _size = value; }

	void Set(glm::i32vec2 const& position, glm::i32vec2 const& size) noexcept;

	void Reset() noexcept { Set({ 0, 0 }, { 0, 0 }); }

	bool IsActive() const noexcept;
	void Activate() noexcept;

private:
	glm::i32vec2 _position;
	glm::i32vec2 _size;
};

END_LFRL_OGL_NAMESPACE

#endif
