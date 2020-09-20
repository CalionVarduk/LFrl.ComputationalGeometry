#include "TimerQuery.h"

BEGIN_LFRL_OGL_NAMESPACE

TimerQuery::TimerQuery() noexcept
	: _ids(), _active(0), _inactive(1), _queryCount(0), _lastElapsedTimeNs(0), _totalElapsedTimeNs(0), _state(ObjectState::CREATED)
{
	std::memset(_ids, 0, sizeof(_ids));
}

std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> TimerQuery::GetLastElapsedTime() const noexcept
{
	return std::chrono::duration<GLuint64, std::chrono::nanoseconds::period>(_lastElapsedTimeNs);
}

std::chrono::duration<GLuint64, std::chrono::nanoseconds::period> TimerQuery::GetTotalElapsedTime() const noexcept
{
	return std::chrono::duration<GLuint64, std::chrono::nanoseconds::period>(_totalElapsedTimeNs);
}

std::chrono::duration<GLdouble, std::chrono::nanoseconds::period> TimerQuery::GetAverageElapsedTime() const noexcept
{
	return std::chrono::duration<GLdouble, std::chrono::nanoseconds::period>(GetAverageElapsedTimeNs());
}

TimerQuery::ActionResult TimerQuery::Initialize()
{
	if (_state >= ObjectState::CREATED)
		return ActionResult::ALREADY_INITIALIZED;

	GLuint ids[2] = { 0, 0 };
	glGenQueries(2, ids);

	if (ids[0] == 0)
	{
		if (ids[1] != 0)
			glDeleteQueries(1, &ids[1]);

		_state = ObjectState::INIT_FAILURE;
		return ActionResult::QUERY_GEN_FAILURE;
	}
	if (ids[1] == 0)
	{
		glDeleteQueries(1, &ids[0]);
		_state = ObjectState::INIT_FAILURE;
		return ActionResult::QUERY_GEN_FAILURE;
	}

	glBeginQuery(GL_TIME_ELAPSED, ids[_inactive]);
	glEndQuery(GL_TIME_ELAPSED);

	_ids[0] = ids[0];
	_ids[1] = ids[1];
	_state = ObjectState::READY;
	return ActionResult::OK;
}

void TimerQuery::Reset()
{
	_queryCount = 0;
	_lastElapsedTimeNs = 0;
	_totalElapsedTimeNs = 0;
}

void TimerQuery::Begin()
{
	glBeginQuery(GL_TIME_ELAPSED, _ids[_inactive]);
}

void TimerQuery::End()
{
	glEndQuery(GL_TIME_ELAPSED);
	glGetQueryObjectui64v(_ids[_active], GL_QUERY_RESULT, &_lastElapsedTimeNs);
	std::swap(_active, _inactive);
	++_queryCount;
	_totalElapsedTimeNs += _lastElapsedTimeNs;
}

TimerQuery::ActionResult TimerQuery::Dispose()
{
	if (_state == ObjectState::DISPOSED)
		return ActionResult::ALREADY_DISPOSED;

	if (_state != ObjectState::READY)
		return ActionResult::NOT_READY;

	glEndQuery(GL_TIME_ELAPSED);
	glDeleteQueries(2, _ids);
	_state = ObjectState::DISPOSED;
	return ActionResult::OK;
}

END_LFRL_OGL_NAMESPACE
