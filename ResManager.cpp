//
//  ResManager.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "ResManager.h"
#include <iostream>
#include "ResourcePath.h"


ResManager::ResManager() : mySoundBuffers(), myMusics(), myTextures(), myTexturesIt(), myAnimations(), myAnimationsIt(), txError(), animError()
{//Load something for txError
}

ResManager::~ResManager()
{
    for (myTexturesIt=myTextures.begin(); myTexturesIt!=myTextures.end(); myTexturesIt++)
        delete myTexturesIt->second;
    myTextures.clear();

    myAnimations.clear();
}

bool ResManager::AddSoundBuffer(std::string const &location, std::string const &key)
{
	mySoundBuffersIt = mySoundBuffers.find(key);
	if(mySoundBuffersIt != mySoundBuffers.end())
	{
        std::cout<<"Error adding: "<<location<<". There is already a SoundBuffer with key: "<<key<<std::endl;
        return 0;
	}

	sf::SoundBuffer* file(new sf::SoundBuffer);
	if(!file->LoadFromFile(ResourcePath()+location))
	{
        std::cout<<"Error loading: "<<location<<". Cannot find the file"<<std::endl;
        return 0;
	}

	mySoundBuffers[key] = file;
	return 1;
}

bool ResManager::AddMusic(std::string const &location, std::string const &key)
{
	myMusicsIt = myMusics.find(key);
	if(myMusicsIt != myMusics.end())
	{
        std::cout<<"Error adding: "<<location<<". There is already a Music with key: "<<key<<std::endl;
        return 0;
	}

	sf::Music* file(new sf::Music);
	if(!file->OpenFromFile(ResourcePath()+location))
	{
        std::cout<<"Error loading: "<<location<<". Cannot find the file"<<std::endl;
        return 0;
	}

	myMusics[key] = file;

	return 1;
}

bool ResManager::AddTexture(std::string const &location, std::string const &key)
{
    //On cherche si la clé existe déja
    myTexturesIt=myTextures.find(key);
    if (myTexturesIt!=myTextures.end())
    {
        std::cout<<"Error adding: "<<location<<". There is already a Texture with key: "<<key<<std::endl;
        return 0;
    }

    sf::Texture *file(new sf::Texture);
    if (!file->LoadFromFile(ResourcePath()+location))
    {
        std::cout<<"Error loading: "<<location<<". Cannot find the file"<<std::endl;
        return 0;
    }

    myTextures.insert(std::pair<std::string, sf::Texture*>(key, file));

    return 1;
}

bool ResManager::AddAnimation(unsigned int frames, std::string const &key)
{
    //On cherche si la clé existe déja
    myAnimationsIt=myAnimations.find(key);
    if (myAnimationsIt!=myAnimations.end())
    {
        std::cout<<"Error adding animation. There is already an animation with key: "<<key<<std::endl;
        return 0;
    }

    myAnimations.insert(std::pair<std::string, std::vector<sf::IntRect> >(key, std::vector<sf::IntRect>()));
    myAnimationsIt=myAnimations.end();
    myAnimationsIt--;
    myAnimationsIt->second.resize(frames);

    return 1;
}

void ResManager::SetAnimRect(std::string const &key, unsigned int i, sf::IntRect const &Rect)
{
    myAnimationsIt=myAnimations.find(key);
    if (myAnimationsIt==myAnimations.end()) //la clé n'existe pas
        return;

    myAnimationsIt->second[i]=Rect;
}

void ResManager::LoadResources()
{
    AddSoundBuffer("jump.wav", "Jump");

    AddTexture("img/player.png", "player");
    AddTexture("img/ryu.png", "ryu");
    AddTexture("img/SplashScreen.png", "back");

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
}

const sf::Texture& ResManager::GetTexture(std::string const &key)
{
    //On cherche si la clé existe
    myTexturesIt=myTextures.find(key);
    if (myTexturesIt!=myTextures.end())
        return (*(myTexturesIt->second));
    else
        return txError;
}

const std::vector<sf::IntRect>& ResManager::GetAnimation(std::string const &key)
{
    myAnimationsIt=myAnimations.find(key);
    if (myAnimationsIt!=myAnimations.end())
        return (myAnimationsIt->second);
    else
        return animError;
}

const sf::SoundBuffer& ResManager::GetSoundBuffer(std::string const &key)
{
    mySoundBuffersIt = mySoundBuffers.find(key);
    if (mySoundBuffersIt != mySoundBuffers.end())
        return (*(mySoundBuffersIt->second));
    else
        return sbError;
}

const sf::Music& ResManager::GetMusic(std::string const &key)
{
    myMusicsIt = myMusics.find(key);
    if (myMusicsIt != myMusics.end())
        return (*(myMusicsIt->second));
    else
        return msError;
}