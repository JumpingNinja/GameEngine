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
#include <cmath>

float RandOne()
{
	if (rand()%2)
		return 1.f;
	else
		return -1.f;
}

float GetAngle(const sf::Vector2f &vec)
{
	float l(sqrt(vec.x*vec.x+vec.y*vec.y));
	return acosf(vec.x/l)*(180.f/3.14f);
}


//guytest::guytest() : CollisionEntity(0), Playable(1), Animation(Game::GetTexture("nyancat"), 5.f, Game::GetAnimation("nyancat_fly")), pInfo(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_rainbow")), pStar(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_star"))
guytest::guytest() : CollisionEntity(0), Playable(1), Animation(Game::GetTexture("ryu"), 5.f, Game::GetAnimation("ryu_walk")), pInfo(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_rainbow")), pStar(Game::GetTexture("nyancat"), Game::GetAnimation("nyancat_star")), partRot(0.f), m_spd(0.f), wallWalkTimer(0)
{
    //Width=33.f; Height=20.f;
    Width=19.f; Height=32.f;
    SetSpeed(sf::Vector2f(3.f, 4.f));
    SetFriction(0.1f), SetBounce(0.f);
    SetDepth(-2);
    //Selon l'animation cela change
    SetOrigin(15.5f, 10.f);
    //SetOrigin(GetTextureRect().Width/2.f, GetTextureRect().Height/2.f);
    myMaxSpeed.x=5.f;
	myMass=10.f;
    //myMaxSpeed.y=10.f;
    //myAirFriction=sf::Vector2f(0.3f, 1.f);

	//pInfo.IncrSpeed=sf::Vector2f(0.f,-0.002f);
	pInfo.Life=60.f;
	//pInfo.Size=sf::Vector2f(3.f,3.f);
	//pInfo.IncrSize=sf::Vector2f(0,-0.005f);
	pInfo.IncrSize=sf::Vector2f(0.f,-0.0005f);
	pInfo.Origin=sf::Vector2f(1.f, 8.5f);
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

	wallWalkFactor = 3;
	wallWalking = 0;
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
	int tmpSurroundings = CheckSurroundings(sf::Vector2f(-1.f*max(1.f, abs(mySpeed.x)), 0), 1);
    if(IsControled())
    {
    	if(CheckGround(1.f))
    	{
    		wallWalking = 0;
    		wallWalkTimer = wallWalkFactor*abs(mySpeed.x);

			if (Game::GetKeyState("P1_MoveLeft").IsKeyPressed()) MoveLeft(), useFriction=0;
			if (Game::GetKeyState("P1_MoveRight").IsKeyPressed()) MoveRight(), useFriction=0;
			if (Game::GetKeyState("P1_Jump").IsJustPressed() && (CheckGround(1.f) || CheckSurroundings(sf::Vector2f(1.f, 0), 1))) Jump(), PlaySound("Jump");

			if(Game::UseJoysticks)
			{
				if ((Game::GetKeyState("JoyJump").IsJustPressed())) Jump(), PlaySound("Jump");
				if(abs(Game::GetAxisState("MoveAxis")) > 1) MoveAxis(Game::GetAxisState("MoveAxis")); //useFriction=0;
			}
        }
		else
		{
			if (Game::GetKeyState("P1_MoveLeft").IsKeyPressed()) AirControlLeft(), useFriction=0;
			if (Game::GetKeyState("P1_MoveRight").IsKeyPressed()) AirControlRight(), useFriction=0;

			if(abs(Game::GetAxisState("MoveAxis")) > 1) AirControlAxis(Game::GetAxisState("MoveAxis"));
			if ((Game::GetKeyState("JoyJump").IsJustPressed()) && tmpSurroundings )
				WallJump(tmpSurroundings);
				//std::cout << "Wall Jump with :" << tmpSurroundings << " Speed : " << mySpeed.x << " " << mySpeed.y << std::endl;

			if(!Game::GetKeyState("WallWalk").IsKeyPressed() || (wallWalking)&&!tmpSurroundings)
				wallWalkTimer = 0;
        }
		if (tmpSurroundings && Game::GetKeyState("WallWalk").IsKeyPressed() && wallWalkTimer)
			AddSpeed(sf::Vector2f(0, -wallWalkTimer*0.1f)),
			wallWalkTimer--, wallWalking = 1;

		if (Game::GetKeyState("DoStuff").IsKeyPressed()) Particle::Create(Game::GetMousePosition(), pInfo, 7.f);
		if (Game::GetKeyState("DoStuff2").IsKeyPressed()) std::cout << "Trop fort, t'as clique sur le bouton droit de la souris..." << std::endl;
    }

	int state;

	if(CheckGround(2.f))
	{
		if (abs(mySpeed.x)<0.5f && abs(mySpeed.y)<0.1f)
			SetRects(Game::GetAnimation("ryu_stand")), state=1;
		else
			SetRects(Game::GetAnimation("ryu_walk")), state=0;

	} else if(wallWalking && tmpSurroundings && Game::GetKeyState("WallWalk").IsKeyPressed() && wallWalkTimer) {
		SetRects(Game::GetAnimation("ryu_stand")), state=0;
	} else {
		SetRects(Game::GetAnimation("ryu_jump")), state=2;
	}

//	if(CheckSurroundings(sf::Vector2f(1.f, 0), 1))
//		std::cout << "Ceci est un mur..." << std::endl;

	if (state==0)
		Play(Game::timerate*abs(mySpeed.x)/myMaxSpeed.x, *this);
	else
		Play(Game::timerate, *this);

	float maxSpeed(max(static_cast<float>(abs(mySpeed.x)), static_cast<float>(abs(mySpeed.y)))*Game::timerate), tmpStep(1.f), tmpSpeed(maxSpeed);
    //Cette vitesse temporelle permet de gérer les collisions entre objets dynamiques
    myStepSpeed=mySpeed;
    //if (!isPositive(maxSpeed)) tmpStep*=-1.f;
    //std::cout<<"Max: "<<max(static_cast<float>(abs(5.f)), static_cast<float>(abs(12.f)))<<std::endl;

    while (tmpSpeed>0.0001f)
    {
		sf::Vector2f v(mySpeed);
		partRot=GetAngle(v);
		wobble(pInfo.Rotation, partRot, 0.1f, 0.6f, m_spd);
		//pInfo.Rotation=GetAngle(v);
		Particle::Create(GetPosition()+sf::Vector2f(tmpSpeed*Game::timerate*mySpeed.x/maxSpeed, tmpSpeed*Game::timerate*mySpeed.y/maxSpeed), pInfo, 5.f);
		tmpSpeed-=tmpStep;
    }


    CollisionEntity::TakeAStep(1);

	// Tourne le personnage vers sa direction
    SetOrigin(GetTextureRect().Width/2.f, GetTextureRect().Height/2.f);
    if (mySpeed.x>0.f)
        SetScale(1.f, 1.f);
    else if(mySpeed.x<0.f)
        SetScale(-1.f, 1.f);

	UpdateSoundList();

	//Particle::Create(GetPosition()-sf::Vector2f((Width/2.f-5.f)*GetScale().x, 0.f), pInfo, 5.f);
	//Particle::Create(GetPosition(), pInfo, 5.f);
	Particle::Create(GetPosition() + sf::Vector2f((rand()%150+15.f)*RandOne(), (rand()%150+15.f)*RandOne()), pStar, 7.f);
}
