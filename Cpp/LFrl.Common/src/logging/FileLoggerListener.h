#ifndef __LFRL_COMMON_FILE_LOGGER_LISTENER_GUARD__
#define __LFRL_COMMON_FILE_LOGGER_LISTENER_GUARD__

#include <string>
#include <fstream>
#include "ILoggerListener.h"

BEGIN_LFRLCOMMON_NAMESPACE

class FileLoggerListener : public ILoggerListener
{
	FileLoggerListener() = delete;
	FileLoggerListener& operator= (FileLoggerListener const&) = delete;
	FileLoggerListener& operator= (FileLoggerListener&&) = delete;

public:
	FileLoggerListener(FileLoggerListener const&) = default;
	FileLoggerListener(FileLoggerListener&&) = default;

	enum struct StreamMode
	{
		TEMPORARY = 0,
		PERMANENT = 1
	};

	const std::string path;
	const StreamMode mode;

	explicit FileLoggerListener(std::string const& path, StreamMode mode = StreamMode::PERMANENT);
	virtual ~FileLoggerListener();

	bool IsOk() const;
	virtual void Invoke(LogMessage const& message) override;

private:
	std::ofstream _stream;
	bool _isOk;
};

END_LFRLCOMMON_NAMESPACE

#endif
