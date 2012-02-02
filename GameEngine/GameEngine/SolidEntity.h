//
//  SolidEntity.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 01/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "CollisionEntity.h"

///@brief Objet solide qui est censé pas bouger


class SolidEntity : public CollisionEntity {
    
public:
    ///@brief constructeur simple
    SolidEntity();
    
    virtual void Update();
};