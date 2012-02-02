//
//  CollisionEntity.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include "Entity.h"
#include "PolygonShape.h"
#include "CollisionGrid.h"

class CollisionEntity : public Entity, public PolygonShape {
private:
    //static grid[][];
    //sstatic std::list<CollisionEntity*>::iterator it;
protected:
    bool mySolid; //Solid object don't move
public:
    ///@brief Return if the Entity is a solid object
    ///@return true if soled else otherway
    bool IsSolid();
    ///@brief Constructeur par défaut
    ///@param solid défini si l'objet est solide ou pas
    CollisionEntity(const bool &solid);
    ///@brief Donne si deux entites collisionnent
    ///@param other une autre entité
    ///@return vrai s'il elles collisionnent, faux sinon
    bool IsColliding(CollisionEntity &other);
};