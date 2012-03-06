#ifndef _PHYSICSRIGID_H_
#define _PHYSICSRIGID_H_

#include "PhysicsPoint.h"
#include "PhysicsConstraint.h"

namespace Physics
{

/** @class Rigid
 * @brief Lien rigide (fort) entre deux Points
 *
 * Permet la création de polygones à partir de Points
**/
class Rigid : public Constraint
{
	private:

	public:
		/// @brief Liste des Rigid créés
		static std::list<Rigid*> List;

		/** @brief Appelle Resolve pour tout les Rigid
		 *
		**/
		static void ResolveAll(int iterations = 10);

		/// @brief Détruit tout les VR
		static void DeleteAll();

		Rigid(Point* P1, Point* P2,
						float Length = -1);
		Rigid(Point &P1, Point &P2,
						float Length = -1);
		~Rigid();

		/** @brief Replace les points pour qu'ils respectent la liaison
		 *
		 * @param iterations Nombre d'itérations, un nombre important génère une simulation plus précise.
		**/
		void Resolve(int iterations);
		/// @brief Replace les points pour qu'ils respectent la liaison
		void Resolve();

		void glDraw();
};

}

#endif
