#include "ServiceLocator.h"

TimeService * ServiceLocator::_timeService = nullptr;
LogService * ServiceLocator::_logService = nullptr;
EventService* ServiceLocator::_eventService = nullptr;
UserInterface* ServiceLocator::_userInterface = nullptr;
TextureManager* ServiceLocator::_textureManager = nullptr;
FontManager* ServiceLocator::_fontManager = nullptr;
SoundService* ServiceLocator::_soundService = nullptr;

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
UserInterface* ServiceLocator::getUI()
{
	return _userInterface;
}
TextureManager* ServiceLocator::getTextureManager()
{
	return _textureManager;
}
FontManager* ServiceLocator::getFontManager()
{
	return _fontManager;
}

SoundService* ServiceLocator::getSoundService()
{
	return _soundService;
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
void ServiceLocator::provide(UserInterface* ui)
{
	_userInterface = ui;
}
void ServiceLocator::provide(TextureManager* tm)
{
	_textureManager = tm;
}
void ServiceLocator::provide(FontManager* tm)
{
	_fontManager = tm;
}
void ServiceLocator::provide(SoundService* tm)
{
	_soundService = tm;
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
	if (_userInterface!= nullptr)
	{
		delete _userInterface;
		_userInterface = nullptr;
	}
	if (_textureManager != nullptr)
	{
		delete _textureManager;
		_textureManager = nullptr;
	}

	if (_fontManager != nullptr)
	{
		delete _fontManager;
		_fontManager = nullptr;
	}
	if (_soundService != nullptr)
	{
		delete _soundService;
		_soundService = nullptr;
	}
}