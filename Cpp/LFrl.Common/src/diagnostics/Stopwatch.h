#ifndef __LFRL_COMMON_STOPWATCH_GUARD__
#define __LFRL_COMMON_STOPWATCH_GUARD__

#include <atomic>
#include "duration_snapshot.h"

BEGIN_LFRL_NAMESPACE

class StopWatch
{
public:
	typedef typename duration_calculator::clock clock;
	typedef typename duration_calculator::duration duration;
	typedef typename duration_calculator::time_point time_point;

	StopWatch() noexcept;
	explicit StopWatch(bool start) noexcept;
	StopWatch(StopWatch const&) = default;
	StopWatch(StopWatch&&) noexcept;
	StopWatch& operator= (StopWatch const&) = default;
	StopWatch& operator= (StopWatch&&) noexcept;
	~StopWatch() noexcept = default;

	bool IsRunning() const noexcept;
	time_point GetStartPoint() const noexcept;
	time_point GetEndPoint() const noexcept;
	duration_calculator GetDurationCalculator() const noexcept;
	duration_snapshot CreateDurationSnapshot() const noexcept;

	duration GetElapsedTime() const;
	convertible_duration GetElapsedConvertibleTime() const;
	u64 GetElapsedMs() const;
	u64 GetElapsedNs() const;

	template <class Rep, class Period>
	std::chrono::duration<Rep, Period> ConvertElapsedTime() const;

	template <class Rep, class Period>
	Rep GetElapsedTimeAs() const;

	bool Start() noexcept;
	bool Stop() noexcept;
	void Restart() noexcept;

private:
	duration_calculator _duration;
	time_point _end;
	std::atomic_bool _isRunning;
};

template <class Rep, class Period>
std::chrono::duration<Rep, Period> StopWatch::ConvertElapsedTime() const
{
	return _duration.convert_elapsed_time<Rep, Period>(GetEndPoint());
}

template <class Rep, class Period>
Rep StopWatch::GetElapsedTimeAs() const
{
	return _duration.get_elapsed_time_as<Rep, Period>(GetEndPoint());
}

END_LFRL_NAMESPACE

#endif
