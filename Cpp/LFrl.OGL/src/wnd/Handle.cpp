#include "Handle.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

HandleParams::HandleParams() noexcept
	: style(WS_VISIBLE), x(0), y(0), width(0), height(0), parent(NULL)
{}

Handle::Handle() noexcept
	: _hwnd(NULL), _cls(NULL), _params(), _state(ObjectState::CREATED)
{}

Handle::Handle(Handle&& other) noexcept
	: _hwnd(NULL), _cls(NULL), _params(), _state(ObjectState::CREATED)
{
	std::swap(_hwnd, other._hwnd);
	std::swap(_cls, other._cls);
	std::swap(_params, other._params);
	std::swap(_state, other._state);
}

Handle& Handle::operator=(Handle&& other) noexcept
{
	if (this != &other)
	{
		std::swap(_hwnd, other._hwnd);
		std::swap(_cls, other._cls);
		std::swap(_params, other._params);
		std::swap(_state, other._state);
	}
	return *this;
}

HWND Handle::GetParentHwnd() const
{
	return ::GetParent(_hwnd);
}

HWND Handle::GetRootHwnd() const
{
	return ::GetAncestor(_hwnd, GA_ROOT);
}

HWND Handle::GetRootOwnerHwnd() const
{
	return ::GetAncestor(_hwnd, GA_ROOTOWNER);
}

bool Handle::SetData(int index, LONG_PTR data)
{
	return SetWindowLongPtr(_hwnd, 0, data), true; // TODO: check if actually valid?
}

LONG_PTR Handle::GetData(int index) const
{
	return GetWindowLongPtr(_hwnd, index);
}

RECT Handle::GetRect() const
{
	RECT rect;
	if (::GetWindowRect(_hwnd, &rect))
		return rect;

	return { 0, 0, 0, 0 };
}

POINT Handle::GetPosition() const
{
	auto rect = GetRect();
	::MapWindowPoints(HWND_DESKTOP, GetParentHwnd(), reinterpret_cast<LPPOINT>(&rect), 2);
	return { rect.left, rect.top };
}

POINT Handle::GetSize() const
{
	auto rect = GetRect();
	return { rect.right - rect.left, rect.bottom - rect.top };
}

PointF Handle::GetAnchorPoint(POINT point) const
{
	auto size = GetSize();
	PointF result;
	result.x = size.x == 0 ? 0.0f : static_cast<GLfloat>(point.x) / static_cast<GLfloat>(size.x);
	result.y = size.y == 0 ? 0.0f : static_cast<GLfloat>(point.y) / static_cast<GLfloat>(size.y);
	return result;
}

bool Handle::SetPos(RECT pos, UINT flags)
{
	return ::SetWindowPos(_hwnd, NULL, pos.left, pos.top, pos.right - pos.left, pos.bottom - pos.top, flags | SWP_NOZORDER);
}

bool Handle::Validate(RECT const* rect)
{
	return ::ValidateRect(_hwnd, rect);
}

Handle::ActionResult Handle::Initialize(Class const& cls, HandleParams params)
{
	if (_state >= ObjectState::READY)
		return ActionResult::ALREADY_INITIALIZED;

	if (cls.GetState() != ObjectState::READY)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::INVALID_CLASS;
	}

	if (params.parent != NULL)
		params.style |= WS_CHILD;

	auto hwnd = CreateWindow(
		cls.GetParams().lpszClassName,
		NULL,
		params.style,
		params.x,
		params.y,
		params.width,
		params.height,
		params.parent,
		NULL,
		cls.GetParams().hInstance,
		NULL);

	if (hwnd == NULL)
	{
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::HWND_INIT_FAILURE;
	}

	_hwnd = hwnd;
	_cls = &cls;
	_params = params;
	_state = ObjectState::READY;
	return ActionResult::OK;
}

Handle::ActionResult Handle::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	if (!::DestroyWindow(_hwnd))
		return ActionResult::HWND_DISPOSAL_FAILURE;

	_hwnd = NULL;
	_cls = nullptr;
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_WND_NAMESPACE
