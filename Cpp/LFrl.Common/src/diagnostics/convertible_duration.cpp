#include "convertible_duration.h"

BEGIN_LFRLCOMMON_NAMESPACE

convertible_duration convertible_duration::zero()
{
	return convertible_duration(duration::zero());
}

convertible_duration::convertible_duration() noexcept
	: _value(duration::zero())
{}

convertible_duration::convertible_duration(typename convertible_duration::duration value) noexcept
	: _value(value)
{}

convertible_duration::convertible_duration(
	typename convertible_duration::time_point start,
	typename convertible_duration::time_point end) noexcept
	: _value(end - start)
{}

u64 convertible_duration::get_ms() const
{
	return get_as<u64, std::milli>();
}

u64 convertible_duration::get_ns() const
{
	return get_as<u64, std::nano>();
}

END_LFRLCOMMON_NAMESPACE
