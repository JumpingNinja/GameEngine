//
//  Background.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 07/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Background.h"
#include "Game.h"
#include <iostream>

Background::Background(float Width, float Height, short Depth) :  Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f(Width/Game::GetWidth(), Height/Game::GetHeight()))
{
    Create(Width, Height);
    Clear(sf::Color::Black);
    Display();
}

Background::Background(const sf::Texture& copyTexture, short Depth) : Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f((Game::GetWidth()-copyTexture.GetWidth())/(Game::GetWidth()-Game::GetView().GetSize().x),(Game::GetHeight()-copyTexture.GetHeight())/(Game::GetHeight()-Game::GetView().GetSize().y)))
{
    SetOrigin(sf::Vector2f());
    SetTexture(copyTexture);

}

Background::Background(short Depth) :  Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f(1.f, 1.f))
{}


Background::~Background()
{}

void Background::UpdatePosition()
{    
    SetPosition((Game::GetView().GetCenter().x-Game::GetView().GetSize().x/2.f)*(myFactor.x), (Game::GetView().GetCenter().y-Game::GetView().GetSize().y/2.f)*(myFactor.y));
}