#ifndef KEYSTATUS_H
#define KEYSTATUS_H

//
// KeyStatus.h
// GameEngine
//

/*
TODO :
Ajouter dans le constructeur de Game de quoi lister toutes les touches accessibles et cr�er le KeyStatus associ�
Cr�er une map liant un string � une touche (dans Game ?)
	std::map<string, sf::Keyboard::Key> Bindings;
et enfin de quoi acc�der facilement � l'�tat cherch� � partir du string (ex : "Shoot")
*/

#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/** @brief Donne le status actuel d'une touche du clavier, public.
**/
class KeyStatus {
	private:
		/** @brief Vaut vrai si la touche est appuy�e
		**/
		bool myIsKeyPressed;
		/** @brief Vaut vrai si la touche vient d'�tre appuy�e
		**/
		bool myJustPressed;
		/** @brief Vaut vrai si la touche vient d'�tre relach�e
		**/
		bool myJustReleased;

	public:
		static std::map<sf::Keyboard::Key, KeyStatus*> map;
		/** @brief Met � jour la liste
		**/
		static void Update(sf::RenderWindow &myMainWindow);

		bool IsKeyPressed() { return myIsKeyPressed; }
		bool IsJustPressed() { return myJustPressed; }
		bool IsJustReleased() { return myJustReleased; }
		KeyStatus(sf::Keyboard::Key Key);
		~KeyStatus();
};

#endif
