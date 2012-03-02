#ifndef _PHYSICSPOLYGON_H_
#define _PHYSICSPOLYGON_H_

#include <vector>
#include <list>
#include <cstdarg>

#include "PhysicsPoint.h"
#include "PhysicsRigid.h"

#define FLAG_NULL 0
#define WITH_LENGTH 1


class CollisionInfo {
	public:
		float	Depth;
		Vec2	Normal;
		Rigid*	R;
		Point*	P;

		CollisionInfo() : Depth(0), Normal(0,0), R(0), P(0)
		{
		}

		CollisionInfo(float D, Vec2 N, Rigid* R, Point* P) :
			Depth(D), Normal(N), R(R), P(P)
		{
		}
};

/** @brief Décrit un polygone concave : Ensemble de points (Vertices)
 * reliés par les liaisons rigides (Edges).
 *
 **/
class Polygon
{
	private:
		std::vector<Point*> Vertices;
		std::vector<Rigid*> Edges;

	public:
		static std::list<Polygon*> List;
		/** @brief Détruit tout les VP (et les VR qu'ils contiennent)
		 * Doit être appellé AVANT Constraint ou Rigid ::DeleteAll !
		**/
		static void DeleteAll();
		/** @brief Calcule et gère les collisions de tous les polygones
		**/
		static void CollideAll();

		/** @brief Construteur à partir de VPs et éventuelement de longueurs
		 *
		 * La longueur des liens est déterminée par la position
		 * des VP lors de la création.
		 *
		 * Si le flag WITH_LENGTH est donné, la longueur des liens doit être donnée après chaque point, exemple :
		 * @code
		 * Polygon(3, WITH_LENGTH, VP1, 10.f, VP2, 10.f, VP3, 20.f);
		 * @endcode
		 * Donnera un triangle isocèle en VP2 avec |VP1VP2| = |VP2VP3| = 10 et |VP3VP1| = 20.
		 * ATTENTION ! Les longeurs doivent être explicitement des floats ou des doubles (dans ce dernier cas, elles seront static_cast<float>) sous peine de plantage (dans le cas d'un passage d'un int) à cause de l'utilisation de la macro va_arg ! En effet, lors de l'appel, il n'est précisé nul part que nous travaillerons en float et donc il n'y aucune conversion implicite int -> float.
		 * @param nb Nombre de VP
		 * @param FLAGS FLAG_NULL, WITH_LENGTH
		 * @param ... Liste de Point* [, float]
		**/
		Polygon(int nb, unsigned int FLAGS, ...);
		/** @brief Destructeur
		 *
		 * Détruit également les Rigid crées lors de la construction !
		**/
		~Polygon();

		CollisionInfo Collide(Polygon* o);

		void ProjectToAxis(float &Min, float &Max, Vec2 Axis);

		Rigid& operator[](const unsigned int);
};

#endif
