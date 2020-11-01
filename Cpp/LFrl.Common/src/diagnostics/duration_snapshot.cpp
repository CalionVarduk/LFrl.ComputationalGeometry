#include "duration_snapshot.h"

BEGIN_LFRL_NAMESPACE

duration_snapshot duration_snapshot::zero()
{
	auto point = duration_calculator::time_point(duration_calculator::duration::zero());
	return duration_snapshot(point, point);
}

duration_snapshot::duration_snapshot() noexcept
	: _calculator(), _end(_calculator.get_start())
{}

duration_snapshot::duration_snapshot(
	duration_calculator calculator,
	typename duration_snapshot::time_point end) noexcept
	: _calculator(calculator), _end(end)
{}

duration_snapshot::duration_snapshot(
	typename duration_snapshot::time_point start,
	typename duration_snapshot::time_point end) noexcept
	: _calculator(start), _end(end)
{}

typename duration_snapshot::duration duration_snapshot::get_elapsed_time() const
{
	return _calculator.get_elapsed_time(_end);
}

u64 duration_snapshot::get_elapsed_ms() const
{
	return _calculator.get_elapsed_ms(_end);
}

u64 duration_snapshot::get_elapsed_ns() const
{
	return _calculator.get_elapsed_ns(_end);
}

END_LFRL_NAMESPACE
