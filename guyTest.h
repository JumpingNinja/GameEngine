//
//  guyTest.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include "CollisionEntity.h"
#include "Animation.h"


class guytest : public CollisionEntity, private Animation {
    
public:
    guytest();
    ~guytest();
    virtual void TakeAStep();
};