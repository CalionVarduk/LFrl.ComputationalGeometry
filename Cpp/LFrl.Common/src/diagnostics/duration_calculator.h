#ifndef __LFRL_COMMON_DURATION_CALCULATOR_GUARD__
#define __LFRL_COMMON_DURATION_CALCULATOR_GUARD__

#include "convertible_duration.h"

BEGIN_LFRL_NAMESPACE

struct duration_calculator final
{
	typedef typename convertible_duration::clock clock;
	typedef typename convertible_duration::duration duration;
	typedef typename convertible_duration::time_point time_point;

	static duration_calculator zero();

	duration_calculator(duration_calculator const&) noexcept = default;
	duration_calculator(duration_calculator&&) noexcept = default;
	duration_calculator& operator=(duration_calculator const&) noexcept = default;
	duration_calculator& operator=(duration_calculator&&) noexcept = default;

	duration_calculator() noexcept;
	duration_calculator(time_point start) noexcept;

	time_point get_start() const noexcept { return _start; }
	convertible_duration calculate(time_point end) const;

	duration get_elapsed_time(time_point end) const;
	u64 get_elapsed_ms(time_point end) const;
	u64 get_elapsed_ns(time_point end) const;

	template <class Rep, class Period>
	std::chrono::duration<Rep, Period> convert_elapsed_time(time_point end) const;

	template <class Rep, class Period>
	Rep get_elapsed_time_as(time_point end) const;

private:
	time_point _start;
};

template <class Rep, class Period>
std::chrono::duration<Rep, Period> duration_calculator::convert_elapsed_time(typename duration_calculator::time_point end) const
{
	return calculate(end).convert<Rep, Period>();
}

template <class Rep, class Period>
Rep duration_calculator::get_elapsed_time_as(typename duration_calculator::time_point end) const
{
	return calculate(end).get_as<Rep, Period>();
}

END_LFRL_NAMESPACE

#endif
