#include "Logger.h"

#include "ILoggerListener.h"

BEGIN_LFRL_COMMON_NAMESPACE

void __begin_buffer(char* buffer)
{
	buffer[0] = '[';
}

void __end_buffer(char* buffer)
{
	buffer[0] = ']';
	buffer[1] = ':';
	buffer[2] = '\n';
	buffer[3] = '\0';
}

void __append_separator(std::string& dest, char separator, u32& cur_count)
{
	if (separator != '\0')
	{
		dest.push_back(separator);
		cur_count = (u32)dest.size();
	}
}

void __append_separator(std::string& dest, char separator, u32& cur_count, u32& last_count)
{
	if (cur_count > last_count)
	{
		last_count = cur_count;
		__append_separator(dest, separator, cur_count);
	}
}

void __append_format(std::string& dest, char const* format, u32& cur_count)
{
	dest.append(format);
	cur_count = (u32)dest.size();
}

void __append_year_format(std::string& dest, Logger::DateTimeFormat::Year year, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	switch (year)
	{
	case Logger::DateTimeFormat::Year::SHORT:
		__append_format(dest, "%y", cur_count);
		break;
	case Logger::DateTimeFormat::Year::LONG:
		__append_format(dest, "%Y", cur_count);
		break;
	}
}

void __append_month_format(std::string& dest, Logger::DateTimeFormat::Month month, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	switch (month)
	{
	case Logger::DateTimeFormat::Month::NUMERIC:
		__append_format(dest, "%m", cur_count);
		break;
	case Logger::DateTimeFormat::Month::ABBREVIATED:
		__append_format(dest, "%b", cur_count);
		break;
	case Logger::DateTimeFormat::Month::FULL:
		__append_format(dest, "%B", cur_count);
		break;
	}
}

void __append_day_format(std::string& dest, Logger::DateTimeFormat::Numeric day, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (day == Logger::DateTimeFormat::Numeric::ENABLED)
		__append_format(dest, "%d", cur_count);
}

void __append_hour_format(std::string& dest, Logger::DateTimeFormat::Numeric hour, Logger::DateTimeFormat::Clock clock, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (hour == Logger::DateTimeFormat::Numeric::ENABLED)
		__append_format(dest, clock == Logger::DateTimeFormat::Clock::C_12_HOUR ? "%I" : "%H", cur_count);
}

void __append_minute_format(std::string& dest, Logger::DateTimeFormat::Numeric minute, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (minute == Logger::DateTimeFormat::Numeric::ENABLED)
		__append_format(dest, "%M", cur_count);
}

void __append_second_format(std::string& dest, Logger::DateTimeFormat::Numeric second, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (second == Logger::DateTimeFormat::Numeric::ENABLED)
		__append_format(dest, "%S", cur_count);
}

void __append_millisecond_format_mock(std::string& dest, Logger::DateTimeFormat::Numeric millisecond, char time_separator, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (millisecond == Logger::DateTimeFormat::Numeric::ENABLED)
		__append_format(dest, time_separator == '\0' ? "{m}" : "{ms}", cur_count);
}

void __append_clock_format(std::string& dest, Logger::DateTimeFormat::Clock clock, char component_separator, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (cur_count > 0 && clock == Logger::DateTimeFormat::Clock::C_12_HOUR)
	{
		__append_separator(dest, component_separator, cur_count);
		__append_format(dest, "%p", cur_count);
	}
}

void __append_timezone_format(std::string& dest, Logger::DateTimeFormat::Timezone timezone, char component_separator, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	if (cur_count > 0)
	{
		switch (timezone)
		{
		case Logger::DateTimeFormat::Timezone::ABBREVIATED:
			__append_separator(dest, component_separator, cur_count);
			__append_format(dest, "(%Z)", cur_count);
			break;
		case Logger::DateTimeFormat::Timezone::GMT_OFFSET:
			__append_separator(dest, component_separator, cur_count);
			__append_format(dest, "%z", cur_count);
			break;
		case Logger::DateTimeFormat::Timezone::FULL:
			__append_separator(dest, component_separator, cur_count);
			__append_format(dest, "%z", cur_count);
			__append_separator(dest, component_separator, cur_count);
			__append_format(dest, "(%Z)", cur_count);
			break;
		}
	}
}

void __append_date_format(std::string& dest, Logger::DateTimeFormat::DateFormat date, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	u32 date_cur_count = 0;
	u32 date_last_count = 0;
	switch (date.layout)
	{
	case Logger::DateTimeFormat::Layout::YEAR_MONTH_DAY:
		__append_year_format(dest, date.year, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_month_format(dest, date.month, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_day_format(dest, date.day, date_cur_count, date_last_count);
		break;
	case Logger::DateTimeFormat::Layout::YEAR_DAY_MONTH:
		__append_year_format(dest, date.year, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_day_format(dest, date.day, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_month_format(dest, date.month, date_cur_count, date_last_count);
		break;
	case Logger::DateTimeFormat::Layout::DAY_MONTH_YEAR:
		__append_day_format(dest, date.day, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_month_format(dest, date.month, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_year_format(dest, date.year, date_cur_count, date_last_count);
		break;
	case Logger::DateTimeFormat::Layout::MONTH_DAY_YEAR:
		__append_month_format(dest, date.month, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_day_format(dest, date.day, date_cur_count, date_last_count);
		__append_separator(dest, date.separator, date_cur_count, date_last_count);
		__append_year_format(dest, date.year, date_cur_count, date_last_count);
		break;
	}
	cur_count = (u32)dest.size();
}

void __apend_time_format(std::string& dest, Logger::DateTimeFormat::TimeFormat time, char component_separator, u32& cur_count, u32& last_count)
{
	last_count = cur_count;
	u32 time_cur_count = 0;
	u32 time_last_count = 0;
	__append_hour_format(dest, time.hour, time.clock, time_cur_count, time_last_count);
	__append_separator(dest, time.separator, time_cur_count, time_last_count);
	__append_minute_format(dest, time.minute, time_cur_count, time_last_count);
	__append_separator(dest, time.separator, time_cur_count, time_last_count);
	__append_second_format(dest, time.second, time_cur_count, time_last_count);
	__append_millisecond_format_mock(dest, time.millisecond, time.separator, time_cur_count, time_last_count);
	__append_clock_format(dest, time.clock, component_separator, time_cur_count, time_last_count);
	__append_timezone_format(dest, time.timezone, component_separator, time_cur_count, time_last_count);
	cur_count = (u32)dest.size();
}

Logger::DateTimeFormat::DateFormat::DateFormat(
	Logger::DateTimeFormat::Year year,
	Logger::DateTimeFormat::Month month,
	Logger::DateTimeFormat::Numeric day,
	Logger::DateTimeFormat::Layout layout,
	char separator)
	: year(year), month(month), day(day), layout(layout), separator(separator)
{}

Logger::DateTimeFormat::TimeFormat::TimeFormat(
	Logger::DateTimeFormat::Numeric hour,
	Logger::DateTimeFormat::Numeric minute,
	Logger::DateTimeFormat::Numeric second,
	Logger::DateTimeFormat::Numeric millisecond,
	Logger::DateTimeFormat::Timezone timezone,
	Logger::DateTimeFormat::Clock clock,
	char separator)
	: hour(hour), minute(minute), second(second), millisecond(millisecond), timezone(timezone), clock(clock), separator(separator)
{}

Logger::DateTimeFormat::DateTimeFormat(
	Logger::DateTimeFormat::DateFormat date,
	Logger::DateTimeFormat::TimeFormat time,
	Logger::DateTimeFormat::Order order,
	char component_separator,
	bool localtime)
	: date(date), time(time), order(order), component_separator(component_separator), localtime(localtime)
{}

std::string Logger::DateTimeFormat::create_format() const
{
	u32 last_count = 0;
	u32 cur_count = 0;
	std::string result;
	switch (order)
	{
	case Order::DATE_FIRST:
		__append_date_format(result, date, cur_count, last_count);
		__append_separator(result, component_separator, cur_count, last_count);
		__apend_time_format(result, time, component_separator, cur_count, last_count);
		break;
	case Order::TIME_FIRST:
		__apend_time_format(result, time, component_separator, cur_count, last_count);
		__append_separator(result, component_separator, cur_count, last_count);
		__append_date_format(result, date, cur_count, last_count);
		break;
	}
	return result;
}

Logger::Logger()
	: _listeners(), _datetimeFormatDescriptor(), _datetimeFormat(_datetimeFormatDescriptor.create_format()), _stopwatch(true), _configuration(0)
{
	EnableAll();
	IncludeDatetime(true);
	IncludeType(true);
}

Logger::~Logger()
{
	_DisposeListeners();
}

std::vector<ILoggerListener*> const& Logger::GetListeners() const noexcept
{
	return _listeners;
}

bool Logger::AddListener(ILoggerListener* listener)
{
	if (listener == nullptr || listener->GetLogger() != nullptr)
		return false;

	listener->_logger = this;
	_listeners.push_back(listener);
	return true;
}

u32 Logger::RemoveListener(ILoggerListener const* listener)
{
	if (listener == nullptr)
		return 0;

	std::vector<size_t> indexes;

	for (size_t i = 0; i < _listeners.size(); ++i)
		if (_listeners[i] == listener)
			indexes.push_back(i);

	for (i32 i = (i32)indexes.size() - 1; i >= 0; --i)
		_listeners.erase(_listeners.begin() + indexes[i]);

	return (u32)indexes.size();
}

void Logger::ClearListeners()
{
	_DisposeListeners();
	_listeners.clear();
}

void Logger::EnableAll() noexcept
{
	EnableDebug();
	EnableInfo();
	EnableSuccess();
	EnableWarning();
	EnableError();
}

void Logger::DisableAll() noexcept
{
	DisableDebug();
	DisableInfo();
	DisableSuccess();
	DisableWarning();
	DisableError();
}

void Logger::EnableDebug() noexcept
{
	Enable(LogMessage::Type::DEBUG);
}

void Logger::DisableDebug() noexcept
{
	Disable(LogMessage::Type::DEBUG);
}

void Logger::EnableInfo() noexcept
{
	Enable(LogMessage::Type::INFO);
}

void Logger::DisableInfo() noexcept
{
	Disable(LogMessage::Type::INFO);
}

void Logger::EnableSuccess() noexcept
{
	Enable(LogMessage::Type::SUCCESS);
}

void Logger::DisableSuccess() noexcept
{
	Disable(LogMessage::Type::SUCCESS);
}

void Logger::EnableWarning() noexcept
{
	Enable(LogMessage::Type::WARNING);
}

void Logger::DisableWarning() noexcept
{
	Disable(LogMessage::Type::WARNING);
}

void Logger::EnableError() noexcept
{
	Enable(LogMessage::Type::ERROR);
}

void Logger::DisableError() noexcept
{
	Disable(LogMessage::Type::ERROR);
}

void Logger::Enable(LogMessage::Type type) noexcept
{
	_EnableConfigurationFlag((u8)type);
}

void Logger::Disable(LogMessage::Type type) noexcept
{
	_DisableConfigurationFlag((u8)type);
}

bool Logger::IsDebugEnabled() const noexcept
{
	return IsEnabled(LogMessage::Type::DEBUG);
}

bool Logger::IsInfoEnabled() const noexcept
{
	return IsEnabled(LogMessage::Type::INFO);
}

bool Logger::IsSuccessEnabled() const noexcept
{
	return IsEnabled(LogMessage::Type::SUCCESS);
}

bool Logger::IsWarningEnabled() const noexcept
{
	return IsEnabled(LogMessage::Type::WARNING);
}

bool Logger::IsErrorEnabled() const noexcept
{
	return IsEnabled(LogMessage::Type::ERROR);
}

bool Logger::IsEnabled(LogMessage::Type type) const noexcept
{
	return _GetConfigurationFlag((u8)type);
}

bool Logger::IsDatetimeIncluded() const noexcept
{
	return _GetConfigurationFlag((i32)LogMessage::Type::ERROR + 1);
}

void Logger::IncludeDatetime(bool value) noexcept
{
	if (value)
		_EnableConfigurationFlag((i32)LogMessage::Type::ERROR + 1);
	else
		_DisableConfigurationFlag((i32)LogMessage::Type::ERROR + 1);
}

void Logger::ExcludeDatetime(bool value) noexcept
{
	IncludeDatetime(!value);
}

bool Logger::IsTypeIncluded() const noexcept
{
	return _GetConfigurationFlag((i32)LogMessage::Type::ERROR + 2);
}

void Logger::IncludeType(bool value) noexcept
{
	if (value)
		_EnableConfigurationFlag((i32)LogMessage::Type::ERROR + 2);
	else
		_DisableConfigurationFlag((i32)LogMessage::Type::ERROR + 2);
}

void Logger::ExcludeType(bool value) noexcept
{
	IncludeType(!value);
}

std::string const& Logger::GetDatetimeFormat() const noexcept
{
	return _datetimeFormat;
}

Logger::DateTimeFormat Logger::GetDatetimeFormatDescriptor() const noexcept
{
	return _datetimeFormatDescriptor;
}

void Logger::SetDatetimeFormatDescriptor(Logger::DateTimeFormat descriptor)
{
	_datetimeFormatDescriptor = descriptor;
	_datetimeFormat = descriptor.create_format();
}

u64 Logger::GetLifetime() const
{
	return _stopwatch.GetElapsedMs();
}

void Logger::Log(LogMessage::Type type, std::string const& message) const
{
	if (IsEnabled(type))
		_Log(type, std::string(message));
}

void Logger::Log(LogMessage::Type type, std::string&& message) const
{
	if (IsEnabled(type))
		_Log(type, std::move(message));
}

void Logger::Log(LogMessage::Type type, std::ostringstream const& message) const
{
	if (IsEnabled(type))
		_Log(type, message.str());
}

void Logger::Log(LogMessage::Type type, char const* message) const
{
	if (IsEnabled(type))
		_Log(type, std::string(message));
}

void Logger::LogDebug(std::string const& message) const
{
	Log(LogMessage::Type::DEBUG, message);
}

void Logger::LogDebug(std::string&& message) const
{
	Log(LogMessage::Type::DEBUG, std::move(message));
}

void Logger::LogDebug(std::ostringstream const& message) const
{
	Log(LogMessage::Type::DEBUG, message);
}

void Logger::LogDebug(char const* message) const
{
	Log(LogMessage::Type::DEBUG, message);
}

void Logger::LogInfo(std::string const& message) const
{
	Log(LogMessage::Type::INFO, message);
}

void Logger::LogInfo(std::string&& message) const
{
	Log(LogMessage::Type::INFO, std::move(message));
}

void Logger::LogInfo(std::ostringstream const& message) const
{
	Log(LogMessage::Type::INFO, message);
}

void Logger::LogInfo(char const* message) const
{
	Log(LogMessage::Type::INFO, message);
}

void Logger::LogSuccess(std::string const& message) const
{
	Log(LogMessage::Type::SUCCESS, message);
}

void Logger::LogSuccess(std::string&& message) const
{
	Log(LogMessage::Type::SUCCESS, std::move(message));
}

void Logger::LogSuccess(std::ostringstream const& message) const
{
	Log(LogMessage::Type::SUCCESS, message);
}

void Logger::LogSuccess(char const* message) const
{
	Log(LogMessage::Type::SUCCESS, message);
}

void Logger::LogWarning(std::string const& message) const
{
	Log(LogMessage::Type::WARNING, message);
}

void Logger::LogWarning(std::string&& message) const
{
	Log(LogMessage::Type::WARNING, std::move(message));
}

void Logger::LogWarning(std::ostringstream const& message) const
{
	Log(LogMessage::Type::WARNING, message);
}

void Logger::LogWarning(char const* message) const
{
	Log(LogMessage::Type::WARNING, message);
}

void Logger::LogError(std::string const& message) const
{
	Log(LogMessage::Type::ERROR, message);
}

void Logger::LogError(std::string&& message) const
{
	Log(LogMessage::Type::ERROR, std::move(message));
}

void Logger::LogError(std::ostringstream const& message) const
{
	Log(LogMessage::Type::ERROR, message);
}

void Logger::LogError(char const* message) const
{
	Log(LogMessage::Type::ERROR, message);
}

u32 Logger::ParseDebugType(char* buffer, u32 buffer_size) const
{
	const char text[] = "DEBUG";
	strcpy_s(buffer, buffer_size, text);
	return sizeof(text) - 1;
}

u32 Logger::ParseInfoType(char* buffer, u32 buffer_size) const
{
	const char text[] = "INFORMATION";
	strcpy_s(buffer, buffer_size, text);
	return sizeof(text) - 1;
}

u32 Logger::ParseSuccessType(char* buffer, u32 buffer_size) const
{
	const char text[] = "SUCCESS";
	strcpy_s(buffer, buffer_size, text);
	return sizeof(text) - 1;
}

u32 Logger::ParseWarningType(char* buffer, u32 buffer_size) const
{
	const char text[] = "WARNING";
	strcpy_s(buffer, buffer_size, text);
	return sizeof(text) - 1;
}

u32 Logger::ParseErrorType(char* buffer, u32 buffer_size) const
{
	const char text[] = "ERROR";
	strcpy_s(buffer, buffer_size, text);
	return sizeof(text) - 1;
}

void Logger::_DisposeListeners() const
{
	for (auto listener : _listeners)
		delete listener;
}

bool Logger::_GetConfigurationFlag(u8 position) const noexcept
{
	return (_configuration & (1U << position)) > 0;
}

void Logger::_EnableConfigurationFlag(u8 position) noexcept
{
	_configuration |= (1U << position);
}

void Logger::_DisableConfigurationFlag(u8 position) noexcept
{
	_configuration &= ~(1U << position);
}

u32 Logger::_GetParsedDatetime(char* buffer, u32 buffer_size) const
{
	tm tm;
	auto now = std::chrono::system_clock::now();
	auto timeT = std::chrono::system_clock::to_time_t(now);

	if (_datetimeFormatDescriptor.localtime)
		localtime_s(&tm, &timeT);
	else
		gmtime_s(&tm, &timeT);

	auto count = (u32)strftime(buffer, buffer_size, _datetimeFormat.c_str(), &tm);

	if (_datetimeFormatDescriptor.time.millisecond == DateTimeFormat::Numeric::DISABLED || count >= buffer_size - 1)
		return count;

	auto msIndex = 0;
	while (buffer[msIndex] != '{')
		++msIndex;

	if (_datetimeFormatDescriptor.time.separator == '\0')
		--msIndex;
	else
	{
		buffer[msIndex] = '.';
		if (msIndex == buffer_size - 2)
			return count;
	}

	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

	buffer[++msIndex] = (char)(msec / 100 + '0');
	if (msIndex == buffer_size - 2)
		return count;

	buffer[++msIndex] = (char)(msec / 10 % 10 + '0');
	if (msIndex == buffer_size - 2)
		return count;

	buffer[++msIndex] = (char)(msec % 10 + '0');
	return count;
}

u32 Logger::_GetParsedType(char* buffer, u32 buffer_size, LogMessage::Type type) const
{
	switch (type)
	{
	case LogMessage::Type::DEBUG: return ParseDebugType(buffer, buffer_size);
	case LogMessage::Type::INFO: return ParseInfoType(buffer, buffer_size);
	case LogMessage::Type::SUCCESS: return ParseSuccessType(buffer, buffer_size);
	case LogMessage::Type::WARNING: return ParseWarningType(buffer, buffer_size);
	case LogMessage::Type::ERROR: return ParseErrorType(buffer, buffer_size);
	}
	return 0;
}

void Logger::_Log(LogMessage::Type type, std::string&& message) const
{
	auto timestamp = GetLifetime();

	if (IsDatetimeIncluded())
	{
		if (IsTypeIncluded())
		{
			char buffer[BUFFER_SIZE * 2];
			__begin_buffer(buffer);
			auto dtLength = _GetParsedDatetime(buffer + 1, BUFFER_SIZE - 3);
			buffer[dtLength + 1] = ',';
			buffer[dtLength + 2] = ' ';
			auto typeLength = _GetParsedType(buffer + dtLength + 3, BUFFER_SIZE - 4, type);
			__end_buffer(buffer + dtLength + typeLength + 3);
			message.insert(0, buffer);
		}
		else
		{
			char buffer[BUFFER_SIZE];
			__begin_buffer(buffer);
			auto length = _GetParsedDatetime(buffer + 1, BUFFER_SIZE - 5);
			__end_buffer(buffer + length + 1);
			message.insert(0, buffer);
		}
	}
	else if (IsTypeIncluded())
	{
		char buffer[BUFFER_SIZE];
		__begin_buffer(buffer);
		auto length = _GetParsedType(buffer + 1, BUFFER_SIZE - 5, type);
		__end_buffer(buffer + length + 1);
		message.insert(0, buffer);
	}

	LogMessage msg(this, std::move(message), type, timestamp);
	for (auto listener : _listeners)
		if (listener->IsEnabled())
			listener->Invoke(msg);
}

END_LFRL_COMMON_NAMESPACE
