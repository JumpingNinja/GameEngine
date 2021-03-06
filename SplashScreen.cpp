//
//  SplashScreen.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "SplashScreen.h"
#include "ResourcePath.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    renderWindow.Clear();
	renderWindow.Draw(mySprBack);
	renderWindow.Display();
    
	sf::Event event;
	//on sort pour faire plus vite
	while(false)
	{
		while(renderWindow.PollEvent(event))
		{
			if(event.Type == sf::Event::KeyPressed 
               || event.Type == sf::Event::MouseButtonPressed
               || event.Type == sf::Event::Closed 
			   || event.Type == sf::Event::JoystickButtonPressed)
			{
				return;
			}
		}
	}
}


SplashScreen::SplashScreen() : myTxBack(), mySprBack()
{
    //Load the textures needed
    myTxBack.LoadFromFile(ResourcePath()+"img/SplashScreen.png");
    mySprBack.SetTexture(myTxBack);
}