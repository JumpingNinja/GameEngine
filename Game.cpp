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
#include "CollisionEntity.h"
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
    myMainWindow.SetFramerateLimit(60.f);
    
    //Show a splashscreen usefull for loading ressources (go edit SplashScreen.cpp)
    myGameState=ShowingSplash;
    
    //fake texture
    sf::Texture tx;
    
    //Manually reate some walls
    CollisionEntity* p;
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 20.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 20, 700));
    p->Width=20.f, p->Height=700.f;
    
    p=new CollisionEntity(1);
    p->SetPosition(1014.f, 20.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 20, 700));
    p->Width=20.f, p->Height=700.f;
    
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 720.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 1024, 20));
    p->Width=1024.f, p->Height=20.f;
    
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 10.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 1024, 20));
    p->Width=1024.f, p->Height=20.f;

    
    for (int i=0; i<10; i++)
    {
        p=new CollisionEntity(0);
        p->SetDepth(-1);
        p->SetPosition(300.f+i*35.f, 150.f);
        p->SetTexture(tx);
        p->SetTextureRect(sf::IntRect(0, 0, 10, 10));
        p->SetColor(sf::Color::Green);
        p->Width=10.f, p->Height=10.f;
        
        //Quelques paramètres por un objet qui ne s'arrete jamais de bouger ^^
        p->SetFriction(0.2f);
        p->SetBounce(0.90f);
        p->SetSpeed(sf::Vector2f(5.f, 3.f));
        if (i==0)
            p->SetSpeed(sf::Vector2f(8.f,-3.f)), p->SetColor(sf::Color::Blue), p->SetMass(3.f);
        if (i==1)
            p->SetSpeed(sf::Vector2f(-8.f, -3.f));
    }
    
    
    //On ralentie le temps
    //gb::timerate=0.2f;
    
    //sf::Clock clock; unsigned int counter(0);
    while(!IsExiting())
    {
        //counter++;
        GameLoop();
        //if (clock.GetElapsedTime().AsSeconds()>=1.0f)
        //std::cout<<"Frametime: "<<1.f/clock.GetElapsedTime().AsSeconds()<<std::endl, counter=0, clock.Restart();
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
            CollisionEntity::Step();
            
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
