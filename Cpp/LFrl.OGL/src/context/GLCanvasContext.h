#ifndef __LFRL_OGL_GL_CANVAS_CONTEXT_GUARD__
#define __LFRL_OGL_GL_CANVAS_CONTEXT_GUARD__

#include "RenderingContext.h"
#include "RenderingPipeline.h"

BEGIN_LFRL_OGL_NAMESPACE

namespace Wnd
{
	class GLCanvas;
}

class GLCanvasContext
{
	friend class Wnd::GLCanvas;

	GLCanvasContext() = delete;
	GLCanvasContext(GLCanvasContext const&) = delete;
	GLCanvasContext& operator=(GLCanvasContext const&) = delete;

public:
	GLCanvasContext(GLCanvasContext&&) = default;
	GLCanvasContext& operator=(GLCanvasContext&&) = default;

	explicit GLCanvasContext(RenderingContext& rc) noexcept;
	~GLCanvasContext() { Dispose(); }

	RenderingPipeline* GetPipeline() noexcept { return &_pipeline; }
	RenderingPipeline const* GetPipeline() const noexcept { return &_pipeline; }
	RenderingContext const* GetRc() const noexcept { return _rc; }
	ObjectState GetState() const noexcept { return _state; }

	bool Initialize();
	void Draw();
	bool Dispose();

protected:
	virtual void OnInitializing() {}
	virtual void OnDisposing() {}
	virtual void OnStartDrawing() {}
	virtual void OnFinishDrawing();
	virtual void OnBoundsChanged(glm::ivec2 const& position, glm::ivec2 const& size);

	RenderingContext* GetRc() noexcept { return _rc; }

private:
	ObjectState _state;
	RenderingContext* _rc;
	RenderingPipeline _pipeline;

	void _UpdateRc(RenderingContext& rc) { _rc = &rc; }
	bool _UpdateBounds(glm::ivec2 const& position, glm::ivec2 const& size);
};

END_LFRL_OGL_NAMESPACE

#endif
