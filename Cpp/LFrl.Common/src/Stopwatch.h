#ifndef __LFRL_COMMON_STOPWATCH_GUARD__
#define __LFRL_COMMON_STOPWATCH_GUARD__

#include <chrono>
#include <atomic>
#include "utils/typedefs.h"

BEGIN_LFRLCOMMON_NAMESPACE

class StopWatch
{
public:
	typedef std::chrono::high_resolution_clock clock_type;
	typedef clock_type::duration duration_type;
	typedef clock_type::time_point time_point_type;

	StopWatch(StopWatch const&) = delete;
	StopWatch(StopWatch&&) = delete;
	~StopWatch() noexcept = default;
	StopWatch& operator= (StopWatch const&) = delete;
	StopWatch& operator= (StopWatch&&) = delete;

	StopWatch() noexcept;
	explicit StopWatch(bool start) noexcept;

	bool IsRunning() const noexcept;
	time_point_type GetStartPoint() const noexcept;
	time_point_type GetEndPoint() const noexcept;

	duration_type GetElapsedTime() const;
	u64 GetElapsedMs() const;
	u64 GetElapsedNs() const;

	template <class Rep, class Period = std::chrono::seconds::period>
	std::chrono::duration<Rep, Period> GetElapsedTimeAs() const;

	bool Start() noexcept;
	bool Stop() noexcept;
	void Restart() noexcept;

private:
	time_point_type _start;
	time_point_type _end;
	std::atomic_bool _isRunning;
};

template <class Rep, class Period>
std::chrono::duration<Rep, Period> StopWatch::GetElapsedTimeAs() const {
	return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(GetElapsedTime());
}

END_LFRLCOMMON_NAMESPACE

#endif
