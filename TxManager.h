//
//  TxManager.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

///@brief Gère les textures et donne accès à elles

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class TxManager {
    std::map<std::string, sf::Texture*> myResourceMap;
    std::map<std::string, sf::Texture*>::iterator myIt;
    std::map<std::string, std::vector<sf::IntRect> > myAnimations;
    std::map<std::string, std::vector<sf::IntRect> >::iterator myAniIt;
    ///@brief Charge une texture et l'ajoute au map si possible
    ///@param location Où se trouve le fichier
    ///@param key clé qui permet l'accès à la resource
    ///@return faux en cas d'erreur
    bool AddTexture(const std::string &location, const std::string& key);
    ///@brief Crée l'information nécessaire pour une animation
    ///@param frames nombre d'images
    ///@param key clé pour accéder à l'animation
    ///@return faux en cas d'erreur
    bool AddAnimation(const unsigned int &frames, const std::string &key);
    ///@brief Ajoute un rectangle à une animation en particulier
    ///@param key clée de l'animation
    ///@param i rectangle à modifier
    ///@param Rect rectangle à ajouter
    void SetAnimRect(const std::string &key, const unsigned int &i, const sf::IntRect & Rect);
    sf::Texture txError;
    std::vector<sf::IntRect> animError;
public:
    ///@brief destructeur
    ~TxManager();
    ///@brief Constructeur
    TxManager();
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
    
    
};