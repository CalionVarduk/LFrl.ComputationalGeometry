#ifndef __LFRL_OGL_WND_CLASS_GUARD__
#define __LFRL_OGL_WND_CLASS_GUARD__

#include <string>
#include "../internal/namespace_macros.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

struct Class final
{
	enum struct State
	{
		CREATED = 0,
		INIT_FAILURE = 1,
		REGISTERED = 2,
		DISPOSED = 3
	};

	enum struct ActionResult
	{
		OK = 0,
		ALREADY_REGISTERED = 1,
		REGISTRATION_FAILURE = 2,
		ALREADY_DISPOSED = 3,
		NOT_REGISTERED = 4,
		UNREGISTRATION_FAILURE = 5
	};

	Class(Class const&) = delete;
	Class(Class&&) = delete;
	Class& operator=(Class const&) = delete;
	Class& operator=(Class&&) = delete;

	Class() noexcept;
	~Class() { Dispose(); }

	WNDCLASS const& GetParams() const noexcept { return _params; }
	State GetState() const noexcept { return _state; }

	ActionResult Initialize(WNDCLASS params);
	ActionResult Dispose();

private:
	WNDCLASS _params;
	State _state;
};

END_LFRL_OGL_WND_NAMESPACE

#endif
