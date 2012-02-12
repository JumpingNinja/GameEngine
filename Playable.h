#ifndef PLAYABLE_H
#define PLAYABLE_H

//
// Playable.h
// GameEngine
//

/** @brief Désigne les Colisions Entity devant réagir à des inputs
*
**/
class Playable {
	private :
	/** @brief myControled Spécifie si l'objet doit prendre en compte les entrées de l'utilisateur.
	**/
		bool myControled;
	public:
		Playable();
		Playable(bool);
		~Playable();
		bool IsControled() { return myControled; }
		void SetControled(bool aControled = 1) { myControled = aControled; }
};

#endif
