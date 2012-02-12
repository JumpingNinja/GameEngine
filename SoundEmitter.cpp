#include "SoundEmitter.h"
#include <iostream>

SoundEmitter::SoundEmitter()
{
}

SoundEmitter::~SoundEmitter()
{
}

std::list<Sound*>::iterator SoundEmitter::AddSound(std::string key)
{
	mySounds.push_back(new Sound(key));
	mySounds.back()->Play();
	return (--mySounds.end());
}

void SoundEmitter::PlaySound(std::list<Sound*>::iterator it)
{
	(*it)->Play();
}

void SoundEmitter::RmSound(std::list<Sound*>::iterator it)
{
	mySounds.erase(it);
}

void SoundEmitter::UpdateSoundList()
{
	for(std::list<Sound*>::iterator it = mySounds.begin(); it != mySounds.end(); it++)
	{
		if((!(*it)->IsPersistant())&&((*it)->GetStatus() == sf::Sound::Stopped))
			RmSound(it), it--; // Pour éviter que l'itérateur sorte de la liste
	}
}
