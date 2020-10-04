#include "PointTestEventHandler.h"

#include <windowsx.h>

BEGIN_LFRL_OGL_CG_NAMESPACE

PointTestViewTransformation::PointTestViewTransformation(OrthogonalView* view)
	: _view(view), _zoomLevel(0), _minZoomLevel(-25), _maxZoomLevel(50), _step(2.0f), _scale(1.0f), _epsilon(1.0f)
{
	
}

void PointTestViewTransformation::SetZoomLevel(GLint value, glm::vec2 const& anchor)
{
	value = glm::clamp(value, _minZoomLevel, _maxZoomLevel);

	_zoomLevel = value;
	_scale = glm::pow(_step, _zoomLevel);
	_epsilon = 1.0f / _scale;

	_view->Scale(glm::vec2(_scale, _scale), anchor);
	_view->RoundTranslation();
}

void PointTestViewTransformation::SetMinZoomLevel(GLint value)
{
	if (value > _maxZoomLevel)
		value = _maxZoomLevel;

	if (value == _minZoomLevel)
		return;

	_minZoomLevel = value;
	if (value < _minZoomLevel)
		SetZoomLevel(_minZoomLevel);
}

void PointTestViewTransformation::SetMaxZoomLevel(GLint value)
{
	if (value < _minZoomLevel)
		value = _minZoomLevel;

	if (value == _maxZoomLevel)
		return;

	_maxZoomLevel = value;
	if (value > _maxZoomLevel)
		SetZoomLevel(_maxZoomLevel);
}

void PointTestViewTransformation::SetStep(GLfloat value)
{
	if (value < 1.0f)
		value = 1.0f;

	if (value == _step)
		return;

	_step = value;
	SetZoomLevel(_zoomLevel);
}

void PointTestViewTransformation::Translate(GLfloat dx, GLfloat dy)
{
	_view->Translate(dx, dy);
	_view->RoundTranslation();
}

// TODO:
// add translation boundaries
// add line path rendering (represent lines as a 4-vertex square, with normalized line direction and length + normalized line direction rotated by PI/2 - for line width)
// each line path point should be rendered as a simple point, for now, with slightly bigger size than the line's width
LRESULT PointTestEventHandler::Handle(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		auto x = GET_X_LPARAM(lParam);
		auto y = GET_Y_LPARAM(lParam);

		_isPanning = true;
		SetCursor(_handCursor);
		SetCapture(GetCanvas()->GetHandle()->GetHwnd());
		_lastCursorPosition = { x, y };
		break;
	}
	case WM_LBUTTONUP:
	{
		_isPanning = false;
		SetCursor(_arrowCursor);
		ReleaseCapture();
		break;
	}
	case WM_MOUSEMOVE:
	{
		auto x = GET_X_LPARAM(lParam);
		auto y = GET_Y_LPARAM(lParam);

		auto canvas = GetCanvas();
		auto handle = canvas->GetHandle();
		auto cursorAnchor = handle->GetAnchorPoint({ x, y });
		cursorAnchor.y = 1.0f - cursorAnchor.y;

		if (cursorAnchor.x < 0 || cursorAnchor.x > 1 || cursorAnchor.y < 0 || cursorAnchor.y > 1)
			if (GetCapture() == handle->GetHwnd())
			{
				SendMessage(handle->GetHwnd(), WM_MOUSELEAVE, NULL, NULL);
				break;
			}

		if (_isPanning)
		{
			auto dx = x - _lastCursorPosition.x;
			auto dy = _lastCursorPosition.y - y;

			if (dx != 0 || dy != 0)
			{
				_transformation.Translate(dx, dy);
				GetCanvas()->Draw();
			}
		}

		auto bounds = _transformation.GetView()->GetBounds();
		auto trans = _transformation.GetView()->GetTranslation();
		auto scale = _transformation.GetView()->GetScale();
		auto viewX = bounds.GetX(cursorAnchor.x);
		auto viewY = bounds.GetY(cursorAnchor.y);

		_lastCursorPosition = { x, y };
		SendMessage(handle->GetHwnd(), WM_USER + 1, *reinterpret_cast<WPARAM*>(&viewX), *reinterpret_cast<LPARAM*>(&viewY));
		SendMessage(handle->GetHwnd(), WM_USER + 2, *reinterpret_cast<WPARAM*>(&trans.x), *reinterpret_cast<LPARAM*>(&trans.y));
		SendMessage(handle->GetHwnd(), WM_USER + 3, *reinterpret_cast<WPARAM*>(&scale.x), *reinterpret_cast<LPARAM*>(&scale.y));
		SendMessage(handle->GetHwnd(), WM_USER + 4, *(WPARAM*)(&bounds.GetOrigin().x), *(LPARAM*)(&bounds.GetOrigin().y));
		SendMessage(handle->GetHwnd(), WM_USER + 5, *(WPARAM*)(&bounds.GetSize().x), *(LPARAM*)(&bounds.GetSize().y));
		break;
	}
	case WM_MOUSEWHEEL:
	{
		auto dt = GET_WHEEL_DELTA_WPARAM(wParam);
		auto scaleStep = dt / WHEEL_DELTA;

		if (scaleStep != 0)
		{
			auto handle = GetCanvas()->GetHandle();
			
			auto cursorAnchor = handle->GetAnchorPoint(_lastCursorPosition);
			cursorAnchor.y = 1.0f - cursorAnchor.y;
			
			_transformation.OffsetZoomLevel(scaleStep, cursorAnchor.x, cursorAnchor.y);
			_context->SetZoomLevel(_transformation.GetZoomLevel());
			
			_context->Draw();

			auto bounds = _transformation.GetView()->GetBounds();
			auto viewX = bounds.GetX(cursorAnchor.x);
			auto viewY = bounds.GetY(cursorAnchor.y);

			auto scale = _transformation.GetView()->GetScale();
			auto trans = _transformation.GetView()->GetTranslation();

			SendMessage(handle->GetHwnd(), WM_USER + 1, *reinterpret_cast<WPARAM*>(&viewX), *reinterpret_cast<LPARAM*>(&viewY));
			SendMessage(handle->GetHwnd(), WM_USER + 2, *reinterpret_cast<WPARAM*>(&trans.x), *reinterpret_cast<LPARAM*>(&trans.y));
			SendMessage(handle->GetHwnd(), WM_USER + 3, *reinterpret_cast<WPARAM*>(&scale.x), *reinterpret_cast<LPARAM*>(&scale.y));
			SendMessage(handle->GetHwnd(), WM_USER + 4, *(WPARAM*)(&bounds.GetOrigin().x), *(LPARAM*)(&bounds.GetOrigin().y));
			SendMessage(handle->GetHwnd(), WM_USER + 5, *(WPARAM*)(&bounds.GetSize().x), *(LPARAM*)(&bounds.GetSize().y));
		}
		break;
	}
	case WM_MOUSELEAVE:
	{
		if (_isPanning)
		{
			_isPanning = false;
			SetCursor(_arrowCursor);
			ReleaseCapture();
			return 0;
		}
		break;
	}
	case WM_SETCURSOR:
	{
		if (_isPanning)
			return 0;
	}
	}
	return base::Handle(message, wParam, lParam);
}

END_LFRL_OGL_CG_NAMESPACE
