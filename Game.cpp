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
#include "guyTest.h"
#include <iostream>
#include "Background.h"

//Initialization des membres statiques
Game::GameState Game::myGameState = Uninitialized;
sf::RenderWindow Game::myMainWindow;
SplashScreen Game::mySplash;
TxManager Game::myTxManager;
sf::View Game::myView;
Entity* Game::myFollow(NULL);
Background* Game::myBack(NULL);
float Game::myWidth(320.f*5.f), Game::myHeight(200.f*4.f);
unsigned int Game::myWinWidth(640), Game::myWinHeight(400);

void Game::Start(void)
{
    if(myGameState != Uninitialized)
        return;
    
    myMainWindow.Create(sf::VideoMode(myWinWidth , myWinHeight,32),"Pang!");
    //myMainWindow.SetFramerateLimit(60);
    myMainWindow.EnableVerticalSync(1);
    
    //Show a splashscreen usefull for loading ressources (go edit SplashScreen.cpp)
    myGameState=ShowingSplash;
    //Ceci se fait normalement dans ScreenSplash::Show()
    myTxManager.LoadResources();
    
    myView.SetSize(myMainWindow.GetWidth(), myMainWindow.GetHeight());
    myView.Zoom(1.f/2.f);
    
    
    myBack= new Background(Game::GetTexture("back"), 10);
    //myBack=new Background(300.f, 300.f, 10);
    //fake texture
    sf::Texture tx;
	
    //Manually reate some walls
	float friction = 0.5f;
	
    CollisionEntity* p;
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 20.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 20, 700));
    p->Width=20.f, p->Height=700.f;
	p->SetFriction(friction);
    
    p=new CollisionEntity(1);
    p->SetPosition(1014.f, 20.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 20, 700));
    p->Width=20.f, p->Height=700.f;
	p->SetFriction(friction);
    
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 720.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 1024, 20));
    p->Width=1024.f, p->Height=20.f;
	p->SetFriction(0.5f);
	
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 10.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 1024, 20));
    p->Width=1024.f, p->Height=20.f;
	p->SetFriction(friction);
	
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 700.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 100, 20));
    p->Width=100.f, p->Height=20.f;
	p->SetFriction(friction);
	
    p=new CollisionEntity(1);
    p->SetPosition(10.f, 680.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 50, 20));
    p->Width=50.f, p->Height=20.f;
	p->SetFriction(friction);
	
    p=new CollisionEntity(1);
    p->SetPosition(300.f, 640.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 50, 20));
    p->Width=50.f, p->Height=20.f;
	p->SetFriction(friction);
	
    p=new CollisionEntity(1);
    p->SetPosition(350.f, 660.f);
    p->SetTexture(tx);
    p->SetTextureRect(sf::IntRect(0, 0, 50, 20));
    p->Width=50.f, p->Height=20.f;
	p->SetFriction(friction);

	/*guytest *pg;
    pg=new guytest;
    pg->SetPosition(100.f, 45.f);
	guytest *pg2;
    pg2=new guytest;
    pg2->SetPosition(200.f, 45.f);*/
    myFollow=new guytest;
    myFollow->SetPosition(300.f, 50.f);
    
    
     
    
    /*for (int i=0; i<30; i++)
    {
        p=new CollisionEntity(0);
        p->SetDepth(-1);
        p->SetPosition(300.f+i*11.f, 150.f);
        p->SetTexture(tx);
        p->SetTextureRect(sf::IntRect(0, 0, 10, 10));
        p->SetColor(sf::Color::Green);
        p->Width=10.f, p->Height=10.f;
        
        //Quelques paramètres por un objet qui ne s'arrete jamais de bouger ^^
        p->SetFriction(0.0f), p->SetBounce(1.0f);
        p->SetSpeed(sf::Vector2f(5.f, -3.f));
        if (i==0)
            p->SetSpeed(sf::Vector2f(18.f,-3.f)), p->SetColor(sf::Color::Blue), p->SetMass(2.f), p->SetDepth(-2);
        if (i==1)
            p->SetSpeed(sf::Vector2f(-18.f, -3.f));
    }*/
     
    
    
    //On ralentie le temps
    //gb::timerate=0.25f;
    
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
            myMainWindow.SetView(myView);
            //Step
            CollisionEntity::Step();
            sf::Vector2f addPos;
            addPos.x=(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)-sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))*10.f;
            addPos.y=(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)-sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))*4.f;
            //myView.SetCenter(myView.GetCenter()+addPos);
            myView.SetCenter(myFollow->GetPosition());
            myView.SetCenter(max(myView.GetSize().x/2.f, myView.GetCenter().x), max(myView.GetSize().y/2.f, myView.GetCenter().y));
            myView.SetCenter(min(myWidth - myView.GetSize().x/2.f, myView.GetCenter().x), min(myHeight - myView.GetSize().y/2.f, myView.GetCenter().y));
            
            wobble(gb::timerate, gb::timerate_to, 0.5f, 0.5f, gb::m_spdTR);
            //à implémenter un peux mieux avec un accesseur sur gb::timerate et un set sur gb::timerate_to
            
            myBack->UpdatePosition();
            
            //drawing
            myMainWindow.Clear();
            Entity::DrawAll(myMainWindow);
            
            //myMainWindow.Draw(*myBack);
            
            //myMainWindow.SetView(myView);
            myMainWindow.Display();
            
            break;
        }
        
        case Game::ShowingSplash:
            mySplash.Show(myMainWindow);
            //c'est la aussi que mySplash.Show() va faire normalement appel au chargement de resources pour afficher "Loading"
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
        if (currentEvent.Type==sf::Event::KeyReleased && currentEvent.Key.Code==sf::Keyboard::X)
        {
            if (gb::timerate_to>0.25f)
                gb::timerate_to=0.25f;
            else
                gb::timerate_to=1.f;
        }
        
    }
}

const sf::Texture& Game::GetTexture(const std::string& key)
{
    return myTxManager.GetTexture(key);
}
const std::vector<sf::IntRect>& Game::GetAnimation(const std::string &key)
{
    return myTxManager.GetAnimation(key);
}

float Game::GetWidth()
{
    return myWidth;
}
float Game::GetHeight()
{
    return myHeight;
}

const sf::View& Game::GetView()
{
    return myView;
}