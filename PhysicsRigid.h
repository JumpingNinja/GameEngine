#ifndef _PHYSICSRIGID_H_
#define _PHYSICSRIGID_H_

#include "PhysicsVertex.h"
#include "PhysicsConstraint.h"

namespace Physics
{

/** @class Rigid
 * @brief Lien rigide (fort) entre deux Vertexs
 *
 * Permet la création de polygones à partir de Vertexs
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

		Rigid(Vertex* P1, Vertex* P2,
						float Length = -1);
		Rigid(Vertex &P1, Vertex &P2,
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
