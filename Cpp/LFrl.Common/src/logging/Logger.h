#ifndef __LFRL_COMMON_LOGGER_GUARD__
#define __LFRL_COMMON_LOGGER_GUARD__

#include <chrono>
#include <array>
#include <vector>
#include <sstream>
#include "LogMessage.h"
#include "../diagnostics/Stopwatch.h"

BEGIN_LFRL_NAMESPACE

struct ILoggerListener;

class Logger
{
	Logger(Logger const&) = delete;
	Logger& operator= (Logger const&) = delete;

public:
	struct DateTimeFormat
	{
		enum struct Year
		{
			DISABLED = 0,
			SHORT = 1,
			LONG = 2
		};
		enum struct Month
		{
			DISABLED = 0,
			NUMERIC = 1,
			ABBREVIATED = 2,
			FULL = 3
		};
		enum struct Numeric
		{
			DISABLED = 0,
			ENABLED = 1
		};
		enum struct Timezone
		{
			DISABLED = 0,
			ABBREVIATED = 1,
			GMT_OFFSET = 2,
			FULL = 3
		};
		enum struct Clock
		{
			C_24_HOUR = 0,
			C_12_HOUR = 1
		};
		enum struct Layout
		{
			YEAR_MONTH_DAY = 0,
			YEAR_DAY_MONTH = 1,
			DAY_MONTH_YEAR = 2,
			MONTH_DAY_YEAR = 3
		};
		enum struct Order
		{
			DATE_FIRST = 0,
			TIME_FIRST = 1
		};

		struct DateFormat
		{
			Year year;
			Month month;
			Numeric day;
			Layout layout;
			char separator;

			explicit DateFormat(
				Year year = Year::LONG,
				Month month = Month::NUMERIC,
				Numeric day = Numeric::ENABLED,
				Layout layout = Layout::YEAR_MONTH_DAY,
				char separator = '-');
		} date;

		struct TimeFormat
		{
			Numeric hour;
			Numeric minute;
			Numeric second;
			Numeric millisecond;
			Timezone timezone;
			Clock clock;
			char separator;

			explicit TimeFormat(
				Numeric hour = Numeric::ENABLED,
				Numeric minute = Numeric::ENABLED,
				Numeric second = Numeric::ENABLED,
				Numeric millisecond = Numeric::ENABLED,
				Timezone timezone = Timezone::DISABLED,
				Clock clock = Clock::C_24_HOUR,
				char separator = ':');
		} time;

		Order order;
		char component_separator;
		bool localtime;

		explicit DateTimeFormat(
			DateFormat date = DateFormat(),
			TimeFormat time = TimeFormat(),
			Order order = Order::DATE_FIRST,
			char component_separator = ' ',
			bool localtime = true);

		std::string create_format() const;
	};

	Logger();
	Logger(Logger&&);
	Logger& operator= (Logger&&);
	virtual ~Logger();

	std::vector<ILoggerListener*> const& GetListeners() const noexcept;

	bool AddListener(ILoggerListener* listener);
	u32 RemoveListener(ILoggerListener const* listener);
	void ClearListeners();

	void EnableAll() noexcept;
	void DisableAll() noexcept;
	void EnableDebug() noexcept;
	void DisableDebug() noexcept;
	void EnableInfo() noexcept;
	void DisableInfo() noexcept;
	void EnableSuccess() noexcept;
	void DisableSuccess() noexcept;
	void EnableWarning() noexcept;
	void DisableWarning() noexcept;
	void EnableError() noexcept;
	void DisableError() noexcept;
	void Enable(LogMessage::Type type) noexcept;
	void Disable(LogMessage::Type type) noexcept;

	bool IsDebugEnabled() const noexcept;
	bool IsInfoEnabled() const noexcept;
	bool IsSuccessEnabled() const noexcept;
	bool IsWarningEnabled() const noexcept;
	bool IsErrorEnabled() const noexcept;
	bool IsEnabled(LogMessage::Type type) const noexcept;

	bool IsDatetimeIncluded() const noexcept;
	void IncludeDatetime(bool value = true) noexcept;
	void ExcludeDatetime(bool value = true) noexcept;
	bool IsTypeIncluded() const noexcept;
	void IncludeType(bool value = true) noexcept;
	void ExcludeType(bool value = true) noexcept;

	std::string const& GetDatetimeFormat() const noexcept;
	DateTimeFormat GetDatetimeFormatDescriptor() const noexcept;
	void SetDatetimeFormatDescriptor(DateTimeFormat descriptor);

	u64 GetLifetime() const;

	void Log(LogMessage::Type type, std::string const& message) const;
	void Log(LogMessage::Type type, std::string&& message) const;
	void Log(LogMessage::Type type, std::ostringstream const& message) const;
	void Log(LogMessage::Type type, char const* message) const;
	void LogDebug(std::string const& message) const;
	void LogDebug(std::string&& message) const;
	void LogDebug(std::ostringstream const& message) const;
	void LogDebug(char const* message) const;
	void LogInfo(std::string const& message) const;
	void LogInfo(std::string&& message) const;
	void LogInfo(std::ostringstream const& message) const;
	void LogInfo(char const* message) const;
	void LogSuccess(std::string const& message) const;
	void LogSuccess(std::string&& message) const;
	void LogSuccess(std::ostringstream const& message) const;
	void LogSuccess(char const* message) const;
	void LogWarning(std::string const& message) const;
	void LogWarning(std::string&& message) const;
	void LogWarning(std::ostringstream const& message) const;
	void LogWarning(char const* message) const;
	void LogError(std::string const& message) const;
	void LogError(std::string&& message) const;
	void LogError(std::ostringstream const& message) const;
	void LogError(char const* message) const;

protected:
	static constexpr u32 BUFFER_SIZE = 128;

	virtual u32 ParseDebugType(char* buffer, u32 buffer_size) const;
	virtual u32 ParseInfoType(char* buffer, u32 buffer_size) const;
	virtual u32 ParseSuccessType(char* buffer, u32 buffer_size) const;
	virtual u32 ParseWarningType(char* buffer, u32 buffer_size) const;
	virtual u32 ParseErrorType(char* buffer, u32 buffer_size) const;

private:
	std::vector<ILoggerListener*> _listeners;
	DateTimeFormat _datetimeFormatDescriptor;
	std::string _datetimeFormat;
	StopWatch _stopwatch;
	u8 _configuration;

	void _DisposeListeners() const;

	bool _GetConfigurationFlag(u8 position) const noexcept;
	void _EnableConfigurationFlag(u8 position) noexcept;
	void _DisableConfigurationFlag(u8 position) noexcept;

	u32 _GetParsedDatetime(char* buffer, u32 buffer_size) const;
	u32 _GetParsedType(char* buffer, u32 buffer_size, LogMessage::Type type) const;

	void _Log(LogMessage::Type type, std::string&& message) const;
};

END_LFRL_NAMESPACE

#endif
