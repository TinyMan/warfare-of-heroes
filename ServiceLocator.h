#pragma once
#include "logservice.h"
#include "TimeService.h"

class ServiceLocator
{
public:

	static void provide(TimeService *);
	static void provide(LogService *);

	static TimeService * getTimeService();
	static LogService * getLogService();

private:
	static TimeService * _timeService;
	static LogService * _logService;
};

