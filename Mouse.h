#ifndef MOUSE_H
#define MOUSE_H

#include <map>
#include <SFML/Window.hpp>

#include "Input.h"

/** @brief Classe générale définissant les touches
*
**/
class MouseStatus : public InputStatus
{
	private:

	public:
		static std::map<sf::Mouse::Button, MouseStatus*> map;
		/** @brief Met à jour la liste
		**/
		static void UpdateAll();

		MouseStatus(sf::Mouse::Button Button);
		~MouseStatus();

		static void DestroyAll();
};

#endif

