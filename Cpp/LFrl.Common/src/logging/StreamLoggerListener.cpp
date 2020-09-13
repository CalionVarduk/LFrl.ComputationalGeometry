#include "StreamLoggerListener.h"

BEGIN_LFRLCOMMON_NAMESPACE

StreamLoggerListener::StreamLoggerListener(std::ostream& stream)
	: stream(stream)
{}

void StreamLoggerListener::Invoke(LogMessage const& message)
{
	stream << message.message << '\n' << std::endl;
}

END_LFRLCOMMON_NAMESPACE
