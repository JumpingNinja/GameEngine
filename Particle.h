//
//  Particle.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 08/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include "Entity.h"
#include "Animation.h"

const float NoDeath(-50.f);

class ParticleInfo {
public:
    sf::Vector2f Speed, IncrSpeed, Gravity, Size, IncrSize, Friction, Origin;
	const sf::Texture& Texture;
	const std::vector<sf::IntRect>& Rects;
	float Life, Rotation, IncrRotation;
	std::vector<sf::Uint8> Alpha;
	std::vector<sf::Color> Color;
    bool CanOut;
    short Depth;
	sf::BlendMode Blend;
    
	void SetNumberOfAlphas(unsigned int n);
	void SetNumberOfColors(unsigned int n);
	void SetAlpha(unsigned int i, sf::Uint8 aAlpha);
	void SetColor(unsigned int i, sf::Color aColor);
	
	ParticleInfo(const sf::Texture &aTexture, const std::vector<sf::IntRect>& aRects);
	~ParticleInfo();
};

class Particle : public Entity, public Animation {
    const ParticleInfo& myInfo;
    sf::Vector2f mySpeed, mySize;
	float myLife, myCurrentColor, myCurrentAlpha;
    static std::list<Particle*> list;
    static std::list<Particle*>::iterator it;
    void TakeAStep(float timerate);
public:
    Particle(const ParticleInfo &Info, float Interval);
    ~Particle();
    
    static void Step(float timerate); 
	static void Create(const sf::Vector2f &pos, const ParticleInfo & Info, float Interval);
    
};