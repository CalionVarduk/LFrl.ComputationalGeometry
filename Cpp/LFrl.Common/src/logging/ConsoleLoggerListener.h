#ifndef __LFRL_COMMON_CONSOLE_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_CONSOLE_LOGGER_LISTENER_GUARD__

#include <iostream>
#include "StreamLoggerListener.h"

BEGIN_LFRLCOMMON_NAMESPACE

class ConsoleLoggerListener : public StreamLoggerListener
{
	ConsoleLoggerListener() = delete;
	ConsoleLoggerListener& operator= (ConsoleLoggerListener const&) = delete;
	ConsoleLoggerListener& operator= (ConsoleLoggerListener&&) = delete;

public:
	typedef StreamLoggerListener base;

	ConsoleLoggerListener(ConsoleLoggerListener const&) = default;
	ConsoleLoggerListener(ConsoleLoggerListener&&) = default;

	ConsoleLoggerListener() : base(std::cout) {}
	virtual ~ConsoleLoggerListener() = default;
};

END_LFRLCOMMON_NAMESPACE

#endif
