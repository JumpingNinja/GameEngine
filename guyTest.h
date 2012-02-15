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
#include "Particle.h"
#include "Sound.h"
#include "SoundEmitter.h"


class guytest : virtual public CollisionEntity, public Playable, private Animation, public SoundEmitter {
	ParticleInfo pInfo, pStar;
public:
    guytest();
    ~guytest();
    virtual void TakeAStep(bool useFriction=1);
};
