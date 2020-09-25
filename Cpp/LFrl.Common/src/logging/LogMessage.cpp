#include "LogMessage.h"

BEGIN_LFRL_COMMON_NAMESPACE

LogMessage::LogMessage(Logger const* source, std::string&& message, Type type, u64 timestamp)
	: source(source), message(std::move(message)), type(type), timestamp(timestamp)
{}

LogMessage::LogMessage(Logger const* source, std::string const& message, Type type, u64 timestamp)
	: source(source), message(message), type(type), timestamp(timestamp)
{}

END_LFRL_COMMON_NAMESPACE
