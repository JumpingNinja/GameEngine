#ifndef _VERLETRIGID_H_
#define _VERLETRIGID_H_

#include <SFML/System/Vector2.hpp>

#include "VerletPoint.h"

/** @class VerletRigid
 * @brief Lien rigide (fort) entre deux VerletPoints
 *
 * Permet la création de polygones à partir de VerletPoints
**/
class VerletRigid
{
	private:
		VerletPoint* P1;
		VerletPoint* P2;
		float myLength; ///< Longueur

	public:
		/// @brief Liste des VerletRigid créés
		static std::list<VerletRigid*> VRList;

		/// @brief Appelle Replace pour tout les VerletRigid
		static void ReplaceAll(int iterations = 10);

		/// @brief Détruit tout les VR
		static void DeleteAll();

		VerletRigid(VerletPoint* P1, VerletPoint* P2,
						float Length = -1);
		VerletRigid(VerletPoint &P1, VerletPoint &P2,
						float Length = -1);
		~VerletRigid();

		/** @brief Replace les points pour qu'ils respectent la liaison
		 *
		 * @param iterations Nombre d'itérations, un nombre important génère une simulation plus précise.
		**/
		void Replace(int iterations = 10);
};

#endif
