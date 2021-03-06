#include "Sound.h"

std::list<Sound*> Sound::mySounds;
std::list<Sound*>::iterator Sound::mySoundsIt;

Sound::Sound(std::string key) : sf::Sound(Game::GetSoundBuffer(key))
{
	this->SetPitch(Game::timerate);
	Sound::mySounds.push_back(this);
}

Sound::~Sound()
{
	Sound::mySounds.remove(this);
}

void Sound::UpdateAll(float timerate)
{
	for(mySoundsIt = mySounds.begin(); mySoundsIt != mySounds.end(); mySoundsIt++)
	{
		(*mySoundsIt)->SetPitch(timerate);
	}
}

void Sound::DestroyAll()
{
	while(!Sound::mySounds.empty())
		Sound::mySounds.pop_front();
}
