//
//  SolidEntity.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 01/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "SolidEntity.h"

SolidEntity::SolidEntity() : CollisionEntity(1)
{
    
}

void SolidEntity::Update()
{
    PolygonShape::Update();
    CollisionGrid::AssignCells(this, 0);
}