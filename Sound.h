#pragma once

#include <SFML/Audio.hpp>
#include <list>

#include "Game.h"
#include "ResManager.h"

/** @brief Son personalisé
*
* Se construit à partir d'un SoundBuffer de ResManager
**/
class Sound : public sf::Sound
{
	private:
		bool myPersistant;

	public:
		static std::list<Sound*> mySounds;
		static std::list<Sound*>::iterator mySoundsIt;

		/** @brief Détruit tout les sons.
		**/
		static void DestroyAll();

		/** @brief Met à jour le pitch en fonction du timerate
		**/
		static void UpdateAll();

		Sound();
		/** @brief Constructeur à partir d'un SoundBuffer de ResManager
		**/
		Sound(std::string key);

		bool IsPersistant() { return myPersistant; }

		~Sound();
};
