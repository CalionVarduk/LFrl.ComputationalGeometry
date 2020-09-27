#ifndef __LFRL_OGL_CG_POINT_TEST_CONTEXT_GUARD__
#define __LFRL_OGL_CG_POINT_TEST_CONTEXT_GUARD__

#include "../internal/namespace_macros.h"
#include "LFrl.OGL/src/ShaderStore.h"
#include "LFrl.OGL/src/primitives/primitives.h"
#include "LFrl.OGL/src/capacities/capacities.h"
#include "LFrl.OGL/src/context/GLCanvasContext.h"

#include "../vertexes/PointVertex.h"

BEGIN_LFRL_OGL_CG_NAMESPACE

class PointTestContext : public GLCanvasContext
{
public:
	typedef GLCanvasContext base;

	PointTestContext(RenderingContext& rc, ShaderStore* shaders) noexcept;

	CachedTimerQuery<32> const& GetTimer() const noexcept { return _timer; }

protected:
	virtual void OnInitializing() override;
	virtual void OnDisposing() override;
	virtual void OnStartDrawing() override;
	virtual void OnFinishDrawing() override;
	virtual void OnBoundsChanged(glm::ivec2 const& position, glm::ivec2 const& size) override;

private:
	ShaderStore* _shaders;
	CachedTimerQuery<32> _timer;
	ShaderProgram* _sProgram;
	Projection _projection;
	Capacities::Color::ClearValueSnapshot _backgroundColor;
	GLbitfield _clearBuffers;

};

END_LFRL_OGL_CG_NAMESPACE

#endif
