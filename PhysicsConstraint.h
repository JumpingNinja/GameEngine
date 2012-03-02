#ifndef _PHYSICSCONSTRAINT_H_
#define _PHYSICSCONSTRAINT_H_

#include "PhysicsPoint.h"

/** @class Constraint
 * @brief Lien entre deux Points
 *
 * Classe à usage interne, doit être héritée.
**/
class Constraint
{
	protected:
		Point*	P1;
		Point*	P2;
		float	myLength; ///< Longueur à l'équilibre

	public:
		Constraint(Point* P1, Point* P2, float Length = -1);
		Constraint(Point &P1, Point &P2, float Length = -1);
		virtual ~Constraint();

		/// @brief Applique la contrainte
		virtual void Resolve() =0;

		/// @brief Retourne le vecteur associé à la contrainte (dans le sens P1 vers P2)
		Vec2 GetVector() { return P2->GetPosition() - P1->GetPosition(); }
};

#endif
