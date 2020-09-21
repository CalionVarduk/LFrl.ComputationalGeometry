#include "GLCanvas.h"

#include "../capacities/Viewport.h"
#include "../utils/rendering_context_swapper.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

Class::ActionResult GLCanvas::Register()
{
	WNDCLASS params;
	std::memset(&params, 0, sizeof(params));
	params.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_GLOBALCLASS;
	params.lpfnWndProc = GLCanvas::_WndProc;
	params.hCursor = LoadCursor(NULL, IDC_ARROW);
	params.hInstance = GetModuleHandle(NULL);
	params.cbWndExtra = sizeof(GLCanvas*);
	params.lpszClassName = "LFrl::OGL::Wnd::GLCanvas";
	return _Class.Initialize(params);
}

GLCanvas::GLCanvas() noexcept
	: _handle(), _dc(), _rc(), _state(ObjectState::CREATED)
{}

GLCanvas::ActionResult GLCanvas::Initialize(HWND parent, RECT bounds)
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	if (_handle.GetState() != ObjectState::READY)
	{
		HandleParams hParams;
		hParams.parent = parent;
		hParams.x = bounds.left;
		hParams.y = bounds.top;
		hParams.width = bounds.right - bounds.left;
		hParams.height = bounds.bottom - bounds.top;

		Handle handle;
		auto hInitResult = handle.Initialize(_Class, hParams);
		if (hInitResult != Handle::ActionResult::OK)
		{
			_state = ObjectState::INIT_FAILURE;
			return ActionResult::HANDLE_INIT_FAILURE;
		}
		if (!handle.SetData(0, reinterpret_cast<LONG_PTR>(this)))
		{
			handle.Dispose();
			_state = ObjectState::INIT_FAILURE;
			return ActionResult::HANDLE_INIT_FAILURE;
		}
		_handle = std::move(handle);
	}
	if (_dc.GetState() != ObjectState::READY)
	{
		PixelFormatAttributes pxfAttribs;
		auto dcInitResult = _dc.Initialize(_handle, pxfAttribs);
		if (dcInitResult != DeviceContext::ActionResult::OK)
		{
			_state = ObjectState::INIT_FAILURE;
			return ActionResult::DC_INIT_FAILURE;
		}
	}

	RenderingAttributes rAttribs;
	auto rcInitResult = _rc.Initialize(_dc, rAttribs);
	if (rcInitResult != RenderingContext::ActionResult::OK)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::RC_INIT_FAILURE;
	}

	// TODO: add context factory param + use it to create context, if fails, fail transactionally, add new canvas method for recreating context (accepts one context factory param)

	// TODO: update gl viewport via context (not immediately here, though, but when window is actually shown)
	_state = ObjectState::READY;
	return ActionResult::OK;
}

GLCanvas::ActionResult GLCanvas::ChangePixelFormat(PixelFormatAttributes attributes, PIXELFORMATDESCRIPTOR descriptor)
{
	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	DeviceContext dc;
	auto dcInitResult = dc.Initialize(_handle, attributes, descriptor);
	if (dcInitResult != DeviceContext::ActionResult::OK)
		return ActionResult::DC_INIT_FAILURE;

	RenderingAttributes rAttribs;

	if (dc.GetHdc() == _dc.GetHdc())
	{
		RenderingContext rc;
		auto rcInitResult = rc.Initialize(_dc, rAttribs);
		if (rcInitResult != RenderingContext::ActionResult::OK)
		{
			dc.Invalidate();
			return ActionResult::RC_INIT_FAILURE;
		}

		if (_rc.GetHglrc() == rc.GetHglrc())
		{
			dc.Invalidate();
			rc.Invalidate();
			return ActionResult::NO_CHANGE;
		}
		else
			_rc = std::move(rc);
	}
	else
	{
		RenderingContext rc;
		auto rcInitResult = rc.Initialize(dc, rAttribs);
		if (rcInitResult != RenderingContext::ActionResult::OK)
			return ActionResult::RC_INIT_FAILURE;

		_dc = std::move(dc);
		_rc = std::move(rc);
	}
	// TODO: update context rc reference
	return ActionResult::OK;
}

bool GLCanvas::SetBounds(RECT value)
{
	if (_state != ObjectState::READY)
		return false;

	if (!_handle.SetPos(value))
		return false;

	rendering_context_swapper swapper(_rc);
	// TODO: update gl viewport via context
	if (swapper.swapped())
	{
		// TODO: prepare context (context preparation = enable/disable gl flags, prepare global settings shared between all context renderers, updating projection matrix, background color, all that jazz)
	}

	// TODO: draw context
	return true;
}

bool GLCanvas::Draw()
{
	if (_state != ObjectState::READY)
		return false;

	rendering_context_swapper swapper(_rc);
	if (swapper.swapped())
	{
		// TODO: prepare context
	}
	
	// TODO: draw context
	return true;
}

GLCanvas::ActionResult GLCanvas::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	// TODO: dispose context

	if (_rc.GetState() == ObjectState::READY)
	{
		auto rcDisposalResult = _rc.Dispose();
		if (rcDisposalResult != RenderingContext::ActionResult::OK)
			return ActionResult::RC_DISPOSAL_FAILURE;
	}
	if (_dc.GetState() == ObjectState::READY)
	{
		auto dcDisposalResult = _dc.Dispose();
		if (dcDisposalResult != DeviceContext::ActionResult::OK)
			return ActionResult::DC_DISPOSAL_FAILURE;
	}
	if (_handle.GetState() == ObjectState::READY)
	{
		if (!_handle.SetData(0, NULL))
			return ActionResult::HANDLE_DISPOSAL_FAILURE;

		auto hDisposalResult = _handle.Dispose();
		if (hDisposalResult != Handle::ActionResult::OK)
			return ActionResult::HANDLE_DISPOSAL_FAILURE;
	}

	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

Class GLCanvas::_Class = Class();

LRESULT CALLBACK GLCanvas::_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto canvas = reinterpret_cast<GLCanvas*>(GetWindowLongPtr(hwnd, 0));

	if (canvas == nullptr)
		return DefWindowProc(hwnd, message, wParam, lParam);

	switch (message)
	{
		// TODO: implement
	}

	// TODO: send to IGLCanvasEventHandler (add generic implementation with T being the concrete convas context type - allows handler implementation to access context type & methods directly, without any fiddling with casting etc.)
	return DefWindowProc(hwnd, message, wParam, lParam); // TODO: don't do this if canvas event handler is defined
}

END_LFRL_OGL_WND_NAMESPACE