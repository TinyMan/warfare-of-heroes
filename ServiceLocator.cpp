#include "ServiceLocator.h"

TimeService * ServiceLocator::_timeService = nullptr;
LogService * ServiceLocator::_logService = nullptr;
EventService* ServiceLocator::_eventService = nullptr;

TimeService * ServiceLocator::getTimeService()
{
	return _timeService;
}
LogService * ServiceLocator::getLogService()
{
	return _logService;
}
EventService* ServiceLocator::getEventService()
{
	return _eventService;
}

void ServiceLocator::provide(TimeService * ts)
{
	_timeService = ts;
}
void ServiceLocator::provide(LogService * ls)
{
	_logService = ls;
}
void ServiceLocator::provide(EventService* es)
{
	_eventService = es;
}