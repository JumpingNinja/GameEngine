//
//  Animation.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 04/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

///@brief Classe qui gére une animation
///
///Cette classe utilise une référence vers une Texture et une liste de rectangles qui définissent la position. Elle a un intervalle et gère l'animation grace à l'appel Play(). L'interval est en steps/frames

class Animation {
    const sf::Texture& myTexture;
    const std::vector<sf::IntRect> *myRects;
    ///@brief si myInterval<0.f alors on considère l'animation manuelle (car on n'a pas d'animation inversées)
    float myInterval, myFrame;
    bool myNeedUpdate;
    unsigned short myLastframe;
public:
    ///@brief Constructeur
    ///@param texture texture à partir de la quelle cette animation marche
    ///@param interval intervalle de l'animation en steps/frames
    ///@param Rects vector des rectangles des images de l'animation
    Animation(const sf::Texture& texture, float interval, const std::vector<sf::IntRect>& Rects);
    ///@brief destructor
    virtual ~Animation() { }
    ///@brief Avance l'animation et modifie le sprite avec la texture associée et le rectangle qui correspond au frame actuel
    ///
    ///Faire attention a la recalculation du rectangle de la texture? avec param adiotionnel sur settexture()
    ///@param timerate vitesse du temps
    ///@param sprite Sprite qui va ètre modifié
    void Play(float timerate, sf::Sprite& sprite);
    ///@brief Change manuellement le frame actuel
    ///@param frame nouveau frame
    void SetFrame(float frame);
    ///@brief Retourne le frame actuel de l'animation
    ///@return le frame où se trouve l'animation
    float GetFrame() const;
	///@brief change l'interval de l'animation
	///@param interval nouvel interval
	void SetInterval(float interval);
	///@brief retourne l'interval de l'animation
	///@return l'interval de l'animation
	float GetInterval() const;
    ///@brief Change l'animation (donc les rectangles)
    ///@param Rects vector de rectangles
    void SetRects(const std::vector<sf::IntRect>& Rects);
};