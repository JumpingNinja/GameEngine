#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SFML/Window.hpp>

#include "Constants.h"

/** @brief Classe générale définissant les touches
*
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

		static std::map<gb::Key, InputStatus*> map;
		//static void UpdateAll();

		InputStatus(gb::Key Key);

		virtual ~InputStatus();

		bool IsKeyPressed() const { return myIsKeyPressed; }
		bool IsJustPressed() const { return myJustPressed; }
		bool IsJustReleased() const { return myJustReleased; }

		static void DestroyAll();
	
	/**
	 @brief Donne la valeur associée à un bouton d'un Joystick
	 @param iJoy index du joystick 0-7
	 @param iBut index du boutons 0-31
	 @return valeur associé au bouton spécifié
	 **/
	static inline gb::Key JoystickButton(unsigned short iJoy, unsigned short iBut) { return static_cast<gb::Key>(gb::Joy0_1+32*iJoy+iBut); }
};

#endif
