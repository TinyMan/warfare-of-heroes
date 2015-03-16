#include "ServiceLocator.h"

TimeService * ServiceLocator::_timeService = NULL;
LogService * ServiceLocator::_logService = NULL;

TimeService * ServiceLocator::getTimeService()
{
	return _timeService;
}
LogService * ServiceLocator::getLogService()
{
	return _logService;
}


void ServiceLocator::provide(TimeService * ts)
{
	_timeService = ts;
}
void ServiceLocator::provide(LogService * ls)
{
	_logService = ls;
}