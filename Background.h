//
//  Background.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 07/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "Entity.h"

class Background : public Entity, private sf::RenderTexture {
private:
    //float myTotal;
    ///@brief facteur de déplacement
    sf::Vector2f myFactor;
public:
    ///@brief constructeur à partir de la taille de la texture
    ///@param Width longueur
    ///@param Height Largeur
    ///@param Depth pronfondeur
    Background(float Width, float Height, short Depth);
    ///@brief constructeur à partir d'une texture
    ///@brief copyTexture texture d'où faire la copie
    Background(const sf::Texture& copyTexture, short Depth);
    ///@brief Constructeur simple
    Background(short Depth);
    ///@brief destructeur
    ~Background();
    
    ///@brief Met à jour la position
    void UpdatePosition();
	
	///@brief met a jour le facteur pour les calculs de position
	void UpdateFactor();
    
};