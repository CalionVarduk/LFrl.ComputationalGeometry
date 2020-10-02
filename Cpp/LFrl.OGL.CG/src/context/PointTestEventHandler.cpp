#include "PointTestEventHandler.h"

#include <windowsx.h>

BEGIN_LFRL_OGL_CG_NAMESPACE

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
				_context->GetView().Translate(dx, dy);
				GetCanvas()->Draw();
			}
		}

		auto bounds = _context->GetView().GetBounds();
		auto trans = _context->GetView().GetTranslation();
		auto scale = _context->GetView().GetScale();
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
		auto scaleStep = dt / WHEEL_DELTA * 0.125f;

		if (scaleStep != 0)
		{
			auto handle = GetCanvas()->GetHandle();
			
			auto cursorAnchor = handle->GetAnchorPoint(_lastCursorPosition);
			cursorAnchor.y = 1.0f - cursorAnchor.y;
			
			auto scale = _context->GetView().GetScale();
			_context->GetView().Scale(scale.x + scaleStep, scale.y + scaleStep, cursorAnchor.x, cursorAnchor.y);

			_context->Draw();

			auto bounds = _context->GetView().GetBounds();
			auto viewX = bounds.GetX(cursorAnchor.x);
			auto viewY = bounds.GetY(cursorAnchor.y);

			scale = _context->GetView().GetScale();
			auto trans = _context->GetView().GetTranslation();

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
