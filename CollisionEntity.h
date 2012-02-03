//
//  CollisionEntity.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include "Entity.h"

///@brief Position relative

enum RelativePosition {
    kLeft,
    kRight,
    kTop,
    kBottom,
    kUnknown
    };

class CollisionEntity : public Entity, public sf::FloatRect {
private:
    static std::list<CollisionEntity*> list;
    static std::list<CollisionEntity*>::iterator it;
protected:
    bool mySolid; //Solid object don't move
    float myFriction, myBounce, myGravity;
    sf::Vector2f myAirFriction, mySpeed, myMaxSpeed;
    ///@brief update collision rectangle
    void UpdateRect();
public:
    ///@brief Return if the Entity is a solid object
    ///@return true if soled else otherway
    bool IsSolid();
    ///@brief Constructeur par défaut
    ///@param solid défini si l'objet est solide ou pas
    CollisionEntity(const bool &solid);
    ///@brief destructeur simple
    ~CollisionEntity();
    ///@brief Donne si deux entites collisionnent
    ///@param other une autre entité
    ///@return vrai s'il elles collisionnent, faux sinon
    bool IsColliding(CollisionEntity &other);
    ///@brief Donne si la position relative d'une autre entité
    ///@param other une autre entité
    ///@return Relative position
    RelativePosition GetRelativePosition(CollisionEntity &other);
    ///@brief simule un step
    virtual void TakeAStep();
    ///@brief Collisionne avec le monde
    virtual bool Collide();
    ///@brief vérifie si on est par terre ou pas
    bool CheckGround(const float &offsetY);
    ///@brief Change la position
    virtual void SetPosition(const float &x, const float &y);
    ///@brief Change la position
    virtual void SetPosition(const sf::Vector2f &vec);
    /** @brief Modificateur de la vitesse.
     * @param aSpeed Nouvelle vitesse.
     **/
	void SetSpeed(const sf::Vector2f& aSpeed);
    /** @brief Change la friction
     ** @param friction nouvelle friction
    **/
    void SetFriction(const float &friction);
    /** @brief Change le rebondissement
     ** @param bounce nouvel rebondissement
     **/
    void SetBounce(const float &bounce);
    /** @brief Donne la friction
     ** @return friction de l'objet
     **/
    float GetFriction();
    /** @brief Donne le rebondissement
     ** @return rebondissement de l'objet
     **/
    float GetBounce();
    
    
    
    ///@brief Step sur tous les dynamiques
    static void Step();
};