#ifndef _PHYSICSRECTANGLE_H_
#define _PHYSICSRECTANGLE_H_

#include "PhysicsPolygon.h"

namespace Physics
{

/** @class Rectangle
 * Spécialisation de Physics::Polygon permettant de créer rapidement et
 * simplement des Rectangles rigides.
**/
class Rectangle : public Polygon
{
	public:
		/** @brief Constructeur simple
		 *
		 * @param Width Largeur
		 * @param Height Hauteur
		**/
		Rectangle(float Width, float Heigth);
		/** @brief Constructeur avec masse
		 *
		 * @param Width Largeur
		 * @param Height Hauteur
		 * @param Mass Masse des verticles
		**/
		Rectangle(float Width, float Heigth, float Mass);
		/** @brief Constructeur avec masses pour chaque point
		 *
		 * @param Width Largeur
		 * @param Height Hauteur
		 * @param Mass1
		 * @param Mass2
		 * @param Mass3
		 * @param Mass4
		**/
		Rectangle(float Width, float Heigth, float Mass1, float Mass2, float Mass3, float Mass4);
		~Rectangle();

		/// @brief Retourne une référence vers le point en haut à gauche
		Point& GetTopLeft();
};

}

#endif
