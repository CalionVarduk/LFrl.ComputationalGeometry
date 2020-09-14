#include "StreamLoggerListener.h"

BEGIN_LFRL_COMMON_NAMESPACE

StreamLoggerListener::StreamLoggerListener(std::ostream& stream)
	: stream(stream)
{}

void StreamLoggerListener::Invoke(LogMessage const& message)
{
	stream << message.message << '\n' << std::endl;
}

END_LFRL_COMMON_NAMESPACE
