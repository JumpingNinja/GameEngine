//
//  CollisionEntity.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "CollisionEntity.h"


bool CollisionEntity::IsSolid()
{
    return mySolid;
}

CollisionEntity::CollisionEntity(const bool &solid) : Entity::Entity(), PolygonShape::PolygonShape(), mySolid(solid)
{}

bool CollisionEntity::IsColliding(CollisionEntity &other)
{
    return PolygonShape::IsColliding(other, *this, other);
}