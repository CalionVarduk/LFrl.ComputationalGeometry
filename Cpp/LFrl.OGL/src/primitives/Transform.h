#ifndef __LFRL_OGL_TRANSFORM_GUARD__
#define __LFRL_OGL_TRANSFORM_GUARD__

#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_NAMESPACE

struct Transform
{
	Transform(Transform const&) noexcept = default;
	Transform(Transform&&) noexcept = default;
	Transform& operator= (Transform const&) noexcept = default;
	Transform& operator= (Transform&&) noexcept = default;

	Transform() noexcept;
	explicit Transform(glm::mat4 const& value) noexcept;

	glm::mat4 const& Get() const noexcept { return _value; }
	void Set(glm::mat4 const& value) noexcept { _value = value; }

	glm::vec4 GetColumn(GLint index) const { return _value[index]; }
	void SetColumn(GLint index, glm::vec4 const& value) { _value[index] = value; }
	void SetColumn(GLint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { SetColumn(index, glm::vec4(x, y, z, w)); }
	
	glm::vec4 GetRow(GLint index) const { return glm::vec4(_value[0][index], _value[1][index], _value[2][index], _value[3][index]); }
	void SetRow(GLint index, glm::vec4 const& value);
	void SetRow(GLint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { SetRow(index, glm::vec4(x, y, z, w)); }
	
	GLfloat GetScalar(GLint columnIndex, GLint rowIndex) const { return _value[columnIndex][rowIndex]; }
	void SetScalar(GLint columnIndex, GLint rowIndex, GLfloat value) { _value[columnIndex][rowIndex] = value; }

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
