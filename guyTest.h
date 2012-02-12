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
#include "Playable.h"
#include "Sound.h"
#include "SoundEmitter.h"


class guytest : public CollisionEntity, public Playable, private Animation, public SoundEmitter {

public:
    guytest();
    ~guytest();
    virtual void TakeAStep(bool useFriction=1);
};
