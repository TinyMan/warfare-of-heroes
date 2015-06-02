#include "SoundService.h"


SoundService::SoundService()
{
	_music = Mix_LoadMUS(MUSIC_FILENAME.c_str());
}


SoundService::~SoundService()
{
	stopMusic();
}

void SoundService::playMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(_music, -1);
	}
	else if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}
void SoundService::pauseMusic()
{
	Mix_PauseMusic();
}
void SoundService::stopMusic()
{
	Mix_HaltMusic();
}
void SoundService::toggleMusic()
{
	//If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(_music, -1);
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}
void SoundService::playEffect(string id)
{
	if (_chunks.count(id) == 1)
	{

	}

}