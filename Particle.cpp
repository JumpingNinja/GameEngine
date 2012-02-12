//
//  Particle.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 08/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Particle.h"
#include <iostream>
#include <cmath>

std::list<Particle*> Particle::list;
std::list<Particle*>::iterator Particle::it;


ParticleInfo::ParticleInfo(const sf::Texture &aTexture, const std::vector<sf::IntRect>& aRects) : Speed(sf::Vector2f()), IncrSpeed(sf::Vector2f()), Gravity(sf::Vector2f()), Size(sf::Vector2f(1.f,1.f)), IncrSize(sf::Vector2f()), Friction(sf::Vector2f()), Origin(sf::Vector2f()), Life(100.f), Rotation(0.f), IncrRotation(0.f), CanOut(0), Depth(0), Alpha(std::vector<sf::Uint8>(1)), Color(std::vector<sf::Color>(1)), Texture(aTexture), Rects(aRects), Blend(sf::BlendNone)
{
	Alpha[0]=255;
	Color[0]=sf::Color::White;
}

ParticleInfo::~ParticleInfo()
{
	Alpha.clear();
	Color.clear();
}

void ParticleInfo::SetAlpha(unsigned int i, sf::Uint8 aAlpha)
{
	Alpha[i]=aAlpha;
}

void ParticleInfo::SetColor(unsigned int i, sf::Color aColor)
{
	Color[i]=aColor;
}

void ParticleInfo::SetNumberOfAlphas(unsigned int n)
{
	Alpha.resize(n);
}

void ParticleInfo::SetNumberOfColors(unsigned int n)
{
	Color.resize(n);
}


Particle::Particle(const ParticleInfo& Info, float Interval) : myInfo(Info), Entity(Info.Depth), mySize(Info.Size), mySpeed(Info.Speed), myLife(Info.Life), myCurrentColor(0.f), myCurrentAlpha(0.f), Animation(Info.Texture, Interval, Info.Rects)
{
	SetTexture(Info.Texture);
    list.push_back(this);
	SetAlpha(Info.Alpha[0]);
	SetColor(Info.Color[0]);
	SetOrigin(Info.Origin);
	SetRotation(Info.Rotation);
	
	myBlendMode=Info.Blend;

}

Particle::~Particle()
{
	std::list<Particle*>::iterator ite;
    for (ite=list.begin(); ite!=list.end(); ite++)
    {
        if ((*ite)==this)
            break;
    }
    
    if ((*ite)==this)
        list.erase(ite);
}

void Particle::TakeAStep(float timerate)
{
	
	myLife-=1.f*timerate;
    Move(mySpeed*timerate);
    mySpeed+=myInfo.Gravity*timerate;
    mySpeed+=myInfo.IncrSpeed*timerate;
    mySize+=myInfo.IncrSize*timerate;
    mySpeed.x*=(1.f-myInfo.Friction.x);
    mySpeed.y*=(1.f-myInfo.Friction.y);

	if (myLife<=0.f) myDestroy=1;
	
	Play(gb::timerate, *this);
	
	Rotate(myInfo.IncrRotation);
	
	SetScale(mySize);
	
	//On modifie la couleur
	if (myInfo.Color.size()>0)
	{
		myCurrentColor+=((myInfo.Color.size()-1)/myInfo.Life)*timerate;
		unsigned int lower(static_cast<unsigned int>(myCurrentColor));
		unsigned int upper(static_cast<unsigned int>(myCurrentColor+1.f)); //ceil
		sf::Color tmpColor;
		tmpColor.r=(myInfo.Color[upper].r-myInfo.Color[lower].r)*(myCurrentColor-lower)+myInfo.Color[lower].r;
		tmpColor.g=(myInfo.Color[upper].g-myInfo.Color[lower].g)*(myCurrentColor-lower)+myInfo.Color[lower].g;
		tmpColor.b=(myInfo.Color[upper].b-myInfo.Color[lower].b)*(myCurrentColor-lower)+myInfo.Color[lower].b;
		SetColor(tmpColor);
	}
		
	//On modifie le alpha
	if (myInfo.Alpha.size()>0)
	{
		myCurrentAlpha+=((myInfo.Alpha.size()-1)/myInfo.Life)*timerate;
		unsigned int lower(static_cast<unsigned int>(myCurrentAlpha));
		unsigned int upper(static_cast<unsigned int>(myCurrentAlpha+1.f)); //ceil
		SetAlpha((myInfo.Alpha[upper]-myInfo.Alpha[lower])*(myCurrentAlpha-lower)+myInfo.Alpha[lower]);
	}
}

void Particle::Step(float timerate)
{
    for (it=list.begin(); it!=list.end(); it++)
	{
		(*it)->TakeAStep(timerate);

	}
        
}

void Particle::Create(sf::Vector2f const &pos, const ParticleInfo &Info, float Interval)
{
	Particle *p(new Particle(Info, Interval));
	p->SetPosition(pos);
}