#include "GLCanvasContext.h"

#include "../utils/rendering_context_swapper.h"
#include "../capacities/Viewport.h"

BEGIN_LFRL_OGL_NAMESPACE

GLCanvasContext::GLCanvasContext(RenderingContext& rc) noexcept
	: _state(ObjectState::CREATED), _rc(&rc), _pipeline()
{}

GLCanvasContext::GLCanvasContext(GLCanvasContext&& other)
	: _state(ObjectState::CREATED), _rc(nullptr), _pipeline()
{
	std::swap(_state, other._state);
	std::swap(_rc, other._rc);
	std::swap(_pipeline, other._pipeline);
}

GLCanvasContext& GLCanvasContext::operator= (GLCanvasContext&& other)
{
	if (this != &other)
	{
		std::swap(_state, other._state);
		std::swap(_rc, other._rc);
		std::swap(_pipeline, other._pipeline);
	}
	return *this;
}

bool GLCanvasContext::Initialize()
{
	if (_state >= ObjectState::READY)
		return false;

	rendering_context_swapper swapper(*_rc);
	OnInitializing();
	_state = ObjectState::READY;
	return true;
}

void GLCanvasContext::Draw()
{
	rendering_context_swapper swapper(*_rc);
	OnStartDrawing();
	_pipeline.Run();
	OnFinishDrawing();
}

bool GLCanvasContext::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return false;

	if (_state != ObjectState::READY)
		return false;

	rendering_context_swapper swapper(*_rc);
	OnDisposing();
	_rc = nullptr;
	_pipeline.Clear();
	_state = ObjectState::DISPOSED;
	return true;
}

void GLCanvasContext::OnFinishDrawing()
{
	_rc->GetDeviceContext()->SwapBuffers();
}

void GLCanvasContext::OnBoundsChanged(glm::ivec2 const& position, glm::ivec2 const& size)
{
	Capacities::Viewport::Set(0, 0, size.x, size.y);
}

bool GLCanvasContext::_UpdateBounds(glm::ivec2 const& position, glm::ivec2 const& size)
{
	rendering_context_swapper swapper(*_rc);
	auto oldViewport = Capacities::Viewport::Snapshot::Load();
	OnBoundsChanged(position, size);
	auto newViewport = Capacities::Viewport::Snapshot::Load();
	return oldViewport.value.position != newViewport.value.position || oldViewport.value.size != newViewport.value.size;
}

END_LFRL_OGL_NAMESPACE
