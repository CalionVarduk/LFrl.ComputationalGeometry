#ifndef __LFRL_OGL_PROJECTION_GUARD__
#define __LFRL_OGL_PROJECTION_GUARD__

#include "Transform.h"

BEGIN_LFRL_OGL_NAMESPACE

struct Projection : public Transform
{
	typedef Transform base;

	Projection(Projection const&) noexcept = default;
	Projection(Projection&&) noexcept = default;
	Projection& operator= (Projection const&) noexcept = default;
	Projection& operator= (Projection&&) noexcept = default;

	Projection() noexcept;
	explicit Projection(glm::mat4 const& value) noexcept;

	void SetOrthogonal(GLfloat width, GLfloat height, GLfloat zNear = -1000.0f, GLfloat zFar = 1.0f);
	void SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar);
};

END_LFRL_OGL_NAMESPACE

#endif
