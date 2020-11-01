#ifndef __LFRL_COMMON_MEASURABLE_GUARD__
#define __LFRL_COMMON_MEASURABLE_GUARD__

#include <atomic>
#include <stdexcept>
#include "convertible_duration.h"

BEGIN_LFRL_NAMESPACE

struct IMeasurable
{
	IMeasurable(IMeasurable const&) = delete;
	IMeasurable& operator=(IMeasurable const&) = delete;

	virtual ~IMeasurable() = default;

	bool IsRunning() const noexcept { return _isRunning.load(); }
	convertible_duration Measure() noexcept(false);

protected:
	IMeasurable() noexcept;
	IMeasurable(IMeasurable&&) noexcept;
	IMeasurable& operator=(IMeasurable&&) noexcept;

	virtual convertible_duration Invoke() = 0;

private:
	std::atomic_bool _isRunning;
};

END_LFRL_NAMESPACE

#endif
