#ifndef __LFRL_OGL_WND_CLASS_GUARD__
#define __LFRL_OGL_WND_CLASS_GUARD__

#include <string>
#include "../ObjectState.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

struct Class final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_REGISTERED = 1,
		REGISTRATION_FAILURE = 2,
		ALREADY_DISPOSED = 3,
		NOT_READY = 4,
		UNREGISTRATION_FAILURE = 5
	};

	Class(Class const&) = delete;
	Class& operator=(Class const&) = delete;

	Class() noexcept;
	Class(Class&&) noexcept;
	Class& operator=(Class&&) noexcept;
	~Class() { Dispose(); }

	WNDCLASS const& GetParams() const noexcept { return _params; }
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize(WNDCLASS params);
	ActionResult Dispose();

private:
	WNDCLASS _params;
	ObjectState _state;
};

END_LFRL_OGL_WND_NAMESPACE

#endif
