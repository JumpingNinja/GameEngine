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

/**
 @brief Information relative à un type de particule
 
 Cette information est nécessaire lorsqu'on veut créer une particule. Elle est a istancier une seule fois car très lourde en données
**/

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
    
	/**
	@brief Donne la quantité d'alphas qu'a la particule
	
	La particule va prendre progressivement tous les alphas de façon linéaire entre chacune.
	@code ParticleInfo pInfo(uneTexture, unVectordeRectangles);
	 pInfo.SetNumberOfAlphas(2);
	 pInfo.SetAlpha(0, 255);
	 pInfo.SetAlpha(1, 0);
	@endcode
	@param n nombre d'alphas
	 **/
	void SetNumberOfAlphas(unsigned int n);
	/**
	 @brief Donne la quantité de couleurs qu'a la particule
	 
	La particule va prendre progressivement toutes les couleurs de façon linéaire entre chacune.
	@code ParticleInfo pInfo(uneTexture, unVectordeRectangles);
	pInfo.SetNumberOfColors(2);
	pInfo.SetColor(0, sf::Color::White);
	pInfo.SetColor(1, sf::Color::Black);
	@endcode
	@param n nombre de couleurs
	 **/
	void SetNumberOfColors(unsigned int n);
	/**
	 @brief Change une valeur d'alpha
	 @param i index de la valeur à changer
	 @param aAlpha nouvelle valeur
	 **/
	void SetAlpha(unsigned int i, sf::Uint8 aAlpha);
	/**
	 @brief Change une valeur de couleur
	 @param i index de la valeur à changer
	 @param aColor nouvelle valeur
	 **/
	void SetColor(unsigned int i, sf::Color aColor);
	
	/**
	 @brief Constructeur
	 @param aTexture reference vers une texture
	 @param aRects Reference vers une animation (vector de rectangle)
	 **/
	ParticleInfo(const sf::Texture &aTexture, const std::vector<sf::IntRect>& aRects);
	///@brief destructeur
	~ParticleInfo();
};

/**
 @brief Classe qui crée des particules
**/

class Particle : public Entity, public Animation {
    const ParticleInfo& myInfo;
    sf::Vector2f mySpeed, mySize;
	float myLife, myCurrentColor, myCurrentAlpha;
    static std::list<Particle*> list;
    static std::list<Particle*>::iterator it;
	/**
	 @brief simule le mouvement de la particule (timerate a supprimer en tant qu'argument)
	 **/
    void TakeAStep(float timerate);
public:
	/**
	 @brief Constructeur
	 @param Info reference vers les caracteristiques de particule
	 @param Interval interval de l'animation
	**/
    Particle(const ParticleInfo &Info, float Interval);
	///@brief destructeur
    ~Particle();
    
	/**@brief Simule le mouvement des particules (timerate est a supprimer)
	 **/
    static void Step(float timerate); 
	/**
	 @brief crée une particule
	 @param pos où créer la particule
	 @param Info caracteristiques de la particule
	 @param Interval interval de l'animation
	 @return pointeur vers la particules
	**/
	static void Create(const sf::Vector2f &pos, const ParticleInfo & Info, float Interval);
    
};