//
//  Game.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Game.h"
#include "Entity.h"
#include "CollisionEntity.h"
#include "guyTest.h"
#include <iostream>

//Initialization des membres statiques*
std::map<std::string, gb::Key> Game::Bindings;

Game::GameState Game::myGameState = Uninitialized;
sf::RenderWindow Game::myMainWindow;
SplashScreen Game::mySplash;
ResManager Game::myResManager;
sf::View Game::myView;
std::list<Entity*> Game::myFollow;
Background* Game::myBack(NULL);
float Game::myWidth(320.f*5.f), Game::myHeight(200.f*4.f), Game::timerate(1.f), Game::timerateTo(1.f), Game::m_spd[12]={0.f};
unsigned int Game::myWinWidth(640), Game::myWinHeight(400);
bool Game::UseJoysticks = 1;

InputStatus* Game::InputStatusError(NULL);


void Game::Start(void)
{
    if(myGameState != Uninitialized)
        return;

	//Clé nulle pour gérer les touches non reconues
	InputStatusError=new InputStatus(gb::KeyCount);

    // Préparation de la gestion des inputs
    for(int keyLoop = gb::A; keyLoop != gb::LastKeyboardKey; keyLoop++)
    {
        new KeyStatus(static_cast<sf::Keyboard::Key>(keyLoop));
    }
    for(int keyLoop = gb::LastKeyboardKey + 1; keyLoop != gb::LastMouseButton; keyLoop++)
    {
        new MouseStatus(static_cast<sf::Mouse::Button>(keyLoop - gb::LastKeyboardKey - 1));
    }

    Game::UseJoysticks = 1; // Doit être récupéré d'un fichier de configuration

	sf::Joystick::Update();
	for(int nbJoysticks = 0;  nbJoysticks < 8;  nbJoysticks++)
	{
		std::cout << "Joystick " << nbJoysticks << std::endl;
		if (sf::Joystick::IsConnected(nbJoysticks))
		{
			unsigned int buttons = min((int) sf::Joystick::GetButtonCount(nbJoysticks), 32);
			for(unsigned int nbButtons = 0; nbButtons < buttons; nbButtons++)
			{
				std::cout<<"Nb Joys: "<<nbJoysticks<<" nbButton: "<<nbButtons<<std::endl;
				new JoyButtonStatus(nbJoysticks*32 + nbButtons);
			}
			for(unsigned int Axis = sf::Joystick::X; Axis <= sf::Joystick::PovY; Axis++)
			{
				if (sf::Joystick::HasAxis(nbJoysticks,static_cast<sf::Joystick::Axis>(Axis)))
					std::cout << "Added Axis " << Axis << std::endl,
					new JoystickAxis(nbJoysticks, static_cast<sf::Joystick::Axis>(Axis));
			}
		} else {
			if(nbJoysticks <= 0) Game::UseJoysticks = 0; // Désactive la prise en compte des joysticks si aucun connecté
			break;
		}
	}

    // Quelques binds (à terme : fichier de configuration)

	AddKeyBinding("Exit", gb::Escape);
	AddKeyBinding("Slow", gb::E);
	AddKeyBinding("P1_MoveLeft", gb::Q);
	AddKeyBinding("P1_MoveRight", gb::D);
	AddKeyBinding("P1_Jump", gb::Space);
	AddKeyBinding("DoStuff", gb::MouseButton1);
	AddKeyBinding("DoStuff2", gb::MouseButton2);

	if(Game::UseJoysticks == 1)
	{
		AddKeyBinding("DoStuff3", gb::Joy0_17);
		AddKeyBinding("DoStuff4", gb::Joy0_18);
		AddKeyBinding("DoStuff5", gb::Joy0_19);
		AddKeyBinding("DoStuff6", gb::Joy0_20);
		AddKeyBinding("DoStuff7", gb::Joy1_1);
		AddKeyBinding("DoStuff8", gb::Joy1_2);
		AddKeyBinding("DoStuff9", gb::Joy1_3);
		AddKeyBinding("SlowDown", gb::Joy1_4);
		AddKeyBinding("DoStuff11", gb::Joy3_1);
		AddKeyBinding("DoStuff12", gb::Joy3_2);
		AddKeyBinding("DoStuff13", gb::Joy3_3);
		AddKeyBinding("DoStuff14", gb::Joy3_4);

		AddKeyBinding("MoveAxis", gb::Joy1_X);
	}

    myMainWindow.Create(sf::VideoMode(myWinWidth , myWinHeight,32),"Pang!");
    //myMainWindow.SetFramerateLimit(60);
    myMainWindow.EnableVerticalSync(1);
	// Ignore la répétition des inputs par l'OS, pourrait être activé dans les menus...
	myMainWindow.EnableKeyRepeat(1);

    //Show a splashscreen usefull for loading ressources (go edit SplashScreen.cpp)
    myGameState=ShowingSplash;
    //Ceci se fait normalement dans ScreenSplash::Show()
    myResManager.LoadResources();

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
	p->SetBounce(20.f);
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
    myFollow.push_back(new guytest);
    myFollow.front()->SetPosition(300.f, 50.f);




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
    //Game::timerate=0.25f;

    //sf::Clock clock; unsigned int counter(0);
    while(!IsExiting())
    {
        //counter++;
        GameLoop();
        //if (clock.GetElapsedTime().AsSeconds()>=1.0f)
        //std::cout<<"Frametime: "<<1.f/clock.GetElapsedTime().AsSeconds()<<std::endl, counter=0, clock.Restart();
    }

    Entity::DestroyAll(); //à cause des new
    InputStatus::DestroyAll();
    JoystickAxis::DestroyAll();

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
	// Gestion des Events
    sf::Event currentEvent;

    while(myMainWindow.PollEvent(currentEvent))
    {
        if(currentEvent.Type==sf::Event::Closed)
            myGameState=Game::Exiting;
    }

	KeyStatus::UpdateAll();
	MouseStatus::UpdateAll();
	JoyButtonStatus::UpdateAll();


    if (Game::GetKeyState("Exit").IsJustPressed())
        myGameState=Game::Exiting;
    if ((Game::GetKeyState("Slow").IsJustPressed())||(Game::GetKeyState("SlowDown").IsJustPressed()))
    {
        if (Game::timerateTo>0.25f)
            Game::timerateTo=0.25f;
        else
            Game::timerateTo=1.f;
    }

	Sound::UpdateAll(Game::timerate);

    switch(myGameState)
    {
        case Game::Playing:
        {

            myMainWindow.SetView(myView);
            //Step
            CollisionEntity::Step();
			Particle::Step(Game::timerate);
            //sf::Vector2f addPos;
            //addPos.x=(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)-sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))*10.f;
            //addPos.y=(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)-sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))*4.f;
            //myView.SetCenter(myView.GetCenter()+addPos);

			Game::GlobalStep();

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
}

const sf::Texture& Game::GetTexture(const std::string& key)
{
    return myResManager.GetTexture(key);
}

const std::vector<sf::IntRect>& Game::GetAnimation(const std::string &key)
{
    return myResManager.GetAnimation(key);
}

const sf::SoundBuffer& Game::GetSoundBuffer(const std::string& key)
{
    return myResManager.GetSoundBuffer(key);
}

const sf::Music& Game::GetMusic(const std::string& key)
{
    return myResManager.GetMusic(key);
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

const InputStatus& Game::GetKeyState(const std::string &Action)
{
	// Vérifier que Game::Bindings[Action] existe réélement avant ? Trop cher ou pas ?
	// (Evite le plantage si on appelle une action qui n'existe pas)
	if (Game::Bindings[Action] < gb::LastKeyboardKey)
		return *KeyStatus::map[static_cast<sf::Keyboard::Key>(Game::Bindings[Action])];
	else if (Game::Bindings[Action] < gb::LastMouseButton)
		return *MouseStatus::map[static_cast<sf::Mouse::Button>(Game::Bindings[Action] - gb::LastKeyboardKey - 1)];
	else if (Game::Bindings[Action] < gb::LastJoystickButton)
		return *JoyButtonStatus::map[static_cast<unsigned int>(Game::Bindings[Action] - gb::LastMouseButton - 1)];
	else
		return *Game::InputStatusError;

}

float Game::GetAxisState(const std::string &Action)
{
	// Vérifier que Game::Bindings[Action] existe réélement avant ? Trop cher ou pas ?
	// (Evite le plantage si on appelle une action qui n'existe pas)
	return JoystickAxis::map[static_cast<gb::Key>(Game::Bindings[Action])]->GetPosition();
}

void Game::AddKeyBinding(std::string const &Action, gb::Key Key)
{
	// Vérifie que le boutton du Joystick existe réélement, ou qu'on accède à un autre champ
	if (((Key < gb::LastMouseButton) || (Key > gb::LastJoystickButton) || (JoyButtonStatus::map.count(Key - gb::LastMouseButton - 1) == 1)) && ((Key < gb::LastJoystickButton) || (JoystickAxis::map.count(Key) == 1) ))
		Game::Bindings.insert(std::pair<std::string, gb::Key>(Action, Key));
}

sf::Vector2f Game::ComputeCenter()
{
	std::list<std::pair<float, sf::Vector2f> > List;
	std::list<Entity*>::iterator it;
	for(it = Game::myFollow.begin(); it != Game::myFollow.end(); it++)
	{
		List.push_back(std::pair<float, sf::Vector2f>(1, (*it)->GetPosition()));
	}
	while(List.size() > 1)
	{
		std::pair<float, sf::Vector2f> temp1 = List.front();
		List.pop_front();
		std::pair<float, sf::Vector2f> temp2 = List.front();
		List.pop_front();
		temp1 = std::pair<float, sf::Vector2f>(temp1.first + temp2.first, (temp1.first*temp1.second + temp2.first*temp2.second)/(temp1.first + temp2.first));
		List.push_back(temp1);
	}
	return List.front().second;
}

void Game::GlobalStep()
{
	// Place le centre de l'écoute sur le joueur, et un peu derrière la scène pour éviter des effets bizarres.
	sf::Listener::SetPosition(myFollow.front()->GetPosition().x, myFollow.front()->GetPosition().y, -5);
	
	myView.SetCenter(myFollow.front()->GetPosition());
	
	myView.SetCenter(max(myView.GetSize().x/2.f, myView.GetCenter().x), max(myView.GetSize().y/2.f, myView.GetCenter().y));
	myView.SetCenter(min(myWidth - myView.GetSize().x/2.f, myView.GetCenter().x), min(myHeight - myView.GetSize().y/2.f, myView.GetCenter().y));
	
	wobble(timerate, timerateTo, 0.5f, 0.5f, m_spd[0]);
	//à implémenter un peux mieux avec un accesseur sur Game::timerate et un set sur Game::timerate_to
}
