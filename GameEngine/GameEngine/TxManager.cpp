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
{//Load something fro txError
}

TxManager::~TxManager()
{
    for (myIt=myResourceMap.begin(); myIt!=myResourceMap.end(); myIt++)
        delete myIt->second;
    myResourceMap.clear();
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

void TxManager::LoadResources()
{
    AddTexture("img/player.png", "player");
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