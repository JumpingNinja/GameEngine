//
//  Animation.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Animation.h"
#include "Game.h"
#include <cmath>

Animation::Animation(const sf::Texture& texture, float interval, const std::vector<sf::IntRect>& Rects) : myTexture(texture), myRects(&Rects), myInterval(interval), myFrame(0.f), myNeedUpdate(1), myLastframe(0)
{
}

void Animation::Play(float timerate, sf::Sprite &sprite)
{
    if (myInterval>0.f)
    myFrame+=timerate/myInterval;
    
    if (myFrame>=static_cast<float>(myRects->size()))
        myFrame=0.f;
    
    //Pas besoin de floorf car le cast fait une troncature
    if (myLastframe!=static_cast<unsigned short>(myFrame))
        myLastframe=static_cast<unsigned short>(myFrame), myNeedUpdate=1;
    
    if (myNeedUpdate)
    {
        sprite.SetTexture(myTexture, 1);
        sprite.SetTextureRect((*myRects)[myLastframe]);
        myNeedUpdate=0;
    }
    
}

void Animation::SetFrame(float frame)
{
    myFrame=frame;
}

float Animation::GetFrame() const
{
    return myFrame;
}

void Animation::SetInterval(float interval)
{
	myInterval=interval;
}

float Animation::GetInterval() const
{
	return myInterval;
}

void Animation::SetRects(const std::vector<sf::IntRect> &Rects)
{
    myRects=&Rects;
    //Non implémentable avec des réferences :S
}
