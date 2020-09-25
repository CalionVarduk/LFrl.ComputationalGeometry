#include "ILoggerListener.h"

BEGIN_LFRL_COMMON_NAMESPACE

ILoggerListener::ILoggerListener() noexcept
	: _isEnabled(true), _logger(nullptr)
{}

END_LFRL_COMMON_NAMESPACE
