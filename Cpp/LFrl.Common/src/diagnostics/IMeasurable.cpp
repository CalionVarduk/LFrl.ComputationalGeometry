#include "IMeasurable.h"

BEGIN_LFRL_COMMON_NAMESPACE

convertible_duration IMeasurable::Measure() noexcept(false)
{
	if (_isRunning.exchange(true))
		throw std::runtime_error("measurable is already running");

	auto result = Invoke();
	_isRunning.store(false);
	return result;
}

IMeasurable::IMeasurable() noexcept
	: _isRunning(false)
{}

END_LFRL_COMMON_NAMESPACE
