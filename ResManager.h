//
//  ResManager.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

///@brief Gère les ressources et en permet l'accès

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class ResManager {
    std::map<std::string, sf::SoundBuffer*> mySoundBuffers;
    std::map<std::string, sf::SoundBuffer*>::iterator mySoundBuffersIt;

    std::map<std::string, sf::Music*> myMusics;
    std::map<std::string, sf::Music*>::iterator myMusicsIt;

    std::map<std::string, sf::Texture*> myTextures;
    std::map<std::string, sf::Texture*>::iterator myTexturesIt;

    std::map<std::string, std::vector<sf::IntRect> > myAnimations;
    std::map<std::string, std::vector<sf::IntRect> >::iterator myAnimationsIt;

    ///@brief Charge un SoundBuffer et l'ajoute au map si possible
    ///@param location Où se trouve le fichier
    ///@param key clé qui permet l'accès à la resource
    ///@return faux en cas d'erreur
    bool AddSoundBuffer(const std::string &location, const std::string& key);

    ///@brief Charge une Music et l'ajoute au map si possible
    ///@param location Où se trouve le fichier
    ///@param key clé qui permet l'accès à la resource
    ///@return faux en cas d'erreur
    bool AddMusic(const std::string &location, const std::string& key);

    ///@brief Charge une texture et l'ajoute au map si possible
    ///@param location Où se trouve le fichier
    ///@param key clé qui permet l'accès à la resource
    ///@return faux en cas d'erreur
    bool AddTexture(const std::string &location, const std::string& key);

    ///@brief Crée l'information nécessaire pour une animation
    ///@param frames nombre d'images
    ///@param key clé pour accéder à l'animation
    ///@return faux en cas d'erreur
    bool AddAnimation(unsigned int frames, const std::string &key);

    ///@brief Ajoute un rectangle à une animation en particulier
    ///@param key clée de l'animation
    ///@param i rectangle à modifier
    ///@param Rect rectangle à ajouter
    void SetAnimRect(const std::string &key, unsigned int i, const sf::IntRect & Rect);

    sf::Texture txError;
    std::vector<sf::IntRect> animError;
    sf::SoundBuffer sbError;
    sf::Music msError;
public:
    ///@brief destructeur
    ~ResManager();
    ///@brief Constructeur
    ResManager();
    ///@brief Charge toutes les images nécessaires
    void LoadResources();
    ///@brief donne accès à une texture
    ///@brief key clé associée à la texture
    ///@return Réference constante vers la texture
    const sf::Texture& GetTexture(const std::string& key);
    ///@brief Donne accès à une animation (ses rectangles)
    ///@brief key clé associée à l'animation
    ///@return Référence constante ver le vector de rectangles
    const std::vector<sf::IntRect>& GetAnimation(const std::string &key);
    ///@brief donne accès à un SoundBuffer
    ///@brief key clé associée au SoundBuffer
    ///@return Réference constante vers le SoundBuffer
    const sf::SoundBuffer& GetSoundBuffer(const std::string& key);
    ///@brief donne accès à une Music
    ///@brief key clé associée à la Music
    ///@return Réference constante vers la Music
    const sf::Music& GetMusic(const std::string& key);


};
