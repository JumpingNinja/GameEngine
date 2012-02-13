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
		/** @brief Détermine si le son pourra être joué plusieurs fois (Défaut : Non)
		**/
		bool myPersistant;

	public:
		/** @brief Contient des pointeurs vers tout les sons
		**/
		static std::list<Sound*> mySounds;
		static std::list<Sound*>::iterator mySoundsIt;

		/** @brief Détruit tout les sons.
		**/
		static void DestroyAll();

		/** @brief Met à jour le pitch en fonction du timerate
		*
		* @todo Probablement optimisable facilement
		**/
		static void UpdateAll(float);

		Sound();
		/** @brief Constructeur à partir d'un SoundBuffer de ResManager
		**/
		Sound(std::string key);

		/** @brief Accesseur de la persistance
		**/
		bool IsPersistant() const { return myPersistant; }

		~Sound();
};
