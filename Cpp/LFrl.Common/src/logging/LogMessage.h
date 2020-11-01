#ifndef __LFRL_COMMON_LOG_MESSAGE_GUARD__
#define __LFRL_COMMON_LOG_MESSAGE_GUARD__

#include <array>
#include <string>
#include "../utils/typedefs.h"

BEGIN_LFRL_NAMESPACE

class Logger;

struct LogMessage final
{
	LogMessage() = default;
	LogMessage(LogMessage const&) = default;
	LogMessage(LogMessage&&) = default;
	LogMessage& operator= (LogMessage const&) = default;
	LogMessage& operator= (LogMessage&&) = default;

	enum struct Type
	{
		DEBUG = 0,
		INFO = 1,
		SUCCESS = 2,
		WARNING = 3,
		ERROR = 4
	};

	Logger const* const source;
	const std::string message;
	const Type type;
	const u64 timestamp;

	LogMessage(Logger const* source, std::string&& message, Type type, u64 timestamp);
	LogMessage(Logger const* source, std::string const& message, Type type, u64 timestamp);
};

END_LFRL_NAMESPACE

#endif
