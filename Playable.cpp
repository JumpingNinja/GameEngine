//
//  Playable.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 12/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Playable.h"
#include "Game.h"

bool Playable::IsControled() const
{ return myControled; }

void Playable::SetControled(bool aControled)
{ myControled = aControled; }

Playable::Playable() : myControled(1)
{}

Playable::Playable(bool aControled) : myControled(aControled)
{}

Playable::~Playable()
{}

void Playable::Jump()
{
    AddSpeed(sf::Vector2f(0, -5.f));
}

void Playable::Jump(short int factor)
{
    AddSpeed(sf::Vector2f(3*factor, -5.f*abs(factor)));
}

void Playable::MoveLeft()
{
    AddSpeed(sf::Vector2f(-0.75f*Game::timerate, 0));
}

void Playable::MoveRight()
{
    AddSpeed(sf::Vector2f(0.75f*Game::timerate, 0));
}

void Playable::AirControlLeft()
{
    AddSpeed(sf::Vector2f(-0.50f*Game::timerate, 0));
}

void Playable::AirControlRight()
{
    AddSpeed(sf::Vector2f(0.50f*Game::timerate, 0));
}
