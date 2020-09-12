#include "stopwatch.h"

using namespace LFRLCOMMON;

StopWatch::StopWatch() noexcept
	: _start(clock_type::now()), _end(_start), _isRunning(false)
{}

StopWatch::StopWatch(bool start) noexcept
	: _start(clock_type::now()), _end(_start), _isRunning(start)
{}

bool StopWatch::IsRunning() const noexcept
{
	return _isRunning.load();
}

StopWatch::time_point_type StopWatch::GetStartPoint() const noexcept
{
	return _start;
}

StopWatch::time_point_type StopWatch::GetEndPoint() const noexcept
{
	return _isRunning ? clock_type::now() : _end;
}

StopWatch::duration_type StopWatch::GetElapsedTime() const
{
	return GetEndPoint() - _start;
}

u64 StopWatch::GetElapsedMs() const
{
	return std::chrono::duration_cast<std::chrono::duration<u64, std::milli>>(GetElapsedTime()).count();
}

u64 StopWatch::GetElapsedNs() const
{
	return std::chrono::duration<u64, std::nano>(GetElapsedTime()).count();
}

bool StopWatch::Start() noexcept
{
	if (_isRunning.exchange(true))
		return false;

	_start = _end = clock_type::now();
	return true;
}

bool StopWatch::Stop() noexcept
{
	if (!_isRunning.exchange(false))
		return false;

	_end = clock_type::now();
	return true;
}

void StopWatch::Restart() noexcept
{
	_isRunning.exchange(true);
	_start = _end = clock_type::now();
}
