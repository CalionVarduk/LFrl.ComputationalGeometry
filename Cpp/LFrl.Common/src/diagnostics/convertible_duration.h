#ifndef __LFRL_COMMON_CONVERTIBLE_DURATION_GUARD__
#define __LFRL_COMMON_CONVERTIBLE_DURATION_GUARD__

#include <chrono>
#include "../utils/typedefs.h"

BEGIN_LFRL_NAMESPACE

struct convertible_duration final
{
	typedef std::chrono::high_resolution_clock clock;
	typedef clock::duration duration;
	typedef clock::time_point time_point;

	static convertible_duration zero();

	convertible_duration(convertible_duration const&) noexcept = default;
	convertible_duration(convertible_duration&&) noexcept = default;
	convertible_duration& operator=(convertible_duration const&) noexcept = default;
	convertible_duration& operator=(convertible_duration&&) noexcept = default;

	convertible_duration() noexcept;
	convertible_duration(duration value) noexcept;
	convertible_duration(time_point start, time_point end) noexcept;

	duration get() const noexcept { return _value; }
	u64 get_ms() const;
	u64 get_ns() const;

	template <class Rep, class Period>
	std::chrono::duration<Rep, Period> convert() const;

	template <class Rep, class Period>
	Rep get_as() const;

private:
	duration _value;
};

template <class Rep, class Period>
std::chrono::duration<Rep, Period> convertible_duration::convert() const
{
	return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(_value);
}

template <class Rep, class Period>
Rep convertible_duration::get_as() const
{
	return convert<Rep, Period>().count();
}

END_LFRL_NAMESPACE

#endif
