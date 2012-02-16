#ifndef JOYSTICK_H
#define JOYSTICK_H

//
// KeyStatus.h
// GameEngine
//

#include <map>
#include <SFML/Window.hpp>

#include "Input.h"
#include "Game.h"

class JoystickAxis : public InputStatus
{
	private:
		/*unsigned int myJoystick;
		sf::Joystick::Axis myAxis;*/
	public:
		//static std::map<sf::Joystick::Axis, JoystickAxis*> map;

		JoystickAxis(unsigned int Joystick, sf::Joystick::Axis Axis);
		~JoystickAxis();

		float GetPosition();
};

/** @brief Donne le status actuel d'un boutton d'un Joystick.
**/
class JoyButtonStatus : public InputStatus {
	private:

	public:
		static std::map<unsigned int, JoyButtonStatus*> map;
		/** @brief Met à jour la liste
		**/
		static void UpdateAll();

		/** @brief Constructeur par défaut
		*
		* @param Button En 0 et 32*8-1, par 0 désigne le premier bouton du premier Joystick, 33 le deuxième du deuxième joystick, etc...
		**/
		JoyButtonStatus(unsigned int Button);
		~JoyButtonStatus();

		static void DestroyAll();
};

#endif
