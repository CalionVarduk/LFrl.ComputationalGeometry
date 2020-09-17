#ifndef __LFRL_OGL_PROJECTION_GUARD__
#define __LFRL_OGL_PROJECTION_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_NAMESPACE

struct Projection final
{
	Projection(Projection const&) noexcept = default;
	Projection(Projection&&) noexcept = default;
	Projection& operator= (Projection const&) noexcept = default;
	Projection& operator= (Projection&&) noexcept = default;

	Projection() noexcept;
	explicit Projection(glm::mat4 const& value) noexcept;

	glm::mat4 const& Get() const noexcept { return _value; }
	void Set(glm::mat4 const& value) noexcept { _value = value; }

	void SetOrthogonal(GLfloat width, GLfloat height, GLfloat zNear = -1000.0f, GLfloat zFar = 1.0f);
	void SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar);

	void Reset() noexcept;
	void Translate(glm::vec3 const& translate) noexcept;
	void Translate(GLfloat x, GLfloat y, GLfloat z) noexcept { Translate(glm::vec3(x, y, z)); }
	void Scale(glm::vec3 const& scale) noexcept;
	void Scale(GLfloat x, GLfloat y, GLfloat z) noexcept { Scale(glm::vec3(x, y, z)); }
	void Rotate(GLfloat angle, glm::vec3 const& rotate) noexcept;
	void Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) noexcept { Rotate(angle, glm::vec3(x, y, z)); }
	void RotateAround(GLfloat angle, glm::vec3 const& origin, glm::vec3 const& rotate) noexcept;
	void RotateAround(GLfloat angle, GLfloat ox, GLfloat oy, GLfloat oz, GLfloat x, GLfloat y, GLfloat z) noexcept { RotateAround(angle, glm::vec3(ox, oy, oz), glm::vec3(x, y, z)); }

private:
	glm::mat4 _value;
};

END_LFRL_OGL_NAMESPACE

#endif
