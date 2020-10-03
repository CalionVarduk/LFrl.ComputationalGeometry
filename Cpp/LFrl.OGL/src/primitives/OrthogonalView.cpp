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

void OrthogonalView::Translate(glm::vec2 const& value) noexcept
{
	auto scale = GetScale();
	auto prevTranslation = GetTranslation();

	auto translation = prevTranslation + value;

	_view.Reset();
	_view.Translate(translation.x, translation.y, 0.0f);
	_view.Scale(scale.x, scale.y, 1.0f);
}

void OrthogonalView::Scale(glm::vec2 const& scale, glm::vec2 const& anchor) noexcept
{
	auto size = GetProjectionSize();
	auto prevScale = GetScale();
	auto prevTranslation = GetTranslation();

	auto translationOffset = (scale / prevScale - 1.0f) * (prevTranslation - anchor * size);
	auto translation = prevTranslation + translationOffset;

	_view.Reset();
	_view.Translate(translation.x, translation.y, 0.0f);
	_view.Scale(scale.x, scale.y, 1.0f);
}

void OrthogonalView::MoveTo(glm::vec2 const& point, glm::vec2 const& anchor) noexcept
{
	auto size = GetProjectionSize();
	auto scale = GetScale();

	auto translation = -scale * point + anchor * size;

	_view.Reset();
	_view.Translate(translation.x, translation.y, 0.0f);
	_view.Scale(scale.x, scale.y, 1.0f);
}

void OrthogonalView::RoundTranslation() noexcept
{
	auto translation = glm::round(GetTranslation());
	_view.SetScalar(3, 0, translation.x);
	_view.SetScalar(3, 1, translation.y);
}

void OrthogonalView::Reset() noexcept
{
	ResetProjection();
	ResetView();
}

OrthogonalView::Bounds OrthogonalView::GetBounds() const
{
	auto scale = GetScale();
	return Bounds(-GetTranslation() / scale, GetProjectionSize() / scale);
}

END_LFRL_OGL_NAMESPACE
