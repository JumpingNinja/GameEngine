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
    kBottom
    };

class CollisionEntity : public Entity, public sf::FloatRect {
private:
    static std::list<CollisionEntity*> list;
    //static float maxSpeed;
protected:
    bool mySolid; //Solid object don't move
    float myFriction, myBounce, myGravity, myMass;
    sf::Vector2f myAirFriction, mySpeed, myStepSpeed, myMaxSpeed;
    ///@brief update collision rectangle
    void UpdateRect();
public:
    ///@brief Return if the Entity is a solid object
    ///@return true if soled else otherway
    bool IsSolid();
    ///@brief Constructeur par défaut
    ///@param solid défini si l'objet est solide ou pas
    CollisionEntity(bool solid);
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
    ///@param useFriction tenir compte ou pas de la friction du sol
    virtual void TakeAStep(bool useFriction=1);
    ///@brief Collisionne avec le monde
    virtual bool Collide();
    ///@brief vérifie si on est par terre ou pas
    bool CheckGround(float offsetY);
    ///@brief Renvoit le myFriction du sol s'il existe, -1 si l'entité n'est pas sur une autre CollisionEntity
    float GetGroundFriction();
    ///@brief Change la position
    ///@param x nouvel x
    ///@param y nouvel y
    virtual void SetPosition(float x, float y);
    ///@brief Change la position
    ///@param vec vecteur position
    virtual void SetPosition(const sf::Vector2f &vec);
    ///@brief bouge l'objet
    ///@param x mouvement horizontal
    ///@param y mouvement vertical
    virtual void Move(float x, float y);
    ///@brief Change la position
    ///@param vec vecteur de mouvement
    virtual void Move(const sf::Vector2f &vec);
    /** @brief Modificateur de la vitesse.
     * @param aSpeed Nouvelle vitesse.
     **/
	void SetSpeed(const sf::Vector2f& aSpeed);
    /** @brief Change la friction
     ** @param friction nouvelle friction
    **/
    void SetFriction(float friction);
    /** @brief Change le rebondissement
     ** @param bounce nouvel rebondissement
     **/
    void SetBounce(float bounce);
    /** @brief Donne la friction
     ** @return friction de l'objet
     **/
    float GetFriction();
    /** @brief Donne le rebondissement
     ** @return rebondissement de l'objet
     **/
    float GetBounce();
    /** @brief Change la masse
     ** @param mass nouvelle masse
     **/
    void SetMass(float mass);
    /** @brief Donne la masse
     ** @return masse de l'objet
     **/
    float GetMass();
    ///@brief Bouge l'objet jusqu'à que celui-ci se trouve sans collisions
    ///@param dirVec Direction vers où bouger et pas à faire
    ///@param maxStep maximum de boucle à faire
    void MoveOutside(const sf::Vector2f &dirVec, unsigned int maxSteps);
    ///@brief Bouge selon ses cotes et le bas por ne pas rentrer dans autres objets
    void MoveOutside();



    ///@brief Step sur tous les dynamiques
    static void Step();
    ///@brief Obtient la plus grande vitesse pour simuler tout correctement
    ///@return la plus garnde vitesse
    static float GetMaxStep();
};
