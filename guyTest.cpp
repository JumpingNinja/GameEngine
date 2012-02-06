//
//  guyTest.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "guyTest.h"
#include "Game.h"

/*
guytest::guytest() : CollisionEntity(0), Animation(Game::GetTexture("player"), 5.f, Game::GetAnimation("player_walk"))
{
    Width=11; Height=17;
    SetSpeed(sf::Vector2f(20.f, 4.f));
    SetDepth(-2);
}*/

guytest::guytest() : CollisionEntity(0), Animation(Game::GetTexture("ryu"), 6.f, Game::GetAnimation("ryu_walk"))
{
    Width=22; Height=31;
    SetSpeed(sf::Vector2f(20.f, 4.f));
    SetDepth(-2);
}

guytest::~guytest()
{}

void guytest::TakeAStep()
{
    Play(gb::timerate, *this);
    CollisionEntity::TakeAStep();
}