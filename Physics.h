#ifndef _PHYSICS_H_
#define _PHYSICS_H_

/** @defgroup Physics
 * @todo Vérifier collisions
 * @todo Collisions d'objets élastiques ?
 * @todo Séparer l'affichage
 * @{
**/
#include "PhysicsPoint.h"
#include "PhysicsConstraint.h"
#include "PhysicsElastic.h"
#include "PhysicsRigid.h"
#include "PhysicsPolygon.h"
#include "PhysicsRectangle.h"

namespace Physics
{

/** @brief Met à jour la simulation
 *
 * @param prevdt Intervalle de temps lors de la dernière simulation
 * @param dt Intervalle de temps à considérer
**/
void Update(float prevdt, float dt)
{
	Elastic::ResolveAll();
	Point::UpdateAll(prevdt, dt);

	for(int i=0; i<10; i++)
	Rigid::ResolveAll(),
    Polygon::HandleCollisions();
}

void DeleteAll()
{
	Polygon::DeleteAll();
	Rigid::DeleteAll();
	Elastic::DeleteAll();
	Point::DeleteAll();
}

 void ForceAll(Vec2 V, bool Mass = 0) { Point::ForceAll(V, Mass); }

}
/// @}

#endif
