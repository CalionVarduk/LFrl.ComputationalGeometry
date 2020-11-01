#include "duration_calculator.h"

BEGIN_LFRL_NAMESPACE

duration_calculator duration_calculator::zero()
{
	return duration_calculator(duration_calculator::time_point(duration_calculator::duration::zero()));
}

duration_calculator::duration_calculator() noexcept
	: _start(clock::now())
{}

duration_calculator::duration_calculator(typename duration_calculator::time_point start) noexcept
	: _start(start)
{}

convertible_duration duration_calculator::calculate(typename duration_calculator::time_point end) const
{
	return convertible_duration(_start, end);
}

typename duration_calculator::duration duration_calculator::get_elapsed_time(typename duration_calculator::time_point end) const
{
	return calculate(end).get();
}

u64 duration_calculator::get_elapsed_ms(typename duration_calculator::time_point end) const
{
	return calculate(end).get_ms();
}

u64 duration_calculator::get_elapsed_ns(typename duration_calculator::time_point end) const
{
	return calculate(end).get_ns();
}

END_LFRL_NAMESPACE
