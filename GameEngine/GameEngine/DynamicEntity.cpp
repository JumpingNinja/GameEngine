//
//  DynamicEntity.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 01/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "DynamicEntity.h"
#include <iostream>

std::list<DynamicEntity*> DynamicEntity::list;
std::list<DynamicEntity*>::iterator DynamicEntity::it;

DynamicEntity::DynamicEntity() : CollisionEntity(0), mySpeed(sf::Vector2f()), myFriction(0.5f), myBounce(0.5f), myAirFriction(0.f), myGravity(0.3f)
{
    list.push_back(this);
}

DynamicEntity::~DynamicEntity()
{
    for ( DynamicEntity::it=DynamicEntity::list.begin(); DynamicEntity::it!=DynamicEntity::list.end(); DynamicEntity::it++)
    {
        if ((*DynamicEntity::it)==this)
            break;
    }
    
    if ((*DynamicEntity::it)==this)
        DynamicEntity::list.erase(DynamicEntity::it);
}

void DynamicEntity::TakeAStep()
{
    mySpeed.y+=myGravity;
    
    SetPosition(GetPosition()+mySpeed);
    CollisionGrid::AssignCells(this);
    
    std::list<GridCell*>::iterator accesIt;
    std::list<CollisionEntity*>::iterator cellIt;
    
    //std::cout<<"Number of Cells containing object:"<<CollisionGrid::accessList.size()<<std::endl;
    for (accesIt=CollisionGrid::accessList.begin(); accesIt!=CollisionGrid::accessList.end(); accesIt++)
    {
        //std::cout<<"Number of entities inside the cell "<<(*accesIt)<<" :"<<(*accesIt)->myInstances.size()<<std::endl;
        for (cellIt=(*accesIt)->myInstances.begin(); cellIt!=(*accesIt)->myInstances.end(); cellIt++)
        {
            //Ne pas vérifier avec soi même!
            if ((*cellIt)==this) break;
            
            if (IsColliding(**cellIt))
            {
                //std::cout<<"Collision!\n";
                //Check relative position and bounce
                mySpeed.y=-(mySpeed.y*0.8f);
            }
        }
    }
    
    
}

void DynamicEntity::Step()
{
    for (it=list.begin(); it!=list.end(); it++)
    {
        (*it)->TakeAStep();
    }
}
