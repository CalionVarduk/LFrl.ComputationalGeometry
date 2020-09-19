#include "Class.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

Class::Class() noexcept
	: _params(), _state(ObjectState::CREATED)
{
	std::memset(&_params, 0, sizeof(_params));
}

Class::ActionResult Class::Initialize(WNDCLASS params)
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_REGISTERED;

	if (!RegisterClass(&params))
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::REGISTRATION_FAILURE;
	}

	_params = params;
	_state = ObjectState::READY;
	return ActionResult::OK;
}

Class::ActionResult Class::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_REGISTERED;

	if (!UnregisterClass(_params.lpszClassName, _params.hInstance))
		return ActionResult::UNREGISTRATION_FAILURE;

	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_WND_NAMESPACE
