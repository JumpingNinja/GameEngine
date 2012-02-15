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
    // Créé le son et l'ajoute à la liste de sons de l'objet
	mySounds.push_back(new Sound(key));
	// Le place sur l'objet
	mySounds.back()->sf::SoundSource::SetPosition(CollisionEntity::GetPosition().x, CollisionEntity::GetPosition().y, 0);
	// Renvoi un itérateur sur la liste des sons de l'objet pointant sur le son ajouté
	return (--mySounds.end());
}

void SoundEmitter::PlaySound(std::string key)
{
    (*AddSound(key))->Play();
}

void SoundEmitter::PlaySound(std::list<Sound*>::iterator it)
{
    // Place le son sur l'objet qui le joue
	(*it)->sf::SoundSource::SetPosition(Entity::GetPosition().x, Entity::GetPosition().y, 0);
	// Joue le son
	(*it)->Play();
}

void SoundEmitter::RmSound(std::list<Sound*>::iterator it)
{
	mySounds.erase(it);
}

void SoundEmitter::UpdateSoundList()
{
	std::list<Sound*>::iterator tmp_it;
	for(std::list<Sound*>::iterator it = mySounds.begin(); it != mySounds.end(); it++)
	{
		// Place le son sur l'objet
		(*it)->sf::SoundSource::SetPosition(Entity::GetPosition().x, Entity::GetPosition().y, 0);
		// Supprime les sons non persistant et stoppés.
		if((!(*it)->IsPersistant())&&((*it)->GetStatus() == sf::Sound::Stopped))
			tmp_it = it, it--, RmSound(tmp_it), tmp_it = it; // Pour éviter que l'itérateur sorte de la liste
	}
}
