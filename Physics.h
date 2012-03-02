#ifndef _PHYSICS_H_
#define _PHYSICS_H_

/** @defgroup Physics
 * @todo Implémenter SAT
 * @{
**/
#include "PhysicsPoint.h"
#include "PhysicsConstraint.h"
#include "PhysicsElastic.h"
#include "PhysicsRigid.h"
#include "PhysicsPolygon.h"

namespace Physics
{

/** @brief Met à jour la simulation
 *
 * @param prevdt Intervalle de temps lors de la dernière simulation
 * @param dt Intervalle de temps à considérer
**/
void Update(float prevdt, float dt)
{
	Polygon::HandleCollisions();
	Rigid::ResolveAll(), // Les Rigid doivent être gérés avant les Elastic
	Elastic::ResolveAll(),
	Point::UpdateAll(prevdt, dt);

}

void DeleteAll()
{
	Polygon::DeleteAll();
	Rigid::DeleteAll();
	Elastic::DeleteAll();
	Point::DeleteAll();
}

inline void ForceAll(Vec2 V) { Point::ForceAll(V); }

}
/// @}

#endif
