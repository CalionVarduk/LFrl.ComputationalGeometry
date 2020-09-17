#ifndef __LFRL_OGL_WND_HANDLE_GUARD__
#define __LFRL_OGL_WND_HANDLE_GUARD__

#include "Class.h"
#include "LFrl.Common/src/utils/typedefs.h"

BEGIN_LFRL_OGL_WND_NAMESPACE

struct HandleParams final
{
	DWORD style;
	LFRL_COMMON::i32 x;
	LFRL_COMMON::i32 y;
	LFRL_COMMON::i32 width;
	LFRL_COMMON::i32 height;
	HWND parent;

	HandleParams() noexcept;
};

struct Handle final
{
	enum struct State
	{
		CREATED = 0,
		INIT_FAILURE = 1,
		READY = 2,
		DISPOSED = 3
	};

	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		INVALID_CLASS = 2,
		HWND_INIT_FAILURE = 3,
		ALREADY_DISPOSED = 4,
		NOT_READY = 5,
		HWND_DISPOSAL_FAILURE = 6
	};

	Handle(Handle const&) = delete;
	Handle(Handle&&) = delete;
	Handle& operator=(Handle const&) = delete;
	Handle& operator=(Handle&&) = delete;

	Handle();
	~Handle() { Dispose(); }

	HWND GetParentHwnd() const;
	HWND GetRootHwnd() const;
	HWND GetRootOwnerHwnd() const;
	HWND GetHwnd() const noexcept { return _hwnd; }
	Class const* GetClass() const noexcept { return _cls; }
	HandleParams const& GetParams() const noexcept { return _params; }
	State GetState() const noexcept { return _state; }

	bool SetData(int index, LONG_PTR data);
	LONG_PTR GetData(int index) const;
	RECT GetRect() const;
	POINT GetPosition() const;
	POINT GetSize() const;

	bool Validate(RECT const* rect = NULL);

	ActionResult Initialize(Class const& cls, HandleParams params);
	ActionResult Dispose();

private:
	HWND _hwnd;
	Class const* _cls;
	HandleParams _params;
	State _state;
};

END_LFRL_OGL_WND_NAMESPACE

#endif