#ifndef __LFRL_COMMON_STREAM_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_STREAM_LOGGER_LISTENER_GUARD__

#include <ostream>
#include "ILoggerListener.h"

BEGIN_LFRLCOMMON_NAMESPACE

class StreamLoggerListener : public ILoggerListener
{
	StreamLoggerListener() = delete;
	StreamLoggerListener& operator= (StreamLoggerListener const&) = delete;
	StreamLoggerListener& operator= (StreamLoggerListener&&) = delete;

public:
	StreamLoggerListener(StreamLoggerListener const&) = default;
	StreamLoggerListener(StreamLoggerListener&&) = default;

	std::ostream& stream;

	explicit StreamLoggerListener(std::ostream& stream);
	virtual ~StreamLoggerListener() = default;

	virtual void Invoke(LogMessage const& message) override;
};

END_LFRLCOMMON_NAMESPACE

#endif
