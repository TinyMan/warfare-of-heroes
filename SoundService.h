#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class SoundService
{
public:
	SoundService();
	virtual ~SoundService();

	virtual void playMusic();
	virtual void pauseMusic();
	virtual void stopMusic();
	virtual void playEffect(string id);

};

