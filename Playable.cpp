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

Playable::Playable() : myControled(1), myGroundControl(0.75f), myAirControl(0.5f)
{}

Playable::Playable(bool aControled) : myControled(aControled), myGroundControl(0.75f), myAirControl(0.5f)
{}

Playable::~Playable()
{}

void Playable::Jump()
{
    AddSpeed(sf::Vector2f(0, -5.f));
}

void Playable::WallJump(short int factor)
{
    SetSpeed(sf::Vector2f(4*factor, max(-6.f, mySpeed.y - 5.f)));
}

void Playable::MoveLeft()
{
    AddSpeed(sf::Vector2f(-myGroundControl*Game::timerate, 0));
}

void Playable::MoveRight()
{
    AddSpeed(sf::Vector2f(myGroundControl*Game::timerate, 0));
}

void Playable::MoveAxis(float Axis)
{
	AddSpeed(sf::Vector2f(Axis*0.01f*myGroundControl*Game::timerate, 0.f));
}

void Playable::AirControlLeft()
{
    AddSpeed(sf::Vector2f(-myAirControl*Game::timerate, 0));
}

void Playable::AirControlRight()
{
    AddSpeed(sf::Vector2f(myAirControl*Game::timerate, 0));
}

void Playable::AirControlAxis(float Axis)
{
	AddSpeed(sf::Vector2f(Axis*0.01f*myAirControl*Game::timerate, 0.f));
}
