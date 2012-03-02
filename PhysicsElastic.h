#ifndef _Elastic_H_
#define _Elastic_H_

#include "PhysicsPoint.h"
#include "PhysicsConstraint.h"

/** @class Elastic
 * @brief Lien élastique entre deux Points
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

		Elastic(Point* P1, Point* P2,
						float Length = -1, float Spring = 1);
		Elastic(Point &P1, Point &P2,
						float Length = -1, float Spring = 1);
		~Elastic();

		/** @brief Applique la contrainte
		*
		**/
		void Resolve();
};

#endif
