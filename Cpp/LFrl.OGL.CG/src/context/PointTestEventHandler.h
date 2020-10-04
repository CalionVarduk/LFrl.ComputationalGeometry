#ifndef __LFRL_OGL_CG_POINT_TEST_EVENT_HANDLER_GUARD__
#define __LFRL_OGL_CG_POINT_TEST_EVENT_HANDLER_GUARD__

#include "PointTestContext.h"
#include "LFrl.OGL/src/wnd/GLCanvas.h"
#include "LFrl.OGL/src/wnd/GLCanvasEventHandler.h"
#include "LFrl.OGL/src/wnd/GLCanvasEventHandlerFactory.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

struct PointTestViewTransformation
{
	PointTestViewTransformation() = default;
	PointTestViewTransformation(OrthogonalView* view);

	OrthogonalView* GetView() const noexcept { return _view; }
	GLint GetZoomLevel() const noexcept { return _zoomLevel; }
	GLfloat GetScale() const noexcept { return _scale; }

	void SetZoomLevel(GLint value, glm::vec2 const& anchor);
	void SetZoomLevel(GLint value) { SetZoomLevel(value, glm::vec2(0.5f, 0.5f)); }
	void SetZoomLevel(GLint value, GLfloat anchorX, GLfloat anchorY) { SetZoomLevel(value, glm::vec2(anchorX, anchorY)); }
	void OffsetZoomLevel(GLint offset, glm::vec2 const& anchor) { SetZoomLevel(_zoomLevel + offset, anchor); }
	void OffsetZoomLevel(GLint offset) { SetZoomLevel(_zoomLevel + offset); }
	void OffsetZoomLevel(GLint offset, GLfloat anchorX, GLfloat anchorY) { SetZoomLevel(_zoomLevel + offset, anchorX, anchorY); }

	void Translate(GLfloat dx, GLfloat dy);

	GLint GetMinZoomLevel() const noexcept { return _minZoomLevel; }
	void SetMinZoomLevel(GLint value);

	GLint GetMaxZoomLevel() const noexcept { return _maxZoomLevel; }
	void SetMaxZoomLevel(GLint value);

	GLfloat GetStep() const noexcept { return _step; }
	void SetStep(GLfloat value);

	GLfloat GetEpsilon() const noexcept { return _epsilon; }

private:
	OrthogonalView* _view;
	GLint _zoomLevel;
	GLint _minZoomLevel;
	GLint _maxZoomLevel;
	GLfloat _scale;
	GLfloat _step;
	GLfloat _epsilon;
};

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
		_transformation = PointTestViewTransformation(&_context->GetView());
		_transformation.SetStep(glm::pow(2.0f, 0.125f));
		_transformation.SetMinZoomLevel(-32);
		_transformation.SetMaxZoomLevel(64);
		_context->SetZoomLevel(_transformation.GetZoomLevel());
	}

	virtual LRESULT Handle(UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	PointTestContext* _context;
	PointTestViewTransformation _transformation;
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
