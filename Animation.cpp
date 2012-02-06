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

Animation::Animation(const sf::Texture& texture, const float &interval, const std::vector<sf::IntRect>& Rects) : myTexture(texture), myRects(Rects), myInterval(interval), myFrame(0.f)
{
}

void Animation::Play(const float &timerate, sf::Sprite &sprite)
{
    myFrame+=timerate/myInterval;
    if (myFrame>=static_cast<float>(myRects.size()))
        myFrame=0.f;
    
    sprite.SetTexture(myTexture, 1);
    sprite.SetTextureRect(myRects[static_cast<unsigned int>(floorf(myFrame))]);
}

void Animation::SetFrame(const float &frame)
{
    myFrame=frame;
}

float Animation::GetFrame() const
{
    return myFrame;
}