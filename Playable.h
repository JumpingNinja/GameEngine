#ifndef PLAYABLE_H
#define PLAYABLE_H

//
// Playable.h
// GameEngine
//

#include "CollisionEntity.h"

/** @brief D�signe les CollisionEntity devant r�agir � des inputs
*
* H�ritage "horizontal" : Cette classe doit �tre h�rit�e uniquement sur des CollisionEntity.
* Exemple : \n
* class guyTest : public CollisionEntity, public Playable { }
**/
class Playable : virtual public CollisionEntity {
	private :
	/** @brief myControled Sp�cifie si l'objet doit prendre en compte les entr�es de l'utilisateur.
	**/
		bool myControled;
	public:
		Playable();
		Playable(bool);
		virtual ~Playable();
		bool IsControled()const ;
		void SetControled(bool aControled = 1);

        /** @brief Fonction g�n�rique de saut
        *
        **/
		virtual void Jump();
		virtual void Jump(short int factor);
        /** @brief Fonction g�n�rique de mouvement � gauche
        *
        **/
		virtual void MoveLeft();
		virtual void AirControlLeft();
        /** @brief Fonction g�n�rique de mouvement � droite
        *
        **/
		virtual void MoveRight();
		virtual void AirControlRight();
};

#endif
