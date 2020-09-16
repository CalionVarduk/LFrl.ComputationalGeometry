#ifndef __LFRL_OGL_RENDERING_CONTEXT_GUARD__
#define __LFRL_OGL_RENDERING_CONTEXT_GUARD__

#include "DeviceContext.h"
#include "../utils/rendering_context_swapper.h"

BEGIN_LFRL_OGL_NAMESPACE

struct RenderingAttributes final
{
	LFRL_COMMON::u32 majorVersion;
	LFRL_COMMON::u32 minorVersion;
	LFRL_COMMON::u32 layerPlane;
	LFRL_COMMON::u32 flags;
	bool useCoreProfile;

	RenderingAttributes() noexcept;

	std::array<int, 11> encode() const noexcept;
};

struct RenderingContext final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		INVALID_DEVICE_CONTEXT = 2,
		HGLRC_INIT_FAILURE = 3,
		NOT_READY = 4,
		HGLRC_DISPOSAL_FAILURE = 5,
		ALREADY_DISPOSED = 6
	};

	enum struct State
	{
		CREATED = 0,
		INIT_FAILURE = 1,
		READY = 2,
		DISPOSED = 3
	};

	RenderingContext(RenderingContext const&) = delete;
	RenderingContext(RenderingContext&&) = delete;
	RenderingContext& operator=(RenderingContext const&) = delete;
	RenderingContext& operator=(RenderingContext&&) = delete;

	RenderingContext();
	~RenderingContext() { Dispose(); }

	DeviceContext const* GetDeviceContext() const noexcept { return _dc; }
	HGLRC GetHglrc() const noexcept { return _hglrc; }
	RenderingAttributes const& GetAttributes() const noexcept { return _attributes; }
	State GetState() const noexcept { return _state; }

	ActionResult Initialize(DeviceContext const& dc, RenderingAttributes attributes);

	bool Activate();
	bool Deactivate();
	bool IsActive() const;

	void SetViewport(GLsizei width, GLsizei height) { SetViewport(0, 0, width, height); }
	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	ActionResult Dispose();

	char const* GetGLVersion() const;
	char const* GetGLVendor() const;
	char const* GetGLRenderer() const;
	char const* GetGLExtensions() const;
	GLint GetGLMajorVersion() const;
	GLint GetGLMinorVersion() const;
	char const* GetGLewVersion() const;
	char const* GetGLslVersion() const;

private:
	DeviceContext const* _dc;
	HGLRC _hglrc;
	RenderingAttributes _attributes;
	State _state;
};

END_LFRL_OGL_NAMESPACE

#endif
