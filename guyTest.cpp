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
#include <time.h>

float RandOne()
{
	if (rand()%2)
		return 1.f;
	else
		return -1.f;
}


guytest::guytest() : CollisionEntity(0), Playable(1), Animation(Game::GetTexture("nyancat"), 5.f, Game::GetAnimation("nyancat_fly")), pInfo(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_rainbow")), pStar(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_star"))
{
    Width=33.f; Height=20.f;
    SetSpeed(sf::Vector2f(3.f, 4.f));
    SetFriction(0.1f), SetBounce(0.f);
    SetDepth(-2);
    //Selon l'animation cela change
    SetOrigin(15.5f, 10.f);
    //SetOrigin(GetTextureRect().Width/2.f, GetTextureRect().Height/2.f);
    myMaxSpeed.x=5.f*4.f;
    //myAirFriction=sf::Vector2f(0.3f, 1.f);
	
	//pInfo.IncrSpeed=sf::Vector2f(0.f,-0.002f);
	pInfo.Life=60.f;
	//pInfo.Size=sf::Vector2f(3.f,3.f);
	pInfo.IncrSize=sf::Vector2f(-0.005f,-0.005f);
	pInfo.Origin=sf::Vector2f(2.f, 8.5f);
	//pInfo.Rotation=15.f;
	//pInfo.IncrRotation=10.f;
	pInfo.Blend=sf::BlendNone;
	
	pInfo.SetNumberOfAlphas(3);
	pInfo.SetAlpha(0, 255);
	pInfo.SetAlpha(1, 255);
	pInfo.SetAlpha(2, 0);
	/*pInfo.SetNumberOfColors(6);
	pInfo.SetColor(0, sf::Color::Red);
	pInfo.SetColor(1, sf::Color(254,98,54));
	pInfo.SetColor(2, sf::Color::Yellow);
	pInfo.SetColor(3, sf::Color::Green);
	pInfo.SetColor(4, sf::Color::Cyan);
	pInfo.SetColor(5, sf::Color::Blue);*/
	
	pStar.Life=10.f;
	pStar.Depth=-1;
	pStar.Origin=sf::Vector2f(3.5f, 3.5f);
	pStar.SetNumberOfAlphas(3);
	pStar.SetAlpha(0, 255);
	pStar.SetAlpha(1, 255);
	pStar.SetAlpha(2, 0);
	
	
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
        if (Game::GetKeyState("P1_MoveLeft").IsKeyPressed()) mySpeed.x-=0.75f*gb::timerate*4.f, useFriction=0;
        if (Game::GetKeyState("P1_MoveRight").IsKeyPressed()) mySpeed.x+=0.75f*gb::timerate*4.f, useFriction=0;
        if ((Game::GetKeyState("P1_Jump").IsKeyPressed())&&(CheckGround(1.f))) mySpeed.y=-5.f;// AddSound("Jump");
    }

	UpdateSoundList();
	
	float maxSpeed(max(static_cast<float>(abs(mySpeed.x)), static_cast<float>(abs(mySpeed.y)))*gb::timerate), tmpStep(1.f), tmpSpeed(maxSpeed);
    //Cette vitesse temporelle permet de gérer les collisions entre objets dynamiques
    myStepSpeed=mySpeed;
    //if (!isPositive(maxSpeed)) tmpStep*=-1.f;
    //std::cout<<"Max: "<<max(static_cast<float>(abs(5.f)), static_cast<float>(abs(12.f)))<<std::endl;
	
    while (tmpSpeed>0.0001f)
    {
		Particle::Create(GetPosition()+sf::Vector2f(tmpSpeed*gb::timerate*mySpeed.x/maxSpeed, tmpSpeed*gb::timerate*mySpeed.y/maxSpeed), pInfo, 5.f);
		tmpSpeed-=tmpStep;
    }

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

	//Particle::Create(GetPosition()-sf::Vector2f((Width/2.f-5.f)*GetScale().x, 0.f), pInfo, 5.f);
	//Particle::Create(GetPosition(), pInfo, 5.f);
	Particle::Create(GetPosition() + sf::Vector2f((rand()%150+15.f)*RandOne(), (rand()%150+15.f)*RandOne()), pStar, 7.f);
}
