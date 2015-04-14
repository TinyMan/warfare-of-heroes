#pragma once
#include "LogService.h"
#include "TimeService.h"
#include "EventService.h"
#include "UserInterface.h"

#define TYPENAME(x) typeid(x).name()
using namespace Events;

#define UI ServiceLocator::getUI()
#define TIMESERVICE ServiceLocator::getTimeService()

class ServiceLocator
{
public:

	static void provide(TimeService *);
	static void provide(LogService *);
	static void provide(EventService*);
	static void provide(UserInterface*);

	static TimeService * getTimeService();
	static LogService * getLogService();
	static EventService* getEventService();
	static UserInterface* getUI();


	static void cleanup();

private:
	static TimeService * _timeService;
	static LogService * _logService;
	static EventService* _eventService;
	static UserInterface* _userInterface;
};

