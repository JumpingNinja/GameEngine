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

#include "Input.h"
#include "KeyStatus.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Game.h"
#include "Entity.h"
#include "Particle.h"

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
    static const sf::SoundBuffer& GetSoundBuffer(const std::string &key);
    static const sf::Music& GetMusic(const std::string &key);
    static float GetWidth();
    static float GetHeight();
    static const sf::View& GetView();
    /** @brief Renvoi les coordonnées de la souris dans la scène.
    *
    **/
    static inline sf::Vector2f GetMousePosition() { return myMainWindow.ConvertCoords(sf::Mouse::GetPosition(myMainWindow).x, sf::Mouse::GetPosition(myMainWindow).y); }

    /** @brief Contient les associations Action/Touche
    *
    * Associe une action (string) à une touche au sens large :
    * Touches du clavier, bouttons de la souris, des joystick,
    * ou axes de joystick.
    **/
    static std::map<std::string, gb::Key> Bindings;
	/** @brief Renvoi le status de la touche associée à l'action Action
    *
    * Unifie les demandes d'état des touches du clavier, ses bouttons de la souris et
    * des bouttons des Joysticks en une seule fonction simple.
    * @param Action Nom de l'action
    **/
    static const InputStatus& GetKeyState(const std::string &Action);
	/** @brief Renvoi la position de l'axe associé à l'action Action
    *
    * Renvoi un float compris entre -100 et 100.
    * Penser à tester un Threshold pour éviter les mouvements infimes involontaires.
    * @param Action Nom de l'action
    **/
    static float GetAxisState(const std::string &Action);
    /// @brief Détermine si les axes des Joysticks doivent être pris en compte
    static bool UseJoysticks;

private:
    static bool IsExiting();
    static void GameLoop();

    enum GameState { Uninitialized, ShowingSplash, Paused,
        ShowingMenu, Playing, Exiting };

    static GameState myGameState;
    static sf::RenderWindow myMainWindow;
    static ResManager myResManager;
    static sf::View myView;
    static Entity *myFollow;
    static Background *myBack;
    static float myWidth, myHeight;
    static unsigned int myWinWidth, myWinHeight;
    static InputStatus InputStatusError;
    /** @brief Associe une action (chaîne de caractères) à une touche.
    *
    * @param Action Nom de l'action
    * @param Key Touche associée
    **/
	static void AddKeyBinding(const std::string &Action, gb::Key Key);

	static ParticleInfo pInfo;

};

