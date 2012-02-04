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
#include <string>

class TxManager {
    std::map<std::string, sf::Texture*> myResourceMap;
    std::map<std::string, sf::Texture*>::iterator myIt;
    ///@brief Charge une texture et l'ajoute au map si possible
    ///@param location Où se trouve le fichier
    ///@param key clé qui permet l'accès à la resource
    ///@return faux en cas d'erreur
    bool AddTexture(const std::string &location, const std::string& key);
    sf::Texture txError;
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
    
};