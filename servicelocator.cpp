#include "servicelocator.h"

LogService * ServiceLocator::_log = NULL;

LogService* ServiceLocator::getLog()
{
	return _log;
}
void ServiceLocator::provide(LogService* log)
{
	_log = log;
}