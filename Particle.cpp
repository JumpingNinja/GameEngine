//
//  Particle.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 08/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Particle.h"

std::list<Particle*> Particle::list;
std::list<Particle*>::iterator Particle::it;


void ParticleInfo::SetInfo(sf::Vector2f const &aSpeed, sf::Vector2f const &aIncrSpeed, sf::Vector2f const &aGravity, sf::Vector2f const &aSize, sf::Vector2f const &aIncrSize, sf::Vector2f const &aFriction, float aLife, float aAlpha1, float aAlpha2, float aAlpha3, sf::Color aColor1, sf::Color aColor2, sf::Color aColor3, bool aCanOut, short aDepth)
{
    Speed=aSpeed;
    IncrSpeed=aIncrSpeed;
    Gravity=aGravity;
    Size=aSize;
    IncrSize=aIncrSize;
    Friction=aFriction;
    Life=aLife;
    Alpha1=aAlpha1;
    Alpha2=aAlpha2;
    Alpha3=aAlpha3;
    Color1=aColor1;
    Color2=aColor2;
    Color3=aColor3;
    CanOut=aCanOut;
    Depth=aDepth;
}

Particle::Particle(const ParticleInfo& Info) : myInfo(Info), Entity(myInfo.Depth), mySize(myInfo.Size), mySpeed(myInfo.Speed)
{
    list.push_back(this);
}

Particle::~Particle()
{
    for ( it=list.begin(); it!=list.end(); it++)
    {
        if ((*it)==this)
            break;
    }
    
    if ((*it)==this)
        list.erase(it);
}

void Particle::TakeAStep()
{
    Move(mySpeed);
    mySpeed+=myInfo.Gravity;
    mySpeed+=myInfo.IncrSize;
    mySize+=myInfo.IncrSize;
    mySpeed.x+=myInfo.Friction.x;
    mySpeed.y+=myInfo.Friction.y;
    
}

void Particle::Step()
{
    for (it=list.begin(); it!=list.end(); it++)
        (*it)->TakeAStep();
}