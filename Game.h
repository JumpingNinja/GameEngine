//
//  Game.h
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SplashScreen.h"

const unsigned int fpsLimit(30);

class Game
{
    static SplashScreen mySplash;
public:
    static void Start();
    
private:
    static bool IsExiting();
    static void GameLoop();
    
    enum GameState { Uninitialized, ShowingSplash, Paused, 
        ShowingMenu, Playing, Exiting };
    
    static GameState myGameState;
    static sf::RenderWindow myMainWindow;
    static TxManager mytxManager;
};

