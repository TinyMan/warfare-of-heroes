#pragma once
#include "logservice.h"


class ServiceLocator
{
public:
	static void provide(LogService*);
	static LogService* getLog();

private:
	static LogService* _log;
};
