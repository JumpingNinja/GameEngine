#ifndef _VERLETCONSTRAINT_H_
#define _VERLETCONSTRAINT_H_

#include <SFML/System/Vector2.hpp>

#include "VerletPoint.h"

/** @class VerletConstraint
 * @brief Lien entre deux VerletPoints
 *
 * Implémente la loi de Hooke
**/
class VerletConstraint
{
	private:
		VerletPoint* P1;
		VerletPoint* P2;
		float myLength; ///< Longueur à l'équilibre
		float mySpring; ///< Constante de ressort
	public:
		VerletConstraint(VerletPoint* P1, VerletPoint* P2, float Length, float Spring = 1);
		~VerletConstraint();

		/** @brief Applique la contrainte
		*
		**/
		void Resolve();
};

#endif
