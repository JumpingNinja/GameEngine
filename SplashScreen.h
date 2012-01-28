//
//  SplashScreen.h
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include <SFML/Graphics.hpp>

class SplashScreen
{
    sf::Texture myTxBack;
    sf::Sprite mySprBack;
public:
    SplashScreen();
    void Show(sf::RenderWindow& window);
};