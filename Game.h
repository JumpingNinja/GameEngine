//
//  Game.h
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#pragma once
#include <map>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "SplashScreen.h"
#include "Background.h"
#include "KeyStatus.h"
#include "Game.h"
#include "Entity.h"

class Entity;
class Background;

const unsigned int fpsLimit(30);

class Game
{
    static SplashScreen mySplash;
public:
    static void Start();
    static const sf::Texture& GetTexture(const std::string& key);
    static const std::vector<sf::IntRect>& GetAnimation(const std::string &key);
    static float GetWidth();
    static float GetHeight();
    static const sf::View& GetView();

    static std::map<std::string, sf::Keyboard::Key> Bindings;
    static const KeyStatus& GetKeyState(const std::string &Action);

private:
    static bool IsExiting();
    static void GameLoop();

    enum GameState { Uninitialized, ShowingSplash, Paused,
        ShowingMenu, Playing, Exiting };

    static GameState myGameState;
    static sf::RenderWindow myMainWindow;
    static TxManager myTxManager;
    static sf::View myView;
    static Entity *myFollow;
    static Background *myBack;
    static float myWidth, myHeight;
    static unsigned int myWinWidth, myWinHeight;
};

