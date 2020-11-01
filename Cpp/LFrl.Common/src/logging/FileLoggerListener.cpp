#include "FileLoggerListener.h"

BEGIN_LFRL_NAMESPACE

FileLoggerListener::FileLoggerListener(std::string const& path, FileLoggerListener::StreamMode mode)
	: path(path), mode(mode), _stream()
{
	_stream.open(path, std::ios_base::trunc);
	if ((_isOk = !_stream.fail()) && mode == StreamMode::TEMPORARY)
		_stream.close();
}

FileLoggerListener::~FileLoggerListener()
{
	if (_stream.is_open())
		_stream.close();
}

bool FileLoggerListener::IsOk() const
{
	return _isOk;
}

void FileLoggerListener::Invoke(LogMessage const& message)
{
	if (mode == StreamMode::TEMPORARY)
	{
		_stream.open(path, std::ios_base::app);
		if (_isOk = !_stream.fail())
		{
			_stream << message.message << '\n' << std::endl;
			_stream.close();
		}
	}
	else if (_stream.is_open())
		_stream << message.message << '\n' << std::endl;
	else
		_isOk = false;
}

END_LFRL_NAMESPACE
