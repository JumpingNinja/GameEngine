#ifndef _Elastic_H_
#define _Elastic_H_

#include "PhysicsVertex.h"
#include "PhysicsConstraint.h"

namespace Physics
{

/** @class Elastic
 * @brief Lien élastique entre deux Vertexs
 *
 * Implémente la loi de Hooke
**/
class Elastic : public Constraint
{
	private:
		float mySpring; ///< Constante de ressort

	public:
		/// @brief Liste des VerletConstraint créés
		static std::list<Elastic*> List;

		/// @brief Appelle Resolve pour tout les Elastic
		static void ResolveAll();

		/// @brief Détruit tout les VC
		static void DeleteAll();

		Elastic(Vertex* P1, Vertex* P2,
						float Length = -1.f, float Spring = 1.f);
		Elastic(Vertex &P1, Vertex &P2,
						float Length = -1.f, float Spring = 1.f);
		~Elastic();

		/** @brief Applique la contrainte
		*
		**/
		void Resolve();

		void glDraw();
};

}

#endif
