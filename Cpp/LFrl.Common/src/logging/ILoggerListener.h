#ifndef __LFRL_COMMON_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_LOGGER_LISTENER_GUARD__

#include "LogMessage.h"

BEGIN_LFRLCOMMON_NAMESPACE

class Logger;

struct ILoggerListener
{
	friend class Logger;

	virtual ~ILoggerListener() = default;
	virtual void Invoke(LogMessage const& message) = 0;

	bool IsEnabled() const noexcept { return _isEnabled; }
	void Enable() noexcept { _isEnabled = true; }
	void Disable() noexcept { _isEnabled = false; }

	Logger const* GetLogger() const noexcept { return _logger; }

protected:
	ILoggerListener() noexcept
		: _isEnabled(true), _logger(nullptr)
	{}

private:
	bool _isEnabled;
	Logger const* _logger;
};

END_LFRLCOMMON_NAMESPACE

#endif
