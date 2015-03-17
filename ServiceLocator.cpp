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

void ServiceLocator::cleanup()
{
	if (_timeService != nullptr)
	{
		delete _timeService;
		_timeService = nullptr;
	}
	if (_logService != nullptr)
	{
		delete _logService;
		_logService = nullptr;
	}
	if (_eventService != nullptr)
	{
		delete _eventService;
		_eventService = nullptr;
	}
}