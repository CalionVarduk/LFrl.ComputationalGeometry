#include "RenderingContext.h"

#include "../utils/rendering_context_swapper.h"

BEGIN_LFRL_OGL_NAMESPACE

char const* __get_gl_string(RenderingContext const& ctx, GLenum value)
{
	char const* result = nullptr;
	{
		auto swapper = rendering_context_swapper(ctx);
		if (swapper.swapped())
			result = reinterpret_cast<char const*>(glGetString(value));
	}
	return result;
}

GLint __get_gl_integer(RenderingContext const& ctx, GLenum value)
{
	GLint result = -1;
	{
		auto swapper = rendering_context_swapper(ctx);
		if (swapper.swapped())
			glGetIntegerv(value, &result);
	}
	return result;
}

RenderingAttributes::RenderingAttributes() noexcept
	: majorVersion(3), minorVersion(3), layerPlane(0), flags(WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB)
{}

std::array<int, 11> RenderingAttributes::encode() const noexcept
{
	return {
	WGL_CONTEXT_MAJOR_VERSION_ARB, static_cast<int>(majorVersion),
	WGL_CONTEXT_MINOR_VERSION_ARB, static_cast<int>(minorVersion),
	WGL_CONTEXT_LAYER_PLANE_ARB, static_cast<int>(layerPlane),
	WGL_CONTEXT_FLAGS_ARB, static_cast<int>(flags),
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0 };
}

bool RenderingContext::Deactivate()
{
	return wglMakeCurrent(NULL, NULL);
}

RenderingContext::RenderingContext() noexcept
	: _hglrc(NULL), _dc(NULL), _attributes(), _state(ObjectState::CREATED)
{}

RenderingContext::ActionResult RenderingContext::Initialize(DeviceContext& dc, RenderingAttributes attributes)
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	if (dc.GetState() != ObjectState::READY)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::INVALID_DEVICE_CONTEXT;
	}

	auto attribs = attributes.encode();
	auto hglrc = wglCreateContextAttribsARB(dc.GetHdc(), NULL, attribs.data());

	if (hglrc == NULL)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::HGLRC_INIT_FAILURE;
	}

	_hglrc = hglrc;
	_dc = &dc;
	_attributes = attributes;
	_state = ObjectState::READY;
	return ActionResult::OK;
}

bool RenderingContext::Activate()
{
	return wglMakeCurrent(_dc->GetHdc(), _hglrc);
}

bool RenderingContext::IsActive() const
{
	return wglGetCurrentContext() == _hglrc;
}

RenderingContext::ActionResult RenderingContext::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	if ((IsActive() && !Deactivate()) || !wglDeleteContext(_hglrc))
		return ActionResult::HGLRC_DISPOSAL_FAILURE;

	_hglrc = NULL;
	_dc = nullptr;
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

RenderingContext::ActionResult RenderingContext::Invalidate()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	_hglrc = NULL;
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

char const* RenderingContext::GetGLVersion() const
{
	return __get_gl_string(*this, GL_VERSION);
}

char const* RenderingContext::GetGLVendor() const
{
	return __get_gl_string(*this, GL_VENDOR);
}

char const* RenderingContext::GetGLRenderer() const
{
	return __get_gl_string(*this, GL_RENDERER);
}

char const* RenderingContext::GetGLExtensions() const
{
	return __get_gl_string(*this, GL_EXTENSIONS);
}

GLint RenderingContext::GetGLMajorVersion() const
{
	return __get_gl_integer(*this, GL_MAJOR_VERSION);
}

GLint RenderingContext::GetGLMinorVersion() const
{
	return __get_gl_integer(*this, GL_MINOR_VERSION);
}

char const* RenderingContext::GetGLewVersion() const
{
	return reinterpret_cast<char const*>(glewGetString(GLEW_VERSION));
}

char const* RenderingContext::GetGLslVersion() const
{
	return __get_gl_string(*this, GL_SHADING_LANGUAGE_VERSION);
}

END_LFRL_OGL_NAMESPACE
