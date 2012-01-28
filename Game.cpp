//
//  Game.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Game.h"
#include "Entity.h"

//Initialization des membres statiques
Game::GameState Game::myGameState = Uninitialized;
sf::RenderWindow Game::myMainWindow;
SplashScreen Game::mySplash;

void Game::Start(void)
{
    if(myGameState != Uninitialized)
        return;
    
    myMainWindow.Create(sf::VideoMode(1024,768,32),"Pang!");
    myMainWindow.SetFramerateLimit(60.f);
    
    //Show a splashscreen usefull for loading ressources (go edit SplashScreen.cpp)
    myGameState=ShowingSplash;
    
    Entity *p;
    
    for (int i=0; i<100; i++)
    {
        p=new Entity(static_cast<short>(i%10));
        if (i<30 && i>=20)
            p->SetDepth(-2);
        //p->SetDepth(i);
    }
    
    while(!IsExiting())
    {
        GameLoop();
    }
    
    Entity::DestroyAll(); //à cause des new
    myMainWindow.Close();
}

bool Game::IsExiting()
{
    if(myGameState == Game::Exiting) 
        return true;
    else 
        return false;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    
    switch(myGameState)
    {
        case Game::Playing:
        {
            myMainWindow.Clear(sf::Color(55,0,0));
            Entity::DrawAll(myMainWindow);
            myMainWindow.Display();
            
            break;
        }
        
        case Game::ShowingSplash:
            mySplash.Show(myMainWindow);
            myGameState=Playing;
            break;
        default:
            break;
    }
    
    while(myMainWindow.PollEvent(currentEvent))
    {
        if(currentEvent.Type==sf::Event::Closed)
            myGameState=Game::Exiting;
        if (currentEvent.Type==sf::Event::KeyPressed && currentEvent.Key.Code==sf::Keyboard::Escape)
            myGameState=Game::Exiting;
        
    }
}
