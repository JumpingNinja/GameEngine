#ifndef PLAYABLE_H
#define PLAYABLE_H

//
// Playable.h
// GameEngine
//

/** @brief D�signe les Colisions Entity devant r�agir � des inputs
*
**/
class Playable {
	private :
	/** @brief myControled Sp�cifie si l'objet doit prendre en compte les entr�es de l'utilisateur.
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
