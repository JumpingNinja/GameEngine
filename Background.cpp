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

Background::Background(float Width, float Height, short Depth) :  Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f(Width/Game::GetWidth(), Height/Game::GetHeight())), myTotal(sf::Vector2f()) //a  completer!
{
    Create(Width, Height);
    Clear(sf::Color::Black);
    Display();
}

Background::Background(const sf::Texture& copyTexture, short Depth) : Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f(copyTexture.GetWidth()/Game::GetWidth(), copyTexture.GetHeight()/Game::GetHeight())), myTotal(sf::Vector2f())
{
    /*Create(copyTexture.GetWidth(), copyTexture.GetHeight());
    //Clear(sf::Color(0,0,0,0));
    //sf::Sprite spr(copyTexture);
    sf::RenderTarget::Draw(spr);
    Display();*/
    SetOrigin(sf::Vector2f());
    SetTexture(copyTexture);
    //myFactor.x=(Game::GetWidth())/(copyTexture.GetWidth()-160.f);
    myFactor.x=(Game::GetWidth()-copyTexture.GetWidth())/(Game::GetWidth()-Game::GetView().GetSize().x);
    myFactor.y=(Game::GetHeight()-copyTexture.GetHeight())/(Game::GetHeight()-Game::GetView().GetSize().y);
    //myFactor.x=(Game::GetWidth()/(Game::GetWidth()-160.f))*(Game::GetWidth()-160.f)/(Game::GetWidth()-copyTexture.GetWidth());
    std::cout<<myFactor.x<<", "<<myFactor.y<<std::endl;
    //myFactor.y=copyTexture.GetHeight()/(Game::GetHeight());
    //myFactor.x=Game::GetWidth()/copyTexture.GetWidth();
}

Background::Background(short Depth) :  Entity::Entity(Depth), sf::RenderTexture(), myFactor(sf::Vector2f(1.f, 1.f))
{}


Background::~Background()
{}

void Background::UpdatePosition()
{    
    SetPosition((Game::GetView().GetCenter().x-Game::GetView().GetSize().x/2.f)*(myFactor.x), (Game::GetView().GetCenter().y-Game::GetView().GetSize().y/2.f)*(myFactor.y));
}