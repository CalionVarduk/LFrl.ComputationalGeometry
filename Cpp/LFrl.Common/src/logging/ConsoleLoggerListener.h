#ifndef __LFRL_COMMON_CONSOLE_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_CONSOLE_LOGGER_LISTENER_GUARD__

#include <iostream>
#include "StreamLoggerListener.h"

BEGIN_LFRL_NAMESPACE

class ConsoleLoggerListener : public StreamLoggerListener
{
	ConsoleLoggerListener() = delete;
	ConsoleLoggerListener(ConsoleLoggerListener const&) = delete;
	ConsoleLoggerListener(ConsoleLoggerListener&&) = delete;
	ConsoleLoggerListener& operator= (ConsoleLoggerListener const&) = delete;
	ConsoleLoggerListener& operator= (ConsoleLoggerListener&&) = delete;

public:
	typedef StreamLoggerListener base;

	ConsoleLoggerListener() : base(std::cout) {}
	virtual ~ConsoleLoggerListener() = default;
};

END_LFRL_NAMESPACE

#endif
