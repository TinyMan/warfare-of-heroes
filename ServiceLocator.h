#pragma once
#include "LogService.h"
#include "TimeService.h"
#include "EventService.h"
#include "UserInterface.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundService.h"

using namespace Events;

#define UI ServiceLocator::getUI()
#define TIMESERVICE ServiceLocator::getTimeService()
#define SOUNDSERVICE ServiceLocator::getSoundService()

class ServiceLocator
{
public:

	static void provide(TimeService *);
	static void provide(LogService *);
	static void provide(EventService*);
	static void provide(UserInterface*);
	static void provide(TextureManager*);
	static void provide(FontManager*);
	static void provide(SoundService*);

	static TimeService * getTimeService();
	static LogService * getLogService();
	static EventService* getEventService();
	static UserInterface* getUI();
	static TextureManager* getTextureManager();
	static FontManager* getFontManager();
	static SoundService* getSoundService();

	static void cleanup();

private:
	static TimeService * _timeService;
	static LogService * _logService;
	static EventService* _eventService;
	static UserInterface* _userInterface;
	static TextureManager* _textureManager;
	static FontManager* _fontManager;
	static SoundService* _soundService;
};

