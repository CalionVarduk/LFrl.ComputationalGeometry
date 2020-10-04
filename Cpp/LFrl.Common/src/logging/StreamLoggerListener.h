#ifndef __LFRL_COMMON_STREAM_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_STREAM_LOGGER_LISTENER_GUARD__

#include <ostream>
#include "ILoggerListener.h"

BEGIN_LFRL_NAMESPACE

class StreamLoggerListener : public ILoggerListener
{
	StreamLoggerListener() = delete;
	StreamLoggerListener(StreamLoggerListener const&) = delete;
	StreamLoggerListener(StreamLoggerListener&&) = delete;
	StreamLoggerListener& operator= (StreamLoggerListener const&) = delete;
	StreamLoggerListener& operator= (StreamLoggerListener&&) = delete;

public:
	std::ostream& stream;

	explicit StreamLoggerListener(std::ostream& stream);
	virtual ~StreamLoggerListener() = default;

	virtual void Invoke(LogMessage const& message) override;
};

END_LFRL_NAMESPACE

#endif
