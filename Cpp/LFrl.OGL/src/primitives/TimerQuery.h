#ifndef __LFRL_OGL_TIMER_QUERY_GUARD__
#define __LFRL_OGL_TIMER_QUERY_GUARD__

#include <chrono>
#include "../ObjectState.h"

BEGIN_LFRL_OGL_NAMESPACE

struct TimerQuery final
{
	enum struct ActionResult
	{
		OK = 0,
		ALREADY_INITIALIZED = 1,
		QUERY_GEN_FAILURE = 2,
		ALREADY_DISPOSED = 3,
		NOT_READY = 4
	};

	static GLuint GetRunningId();
	static bool IsAnyRunning() { return GetRunningId() != NULL; }

	TimerQuery(TimerQuery const&) = delete;
	TimerQuery(TimerQuery&&) = default;
	TimerQuery& operator=(TimerQuery const&) = delete;
	TimerQuery& operator=(TimerQuery&&) = default;

	TimerQuery() noexcept;
	~TimerQuery() { Dispose(); }

	GLuint GetActiveId() const noexcept { return _ids[_active]; }
	GLuint GetInactiveId() const noexcept { return _ids[_inactive]; }
	GLuint GetQueryCount() const noexcept { return _queryCount; }
	GLuint64 GetLastElapsedTimeNs() const noexcept { return _lastElapsedTimeNs; }
	GLuint64 GetTotalElapsedTimeNs() const noexcept { return _totalElapsedTimeNs; }
	GLdouble GetAverageElapsedTimeNs() const noexcept { return _queryCount == 0 ? 0.0 : _totalElapsedTimeNs / static_cast<GLdouble>(_queryCount); }
	std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> GetLastElapsedTime() const noexcept;
	std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> GetTotalElapsedTime() const noexcept;
	std::chrono::duration<GLdouble, std::chrono::nanoseconds::period> GetAverageElapsedTime() const noexcept;
	ObjectState GetState() const noexcept { return _state; }

	ActionResult Initialize();

	bool IsRunning() const;
	void Reset();
	void Begin();
	void End();

	ActionResult Dispose();

private:
	GLuint _ids[2];
	GLuint _active;
	GLuint _inactive;
	GLuint _queryCount;
	GLuint64 _lastElapsedTimeNs;
	GLuint64 _totalElapsedTimeNs;
	ObjectState _state;
};

END_LFRL_OGL_NAMESPACE

#endif
