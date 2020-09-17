#ifndef __LFRL_OGL_BACKGROUND_GUARD__
#define __LFRL_OGL_BACKGROUND_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

struct Background final
{
	Background(Background const&) noexcept = default;
	Background(Background&&) noexcept = default;
	Background& operator= (Background const&) noexcept = default;
	Background& operator= (Background&&) noexcept = default;

	Background() noexcept;
	explicit Background(glm::vec4 const& color, GLbitfield flags = 0) noexcept;

	glm::vec4 const& GetColor() const noexcept { return _color; }
	void SetColor(glm::vec4 const& value) noexcept { _color = value; }
	void SetColor(glm::vec3 const& value) noexcept { SetColor(value.r, value.g, value.b); }
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) noexcept { SetColor(glm::vec4(r, g, b, a)); }
	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255) noexcept { SetColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }

	GLbitfield GetFlags() const noexcept { return _flags; }
	void SetFlags(GLbitfield value) noexcept { _flags = value; }

	void Clear() noexcept;
	void ClearColor() noexcept;
	void ClearFlags() noexcept;

private:
	glm::vec4 _color;
	GLbitfield _flags;
};

END_LFRL_OGL_NAMESPACE

#endif
