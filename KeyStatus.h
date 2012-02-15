#ifndef KEYSTATUS_H
#define KEYSTATUS_H

//
// KeyStatus.h
// GameEngine
//

#include <map>
#include <SFML/Window.hpp>

#include "Input.h"
#include "Game.h"

/** @brief Donne le status actuel d'une touche du clavier.
**/
class KeyStatus : public InputStatus {
	private:

	public:
		static std::map<sf::Keyboard::Key, KeyStatus*> map;
		/** @brief Met à jour la liste
		**/
		static void Update();

		KeyStatus(sf::Keyboard::Key Key);
		~KeyStatus();

		static void DestroyAll();
};

#endif
