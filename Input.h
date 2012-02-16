#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SFML/Window.hpp>

#include "Constants.h"

/** @brief Classe générale définissant les touches
*
* Extremement laid pour l'instant... Je cherche la solution. Actuellement l'héritage est foireux : un appel à GetPosition() (pourtant déclarée virtuelle) fait toujours appel à la version de InputStatut, certainement car on manipule uniquement des références à des InputStatus et non des JoystickAxis... Ca donne cette horreur... (tout est placé dans InputStatus en réalité, du coup même les touches du clavier se retrouve avec une fonction GetPosition() et les axes se retrouvent avec des JustPressed() etc...) Bref, tout est à refaire, c'est vraiment trop moche :p
**/
class InputStatus
{
	private:

	public:
		/** @brief Vaut vrai si la touche est appuyée
		**/
		bool myIsKeyPressed;
		/** @brief Vaut vrai si la touche vient d'être appuyée
		**/
		bool myJustPressed;
		/** @brief Vaut vrai si la touche vient d'être relachée
		**/
		bool myJustReleased;

		unsigned int myJoystick;
		sf::Joystick::Axis myAxis;

		static std::map<gb::Key, InputStatus*> map;
		static void UpdateAll();

		InputStatus();
		InputStatus(gb::Key Key);
		InputStatus(gb::Key Key, unsigned int Joystick, sf::Joystick::Axis Axis);
		virtual ~InputStatus();

		bool IsKeyPressed() const { return myIsKeyPressed; }
		bool IsJustPressed() const { return myJustPressed; }
		bool IsJustReleased() const { return myJustReleased; }

		virtual float GetPosition(); //=0 ;

		static void DestroyAll();
};

#endif
