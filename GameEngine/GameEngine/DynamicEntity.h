//
//  DynamicEntity.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 01/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "CollisionEntity.h"

///@brief Objet dynamique


class DynamicEntity : public CollisionEntity {
private:
    static std::list<DynamicEntity*> list;
    static std::list<DynamicEntity*>::iterator it;
protected:
    sf::Vector2f mySpeed;
    float myFriction, myBounce, myAirFriction, myGravity;
    void TakeAStep();
public:
    ///@brief constructeur simple
    DynamicEntity();
    ///@brief destructeur
    ~DynamicEntity();
    
    ///@brief Automatise le step sur tous les objets
    static void Step();
};