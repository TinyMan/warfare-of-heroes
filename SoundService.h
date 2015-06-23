#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>

using namespace std;

class SoundService
{
public:
	SoundService();
	virtual ~SoundService();

	virtual void playMusic();
	virtual void pauseMusic();
	virtual void stopMusic();
	virtual void toggleMusic();
	virtual bool isMusicPlaying() const { return Mix_PlayingMusic() != 0 && Mix_PausedMusic() == 0; }
	virtual void playEffect(string id);
	virtual void loadEffect(string filename, string id);

	const string MUSIC_FILENAME = "sound/theme.wav";

private:
	map<string, Mix_Chunk*> _chunks;
	Mix_Music* _music;

};

