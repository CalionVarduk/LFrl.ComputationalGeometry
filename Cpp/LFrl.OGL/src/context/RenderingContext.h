#ifndef __LFRL_OGL_RENDERING_CONTEXT_GUARD__
#define __LFRL_OGL_RENDERING_CONTEXT_GUARD__

#include "DeviceContext.h"

BEGIN_LFRL_OGL_NAMESPACE

struct RenderingAttributes final
{
	LFRL_COMMON::u32 majorVersion;
	LFRL_COMMON::u32 minorVersion;
	LFRL_COMMON::u32 layerPlane;
	LFRL_COMMON::u32 flags;

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

	static bool Deactivate();

	RenderingContext(RenderingContext const&) = delete;
	RenderingContext& operator=(RenderingContext const&) = delete;

	RenderingContext() noexcept;
	RenderingContext(RenderingContext&&) noexcept;
	RenderingContext& operator=(RenderingContext&&) noexcept;
	~RenderingContext() { Dispose(); }

	HGLRC GetHglrc() const noexcept { return _hglrc; }
	DeviceContext* GetDeviceContext() noexcept { return _dc; }
	DeviceContext const* GetDeviceContext() const noexcept { return _dc; }
	RenderingAttributes const& GetAttributes() const noexcept { return _attributes; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize(DeviceContext& dc, RenderingAttributes attributes);

	bool Activate();
	bool IsActive() const;

	ActionResult Dispose();
	ActionResult Invalidate();

	char const* GetGLVersion() const;
	char const* GetGLVendor() const;
	char const* GetGLRenderer() const;
	char const* GetGLExtensions() const;
	GLint GetGLMajorVersion() const;
	GLint GetGLMinorVersion() const;
	char const* GetGLewVersion() const;
	char const* GetGLslVersion() const;

private:
	HGLRC _hglrc;
	DeviceContext* _dc;
	RenderingAttributes _attributes;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
