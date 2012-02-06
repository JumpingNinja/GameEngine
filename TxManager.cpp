//
//  TxManager.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "TxManager.h"
#include <iostream>
#include "ResourcePath.h"


TxManager::TxManager()
{//Load something for txError
}

TxManager::~TxManager()
{
    for (myIt=myResourceMap.begin(); myIt!=myResourceMap.end(); myIt++)
        delete myIt->second;
    myResourceMap.clear();
    
    myAnimations.clear();
}

bool TxManager::AddTexture(std::string const &location, std::string const &key)
{
    //On cherche si la clé existe déja
    myIt=myResourceMap.find(key);
    if (myIt!=myResourceMap.end())
    {
        std::cout<<"Error adding: "<<location<<". There is already a Resource with key: "<<key<<std::endl;
        return 0;
    }
    
    sf::Texture *file(new sf::Texture);
    if (!file->LoadFromFile(ResourcePath()+location))
    {
        std::cout<<"Error loading: "<<location<<". Cannot find the file"<<std::endl;
        return 0;
    }
    
    myResourceMap.insert(std::pair<std::string, sf::Texture*>(key, file));
    
    return 1;
}

bool TxManager::AddAnimation(unsigned int frames, std::string const &key)
{
    //On cherche si la clé existe déja
    myAniIt=myAnimations.find(key);
    if (myAniIt!=myAnimations.end())
    {
        std::cout<<"Error adding animation. There is already an animation with key: "<<key<<std::endl;
        return 0;
    }
    
    myAnimations.insert(std::pair<std::string, std::vector<sf::IntRect> >(key, std::vector<sf::IntRect>()));
    myAniIt=myAnimations.end();
    myAniIt--;
    myAniIt->second.resize(frames);
    
    return 1;
}

void TxManager::SetAnimRect(std::string const &key, unsigned int i, sf::IntRect const &Rect)
{
    myAniIt=myAnimations.find(key);
    if (myAniIt==myAnimations.end()) //la clé n'existe pas
        return;
    
    myAniIt->second[i]=Rect;
}

void TxManager::LoadResources()
{
    AddTexture("img/player.png", "player");
    AddTexture("img/ryu.png", "ryu");
    
    AddAnimation(5, "player_walk");
    SetAnimRect("player_walk", 0, sf::IntRect(37, 0, 9, 17));
    SetAnimRect("player_walk", 1, sf::IntRect(48, 0, 9, 17));
    SetAnimRect("player_walk", 2, sf::IntRect(58, 0, 11, 17));
    SetAnimRect("player_walk", 3, sf::IntRect(69, 0, 10, 17));
    SetAnimRect("player_walk", 4, sf::IntRect(81, 0, 9, 17));
    
    AddAnimation(3, "ryu_walk");
    SetAnimRect("ryu_walk", 0, sf::IntRect(143, 5, 162-143, 37-5));
    SetAnimRect("ryu_walk", 1, sf::IntRect(171, 5, 190-171, 37-5));
    SetAnimRect("ryu_walk", 2, sf::IntRect(197, 5, 219-197, 37-5));
	
    //std::cout<<"size : "<<GetAnimation("player_walk").size()<<" left of first rectangle: "<<GetAnimation("player_walk")[0].Left<<std::endl;
}

const sf::Texture& TxManager::GetTexture(std::string const &key)
{
    //On cherche si la clé existe
    myIt=myResourceMap.find(key);
    if (myIt!=myResourceMap.end())
        return (*(myIt->second));
    else
        return txError;
}

const std::vector<sf::IntRect>& TxManager::GetAnimation(std::string const &key)
{
    myAniIt=myAnimations.find(key);
    if (myAniIt!=myAnimations.end())
        return (myAniIt->second);
    else
        return animError;
}