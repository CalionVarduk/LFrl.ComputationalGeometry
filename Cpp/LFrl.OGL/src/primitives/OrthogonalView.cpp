#include "OrthogonalView.h"

BEGIN_LFRL_OGL_NAMESPACE

OrthogonalView::Bounds::Bounds() noexcept
	: _origin(), _size()
{}

OrthogonalView::Bounds::Bounds(glm::vec2 const& origin, glm::vec2 const& size) noexcept
	: _origin(origin), _size(size)
{}

OrthogonalView::OrthogonalView() noexcept
	: _projection(), _view(), _size(), _zNear(0), _zFar(0)
{}

OrthogonalView::OrthogonalView(glm::vec2 const& size, GLfloat zNear, GLfloat zFar) noexcept
	: _projection(), _view(), _size(size), _zNear(zNear), _zFar(zFar)
{
	_projection.SetOrthogonal(size.x, size.y, zNear, zFar);
}

OrthogonalView::OrthogonalView(GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar) noexcept
	: _projection(), _view(), _size(glm::vec2(width, height)), _zNear(zNear), _zFar(zFar)
{
	_projection.SetOrthogonal(width, height, zNear, zFar);
}

void OrthogonalView::ResetProjection() noexcept
{
	_projection.Reset();
	_size.x = _size.y = _zNear = _zFar = 0.0f;
}

void OrthogonalView::SetProjection(GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar) noexcept
{
	_projection.SetOrthogonal(width, height, zNear, zFar);
	_size = glm::vec2(width, height);
	_zNear = zNear;
	_zFar = zFar;
}

void OrthogonalView::MoveTo(GLfloat x, GLfloat y, GLfloat anchorX, GLfloat anchorY)
{
	anchorX = glm::clamp(anchorX, 0.0f, 1.0f);
	anchorY = glm::clamp(anchorY, 0.0f, 1.0f);
	auto offset = (GetProjectionSize() / GetScale()) * glm::vec2(anchorX, anchorY);

	_view.Reset();
	_view.Translate(x + offset.x, y + offset.y, 0);
}

void OrthogonalView::Reset() noexcept
{
	ResetProjection();
	ResetView();
}

OrthogonalView::Bounds OrthogonalView::GetBounds() const
{
	return Bounds(-GetTranslation(), GetProjectionSize() / GetScale());
}

END_LFRL_OGL_NAMESPACE
