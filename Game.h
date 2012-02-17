//
//  Game.h
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#pragma once
#include <map>
#include <list>

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
	static float timerate;
	
	///@brief lance le jeu
    static void Start();
	/**
	 @brief Donne accès à une texture
	 @param key clé de la texture
	 @return la texture correspondante
	 **/
    static const sf::Texture& GetTexture(const std::string& key);
	/**
	 @brief Donne accès à une animation (vector de ractangles)
	 @param key clé de l'animation
	 @return l'animation correspondante
	 **/
    static const std::vector<sf::IntRect>& GetAnimation(const std::string &key);
	/**
	 @brief Donne accès à un son
	 @param key clé du son
	 @return le son correspondante
	 **/
    static const sf::SoundBuffer& GetSoundBuffer(const std::string &key);
	/**
	 @brief Donne accès à une musique
	 @param key clé de la musique
	 @return la musique correspondante
	 **/
    static const sf::Music& GetMusic(const std::string &key);
	/**
	 @brief Donne la longueur de la scène
	 @return Longueur de la scène
	 **/
    static float GetWidth();
	/**
	 @brief Donne la largeur de la scène
	 @return Largeur de la scène
	 **/
    static float GetHeight();
	/**
	 @brief Donne la vue de la scène
	 @return vue de la scène
	 **/
    static const sf::View& GetView();
    /** @brief Renvoi les coordonnées de la souris dans la scène
		@return vecteur avec la position de la souris en tenant compte de la vue
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
	///@brief Entités que suit la vue
    static std::list<Entity*> myFollow;

private:
    static bool IsExiting();
	///@brief Loop principal du jeu
    static void GameLoop();
	
	///@brief met à jour quelques paramètres du jeu comme la vue (je me sens pas très orginel pour les noms)
	static void GlobalStep();

	///@brief Donne le centre du polygone formé par la liste de myFollow
	///@return vecteur qui donne le centre de la vue
    static sf::Vector2f ComputeCenter();

    enum GameState { Uninitialized, ShowingSplash, Paused,
        ShowingMenu, Playing, Exiting };

    static GameState myGameState;
    static sf::RenderWindow myMainWindow;
    static ResManager myResManager;
    static sf::View myView;
    static Background *myBack;
    static float myWidth, myHeight, timerateTo, m_spd[12];
    static unsigned int myWinWidth, myWinHeight;
    static InputStatus *InputStatusError;

    /** @brief Associe une action (chaîne de caractères) à une touche.
    *
    * @param Action Nom de l'action
    * @param Key Touche associée
    **/
	static void AddKeyBinding(const std::string &Action, gb::Key Key);

	static ParticleInfo pInfo;

};

