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

IMeasurable::IMeasurable(IMeasurable&& other) noexcept
	: _isRunning(other._isRunning.load())
{
	_isRunning.store(false);
}

IMeasurable& IMeasurable::operator=(IMeasurable&& other) noexcept
{
	if (this != &other)
	{
		auto value = _isRunning.load();
		_isRunning.store(other._isRunning);
		other._isRunning.store(value);
	}
	return *this;
}

END_LFRL_COMMON_NAMESPACE
