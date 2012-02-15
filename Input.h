#ifndef INPUT_H
#define INPUT_H

#include <map>

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
		static void Update();

		InputStatus();
		InputStatus(gb::Key Key);
		~InputStatus();

		bool IsKeyPressed() const { return myIsKeyPressed; }
		bool IsJustPressed() const { return myJustPressed; }
		bool IsJustReleased() const { return myJustReleased; }

		static void DestroyAll();
};

#endif
