//
//  guyTest.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "guyTest.h"
#include "Game.h"
#include <iostream>


guytest::guytest() : CollisionEntity(0), Playable(1), Animation(Game::GetTexture("player"), 5.f, Game::GetAnimation("player_walk"))
{
    Width=9.f; Height=17.f;
    SetSpeed(sf::Vector2f(3.f, 4.f));
    SetFriction(0.1f), SetBounce(0.f);
    SetDepth(-2);
    //Selon l'animation cela change
    SetOrigin(4.5f, 8.5f);
    //SetOrigin(GetTextureRect().Width/2.f, GetTextureRect().Height/2.f);
    myMaxSpeed.x=5.f;
    //myAirFriction=sf::Vector2f(0.3f, 1.f);
}
/*
guytest::guytest() : CollisionEntity(0), Animation(Game::GetTexture("ryu"), 6.f, Game::GetAnimation("ryu_walk"))
{
    Width=22; Height=31;
    SetSpeed(sf::Vector2f(20.f, 4.f));
    SetDepth(-2);
}
*/
guytest::~guytest()
{}

void guytest::TakeAStep(bool useFriction)
{
    if(IsControled())
    {
        // A terme les KeyStatus::map seront remplacé par des désignation plus claires : Bindings['P1MoveLeft'] par exemple
        if (Game::GetKeyState("P1_MoveLeft").IsKeyPressed()) mySpeed.x-=0.75f*gb::timerate, useFriction=0;
        if (Game::GetKeyState("P1_MoveRight").IsKeyPressed()) mySpeed.x+=0.75f*gb::timerate, useFriction=0;
        if ((Game::GetKeyState("P1_Jump").IsJustPressed())&&(CheckGround(1.f))) mySpeed.y=-5.f, AddSound("Jump");
    }

	UpdateSoundList();

    /*if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) mySpeed.x-=0.75f*gb::timerate, useFriction=0;
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) mySpeed.x+=0.75f*gb::timerate, useFriction=0;
    if ((sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))&&(CheckGround(1.f))) mySpeed.y=-5.f;*/
    //std::cout<<"useFriction:"<<useFriction<<std::endl;
    Play(gb::timerate, *this);
    SetOrigin(GetTextureRect().Width/2.f, GetTextureRect().Height/2.f);
    CollisionEntity::TakeAStep(1);
    //Il faut le faire dans la classe dérivée car cela est propre à l'objet (je pense) et il faut utiliser SetScale et non pas Scale
    if (mySpeed.x>=0.f)
        SetScale(1.f, 1.f);
    else
        SetScale(-1.f, 1.f);


}
