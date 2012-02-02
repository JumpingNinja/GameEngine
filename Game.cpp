//
//  Game.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Game.h"
#include "Entity.h"
#include "MyClass.h"
#include <iostream>

//Initialization des membres statiques
Game::GameState Game::myGameState = Uninitialized;
sf::RenderWindow Game::myMainWindow;
SplashScreen Game::mySplash;

void Game::Start(void)
{
    if(myGameState != Uninitialized)
        return;
    
    myMainWindow.Create(sf::VideoMode(1024,768,32),"Pang!");
    myMainWindow.SetFramerateLimit(15.f);
    
    //Show a splashscreen usefull for loading ressources (go edit SplashScreen.cpp)
    myGameState=ShowingSplash;
    
    
    Entity *p;
    
    for (int i=0; i<200; i++)
    {
            p=new MyClass(-10);

        if (i<30 && i>=20) p->SetDepth(-2);
        p->SetDepth(i);
    }
    
    sf::Clock clock; unsigned int counter(0);
    while(!IsExiting())
    {
        counter++;
        GameLoop();
        if (clock.GetElapsedTime().AsSeconds()>=1.0f)
        std::cout<<"Frametime: "<<counter/clock.GetElapsedTime().AsSeconds()<<std::endl, counter=0, clock.Restart();
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
            //Step
            
            //drawing
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
