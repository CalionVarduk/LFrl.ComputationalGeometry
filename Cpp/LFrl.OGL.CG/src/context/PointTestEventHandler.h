#ifndef __LFRL_OGL_CG_POINT_TEST_EVENT_HANDLER_GUARD__
#define __LFRL_OGL_CG_POINT_TEST_EVENT_HANDLER_GUARD__

#include "PointTestContext.h"
#include "LFrl.OGL/src/wnd/GLCanvas.h"
#include "LFrl.OGL/src/wnd/GLCanvasEventHandler.h"
#include "LFrl.OGL/src/wnd/GLCanvasEventHandlerFactory.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

class PointTestEventHandler : public LFRL_OGL_WND::GLCanvasEventHandler
{
public:
	typedef LFRL_OGL_WND::GLCanvasEventHandler base;

	explicit PointTestEventHandler(LFRL_OGL_WND::GLCanvas& canvas)
		: base(canvas)
	{
		_context = reinterpret_cast<PointTestContext*>(canvas.GetContext());
		_lastCursorPosition = { 0, 0 };
		_isPanning = false;
		_arrowCursor = LoadCursor(NULL, IDC_ARROW);
		_handCursor = LoadCursor(NULL, IDC_HAND);
	}

	virtual LRESULT Handle(UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	PointTestContext* _context;
	POINT _lastCursorPosition;
	BOOL _isPanning;
	HCURSOR _arrowCursor;
	HCURSOR _handCursor;
};

class PointTestEventHandlerFactory : public LFRL_OGL_WND::GLCanvasEventHandlerFactory
{
public:
	PointTestEventHandlerFactory() noexcept {}

	virtual LFRL_OGL_WND::GLCanvasEventHandler* Create(LFRL_OGL_WND::GLCanvas& canvas) { return new PointTestEventHandler(canvas); }
};

END_LFRL_OGL_CG_NAMESPACE

#endif
