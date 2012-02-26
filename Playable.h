#ifndef PLAYABLE_H
#define PLAYABLE_H

//
// Playable.h
// GameEngine
//

#include "CollisionEntity.h"

/** @brief Désigne les CollisionEntity devant réagir à des inputs
*
* Héritage "horizontal" : Cette classe doit être héritée uniquement sur des CollisionEntity.
* Exemple : \n
* class guyTest : public CollisionEntity, public Playable { }
**/
class Playable : virtual public CollisionEntity {
	private :
	/** @brief myControled Spécifie si l'objet doit prendre en compte les entrées de l'utilisateur.
	**/
		bool myControled;

		/// @brief Coefficient de contrôle au sol
		float myGroundControl;
		/// @brief Coefficient de contrôle aérien
		float myAirControl;
	public:
		Playable();
		Playable(bool);
		virtual ~Playable();
		bool IsControled()const ;
		void SetControled(bool aControled = 1);

        /** @brief Fonction générique de saut
        *
        **/
		virtual void Jump();
		virtual void WallJump(short int factor);
        /** @brief Fonction générique de mouvement à gauche
        *
        **/
		virtual void MoveLeft();
		virtual void AirControlLeft();
        /** @brief Fonction générique de mouvement à droite
        *
        **/
		virtual void MoveRight();
		virtual void AirControlRight();
		void MoveAxis(float Axis);
		void AirControlAxis(float Axis);
};

#endif
