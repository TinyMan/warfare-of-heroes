#include "SoundService.h"


SoundService::SoundService()
{
	_music = Mix_LoadMUS(MUSIC_FILENAME.c_str());
}


SoundService::~SoundService()
{
	stopMusic();
	Mix_FreeMusic(_music);
	for (auto c : _chunks)
	{
		Mix_FreeChunk(c.second);
	}
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
		Mix_PlayChannel(-1, _chunks[id], 0);
	}

}

void SoundService::loadEffect(string filename, string id)
{
	if (filename.length() > 0 && id.length() > 0)
	{
		if (_chunks.count(id) == 1)
		{
			Mix_FreeChunk(_chunks[id]);
		}
		Mix_Chunk* tmp = Mix_LoadWAV(filename.c_str());
		if (tmp)
		{
			_chunks[id] = tmp;
		}
	}
}