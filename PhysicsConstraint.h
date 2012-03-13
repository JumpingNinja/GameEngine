#ifndef _PHYSICSCONSTRAINT_H_
#define _PHYSICSCONSTRAINT_H_

#include "PhysicsVertex.h"


namespace Physics
{

/** @class Constraint
 * @brief Lien entre deux Vertexs
 *
 * Classe à usage interne, doit être héritée.
**/
class Constraint
{
	protected:
		Vertex*	P1;
		Vertex*	P2;
		float	myLength; ///< Longueur à l'équilibre
	static std::list<Constraint*> list;

	public:
		Constraint(Vertex* P1, Vertex* P2, float Length = -1);
		Constraint(Vertex &P1, Vertex &P2, float Length = -1);
		virtual ~Constraint();

		/// @brief Applique la contrainte
		virtual void Resolve() =0;

		/// @brief Accesseur de P1
		Vertex* GetP1() { return P1; }
		/// @brief Accesseur de P2
		Vertex* GetP2() { return P2; }

		/// @brief Retourne le vecteur associé à la contrainte (dans le sens P1 vers P2)
		Vec2 GetVector() { return (P2->GetPosition() - P1->GetPosition()); }

	virtual void glDraw() =0;
	static void DrawAll();
};

}

#endif
