#ifndef __LFRL_COMMON_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_LOGGER_LISTENER_GUARD__

#include "LogMessage.h"

BEGIN_LFRL_NAMESPACE

class Logger;

struct ILoggerListener
{
	friend class Logger;

	ILoggerListener(ILoggerListener const&) = delete;
	ILoggerListener(ILoggerListener&&) = delete;
	ILoggerListener& operator=(ILoggerListener const&) = delete;
	ILoggerListener& operator=(ILoggerListener&&) = delete;

	virtual ~ILoggerListener() = default;
	virtual void Invoke(LogMessage const& message) = 0;

	bool IsEnabled() const noexcept { return _isEnabled; }
	void Enable() noexcept { _isEnabled = true; }
	void Disable() noexcept { _isEnabled = false; }

	Logger const* GetLogger() const noexcept { return _logger; }

protected:
	ILoggerListener() noexcept;

private:
	bool _isEnabled;
	Logger const* _logger;
};

END_LFRL_NAMESPACE

#endif
