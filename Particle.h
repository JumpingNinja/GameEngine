//
//  Particle.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 08/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include "Entity.h"

const float NoDeath(-50.f);

struct ParticleInfo {
    sf::Vector2f Speed, IncrSpeed, Gravity, Size, IncrSize, Friction;
    float Life, Alpha1, Alpha2, Alpha3;
    sf::Color Color1, Color2, Color3;
    bool CanOut;
    short Depth;
    
    void SetInfo(const sf::Vector2f &aSpeed, const sf::Vector2f &aIncrSpeed, const sf::Vector2f &aGravity, const sf::Vector2f &aSize, const sf::Vector2f &aIncrSize, const sf::Vector2f &aFriction, float aLife, float aAlpha1, float aAlpha2, float aAlpha3, sf::Color aColor1, sf::Color aColor2, sf::Color aColor3, bool aCanOut, short aDepth);
};

class Particle : public Entity {
    const ParticleInfo& myInfo;
    sf::Vector2f mySpeed, mySize;
    static std::list<Particle*> list;
    static std::list<Particle*>::iterator it;
    void TakeAStep();
public:
    Particle(const ParticleInfo &Info);
    ~Particle();
    
    static void Step(); 
    
};