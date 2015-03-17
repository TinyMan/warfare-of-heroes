#pragma once
#include "logservice.h"
#include "TimeService.h"
#include "EventService.h"

class ServiceLocator
{
public:

	static void provide(TimeService *);
	static void provide(LogService *);
	static void provide(EventService*);

	static TimeService * getTimeService();
	static LogService * getLogService();
	static EventService* getEventService();

	static void cleanup();

private:
	static TimeService * _timeService;
	static LogService * _logService;
	static EventService* _eventService;
};

