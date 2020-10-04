#ifndef __LFRL_OGL_ORTHOGONAL_VIEW_GUARD__
#define __LFRL_OGL_ORTHOGONAL_VIEW_GUARD__

#include "Projection.h"

BEGIN_LFRL_OGL_NAMESPACE

struct OrthogonalView
{
	struct Bounds final
	{
		glm::vec2 const& GetOrigin() const noexcept { return _origin; }
		void SetOrigin(glm::vec2 const& value) noexcept { _origin = value; }
		glm::vec2 const& GetSize() const noexcept { return _size; }
		void SetSize(glm::vec2 const& value) noexcept { _size = value; }

		GLfloat GetWidth() const noexcept { return _size.x; }
		void SetWidth(GLfloat value) noexcept { _size.x = value; }
		GLfloat GetHeight() const noexcept { return _size.y; }
		void SetHeight(GLfloat value) noexcept { _size.y = value; }

		GLfloat GetLeft() const noexcept { return _origin.x; }
		void SetLeft(GLfloat value) noexcept { _origin.x = value; }
		GLfloat GetRight() const noexcept { return _origin.x + _size.x; }
		void SetRight(GLfloat value) noexcept { _origin.x = value - _size.x; }
		GLfloat GetCentreX() const noexcept { return _origin.x + (_size.x * 0.5f); }
		void SetCentreX(GLfloat value) noexcept { _origin.x = value - (_size.x * 0.5f); }

		GLfloat GetBottom() const noexcept { return _origin.y; }
		void SetBottom(GLfloat value) noexcept { _origin.y = value; }
		GLfloat GetTop() const noexcept { return _origin.y + _size.y; }
		void SetTop(GLfloat value) noexcept { _origin.y = value - _size.y; }
		GLfloat GetCentreY() const noexcept { return _origin.y + (_size.y * 0.5f); }
		void SetCentreY(GLfloat value) noexcept { _origin.y = value - (_size.y * 0.5f); }

		GLfloat GetX(GLfloat anchor) const noexcept { return _origin.x + (_size.x * anchor); }
		GLfloat GetY(GLfloat anchor) const noexcept { return _origin.y + (_size.y * anchor); }

		Bounds() noexcept;
		Bounds(glm::vec2 const& origin, glm::vec2 const& size) noexcept;

	private:
		glm::vec2 _origin;
		glm::vec2 _size;
	};

	OrthogonalView(OrthogonalView const&) noexcept = default;
	OrthogonalView(OrthogonalView&&) noexcept = default;
	OrthogonalView& operator= (OrthogonalView const&) noexcept = default;
	OrthogonalView& operator= (OrthogonalView&&) noexcept = default;

	OrthogonalView() noexcept;
	explicit OrthogonalView(glm::vec2 const& size, GLfloat zNear = -1000.0f, GLfloat zFar = 1.0f) noexcept;
	OrthogonalView(GLfloat width, GLfloat height, GLfloat zNear = -1000.0f, GLfloat zFar = 1.0f) noexcept;

	glm::mat4 GetProjectionMatrix() const noexcept { return _projection.Get(); }
	glm::vec2 GetProjectionSize() const noexcept { return _size; }
	GLfloat GetProjectionZNear() const noexcept { return _zNear; }
	GLfloat GetProjectionZFar() const noexcept { return _zFar; }

	void ResetProjection() noexcept;
	void SetProjection(glm::vec2 const& size, GLfloat zNear = -1.0f, GLfloat zFar = 1000.0f) noexcept { SetProjection(size.x, size.y, zNear, zFar); }
	void SetProjection(GLfloat width, GLfloat height, GLfloat zNear = -1.0f, GLfloat zFar = 1000.0f) noexcept;

	glm::mat4 GetViewMatrix() const noexcept { return _view.Get(); }
	glm::vec2 GetTranslation() const noexcept { return glm::vec2(_view.Get()[3].x, _view.Get()[3].y); }
	glm::vec2 GetScale() const noexcept { return glm::vec2(_view.Get()[0].x, _view.Get()[1].y); }

	void ResetView() noexcept { _view.Reset(); }
	void Translate(glm::vec2 const& value) noexcept;
	void Translate(GLfloat x, GLfloat y) noexcept { Translate(glm::vec2(x, y)); }
	void Scale(glm::vec2 const& scale, glm::vec2 const& anchor) noexcept;
	void Scale(glm::vec2 const& scale) noexcept { Scale(scale, glm::vec2(0.5f, 0.5f)); }
	void Scale(GLfloat x, GLfloat y, GLfloat anchorX, GLfloat anchorY) noexcept { Scale(glm::vec2(x, y), glm::vec2(anchorX, anchorY)); }
	void Scale(GLfloat x, GLfloat y) noexcept { Scale(glm::vec2(x, y)); }

	void MoveTo(glm::vec2 const& point, glm::vec2 const& anchor) noexcept;
	void MoveTo(glm::vec2 const& point) noexcept { MoveTo(point, glm::vec2(0.5f, 0.5f)); }
	void MoveTo(GLfloat x, GLfloat y, GLfloat anchorX, GLfloat anchorY) noexcept { MoveTo(glm::vec2(x, y), glm::vec2(anchorX, anchorY)); }
	void MoveTo(GLfloat x, GLfloat y) noexcept { MoveTo(glm::vec2(x, y)); }

	void RoundTranslation() noexcept;

	glm::mat4 GetMatrix() const noexcept { return GetProjectionMatrix() * GetViewMatrix(); }

	void Reset() noexcept;
	Bounds GetBounds() const;

private:
	Projection _projection;
	Transform _view;
	glm::vec2 _size;
	GLfloat _zNear;
	GLfloat _zFar;
};

END_LFRL_OGL_NAMESPACE

#endif
