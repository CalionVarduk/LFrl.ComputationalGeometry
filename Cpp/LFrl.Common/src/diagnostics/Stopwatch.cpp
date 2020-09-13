#include "Stopwatch.h"

using namespace LFRLCOMMON;

StopWatch::StopWatch() noexcept
	: _duration(), _end(_duration.get_start()), _isRunning(false)
{}

StopWatch::StopWatch(bool start) noexcept
	: _duration(), _end(_duration.get_start()), _isRunning(start)
{}

bool StopWatch::IsRunning() const noexcept
{
	return _isRunning.load();
}

typename StopWatch::time_point StopWatch::GetStartPoint() const noexcept
{
	return _duration.get_start();
}

typename StopWatch::time_point StopWatch::GetEndPoint() const noexcept
{
	return _isRunning ? clock::now() : _end;
}

duration_calculator StopWatch::GetDurationCalculator() const noexcept
{
	return _duration;
}

duration_snapshot StopWatch::CreateDurationSnapshot() const noexcept
{
	return duration_snapshot(_duration, GetEndPoint());
}

typename StopWatch::duration StopWatch::GetElapsedTime() const
{
	return _duration.get_elapsed_time(GetEndPoint());
}

convertible_duration StopWatch::GetElapsedConvertibleTime() const
{
	return _duration.calculate(GetEndPoint());
}

u64 StopWatch::GetElapsedMs() const
{
	return _duration.get_elapsed_ms(GetEndPoint());
}

u64 StopWatch::GetElapsedNs() const
{
	return _duration.get_elapsed_ns(GetEndPoint());
}

bool StopWatch::Start() noexcept
{
	if (_isRunning.exchange(true))
		return false;

	_duration = duration_calculator();
	_end = _duration.get_start();
	return true;
}

bool StopWatch::Stop() noexcept
{
	if (!_isRunning.exchange(false))
		return false;

	_end = clock::now();
	return true;
}

void StopWatch::Restart() noexcept
{
	_isRunning.exchange(true);
	_duration = duration_calculator();
	_end = _duration.get_start();
}
