#ifndef __LFRL_COMMON_DURATION_SNAPSHOT_GUARD__
#define __LFRL_COMMON_DURATION_SNAPSHOT_GUARD__

#include "duration_calculator.h"

BEGIN_LFRL_COMMON_NAMESPACE

struct duration_snapshot final
{
	typedef typename duration_calculator::clock clock;
	typedef typename duration_calculator::duration duration;
	typedef typename duration_calculator::time_point time_point;

	static duration_snapshot zero();

	duration_snapshot(duration_snapshot const&) noexcept = default;
	duration_snapshot(duration_snapshot&&) noexcept = default;
	duration_snapshot& operator=(duration_snapshot const&) noexcept = default;
	duration_snapshot& operator=(duration_snapshot&&) noexcept = default;

	duration_snapshot() noexcept;
	duration_snapshot(time_point start, time_point end) noexcept;
	duration_snapshot(duration_calculator calculator, time_point end) noexcept;

	time_point get_start() const noexcept { return _calculator.get_start(); }
	time_point get_end() const noexcept { return _end; }
	duration get_elapsed_time() const;
	u64 get_elapsed_ms() const;
	u64 get_elapsed_ns() const;

	template <class Rep, class Period>
	std::chrono::duration<Rep, Period> convert_elapsed_time() const;

	template <class Rep, class Period>
	Rep get_elapsed_time_as() const;

private:
	duration_calculator _calculator;
	time_point _end;
};

template <class Rep, class Period>
std::chrono::duration<Rep, Period> duration_snapshot::convert_elapsed_time() const
{
	return _calculator.convert_elapsed_time<Rep, Period>(_end);
}

template <class Rep, class Period>
Rep duration_snapshot::get_elapsed_time_as() const
{
	return _calculator.get_elapsed_time_as<Rep, Period>(_end);
}

END_LFRL_COMMON_NAMESPACE

#endif
