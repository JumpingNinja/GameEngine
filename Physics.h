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
	for(std::list<Point*>::iterator it = Point::List.begin(); it != Point::List.end(); it++)
	{
		if((*it)->GetPosition().x > 800)
			(*it)->SetPosition(Vec2(800.f, (*it)->GetPosition().y));
		if((*it)->GetPosition().x < 0)
			(*it)->SetPosition(Vec2(0.f, (*it)->GetPosition().y));
		if((*it)->GetPosition().y > 600)
			(*it)->SetPosition(Vec2((*it)->GetPosition().x, 600.f));
		if((*it)->GetPosition().y < 0)
			(*it)->SetPosition(Vec2((*it)->GetPosition().x, 0.f));

        // Teste si une coordonnée vaut NaN
        if((*it)->GetPosition().x != (*it)->GetPosition().x || (*it)->GetPosition().y != (*it)->GetPosition().y)
        {
            (*it)->SetPosition(Vec2(0, 0), 1);
        }
	}
	/*for(int i=0; i<50; i++)*/ Polygon::HandleCollisions();
	Rigid::ResolveAll();
	 // Les Rigid doivent être gérés avant les Elastic
	Elastic::ResolveAll();
	Point::UpdateAll(prevdt, dt);
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
