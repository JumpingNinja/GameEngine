//
//  CollisionEntity.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "CollisionEntity.h"
#include <iostream>

std::list<CollisionEntity*> CollisionEntity::list;
std::list<CollisionEntity*>::iterator CollisionEntity::it;

bool CollisionEntity::IsSolid()
{
    return mySolid;
}

CollisionEntity::CollisionEntity(const bool &solid) : Entity::Entity(), sf::FloatRect(), mySolid(solid), myFriction(0.5f), myBounce(0.5f), myAirFriction(sf::Vector2f()), mySpeed(sf::Vector2f()), myGravity(0.3f), myMaxSpeed(sf::Vector2f(3000.f, 12.f))
{
    CollisionEntity::list.push_back(this);
}

CollisionEntity::~CollisionEntity()
{
    for (CollisionEntity::it=CollisionEntity::list.begin(); CollisionEntity::it!=CollisionEntity::list.end(); CollisionEntity::it++)
    {
        if ((*CollisionEntity::it)==this)
            break;
    }
    
    if ((*CollisionEntity::it)==this)
        CollisionEntity::list.erase(CollisionEntity::it);
}

bool CollisionEntity::IsColliding(CollisionEntity &other)
{
    return Intersects(other);
}

RelativePosition CollisionEntity::GetRelativePosition(CollisionEntity &other)
{
    //Top et Left donnent déjà la position
    sf::Vector2f relPos(other.Left-Left, other.Top-Top);
    //std::cout<<"vect: "<<relPos.x<<", "<<relPos.y<<std::endl;
    
    if (!isPositive(relPos.x)) //on est sur la droite
    {
        if (!isPositive(relPos.y)) //on est en bas
        {
            //on regarde la penetration horizontale et verticale dans le rectangle
            if (abs(relPos.x)+other.Width<abs(relPos.y)+other.Height)
                return kLeft;
            else
                return kTop;
        }
        else
        {
            if (abs(relPos.x)+other.Width<abs(relPos.y)+other.Height)
                return kLeft;
            else
                return kBottom;
        }
    }
    else //on est sur la gauche
    {
        if (isPositive(relPos.y)) //on est en bas
        {
            //on calcule aussi la penetration
            if (abs(relPos.x)+Width<abs(relPos.y)+Height)
                return kRight;
            else
                return kTop;
        }
        else
        {
            if (abs(relPos.x)+Width<abs(relPos.y)+Height) //on est en haut :)
                return kRight;
            else
                return kBottom;
        }
    }
    
    
    //On considere que si ce n'es pas l'une c'est l'autre car cette fonction doit être utilisée lorsqu'il y a collision
}

void CollisionEntity::TakeAStep()
{
    if (mySolid) return;
    //std::cout<<"Step staken\n";
    if (!CheckGround(1.f+Height))
        mySpeed.y+=myGravity*gb::timerate;
    //std::cout<<"grav:"<<myGravity*gb::timerate<<std::endl;
    
    //On limite la vitesse
    mySpeed.y=min(mySpeed.y, myMaxSpeed.y);
    if (mySpeed.x<=0)
        mySpeed.x=max(mySpeed.x, -myMaxSpeed.x);
    else
        mySpeed.x=min(mySpeed.x, myMaxSpeed.x);
    
    //Stoppe quand la vitesse est très petite, il faut prendre la valeur de myGravity pour y!
    if (abs(mySpeed.x)<0.2f*gb::timerate) mySpeed.x=0.f;
    if (abs(mySpeed.y)<0.3f*gb::timerate) mySpeed.y=0.f;
    
    //Move(mySpeed);
    
    float maxSpeed(max(static_cast<float>(abs(mySpeed.x)), static_cast<float>(abs(mySpeed.y)))), tmpStep(1.f), tmpSpeed(maxSpeed);
    //if (!isPositive(maxSpeed)) tmpStep*=-1.f;
    //std::cout<<"Max: "<<max(static_cast<float>(abs(5.f)), static_cast<float>(abs(12.f)))<<std::endl;
    
    while (tmpSpeed>0.01f)
    {
        Move(gb::timerate*mySpeed.x/maxSpeed, gb::timerate*mySpeed.y/maxSpeed);
        if (Collide())
            tmpSpeed=0.f;
        else
            tmpSpeed-=tmpStep;
    }
    
    //std::cout<<"mySpeed: "<<mySpeed.x<<", "<<mySpeed.y<<std::endl;
}

void CollisionEntity::Step()
{
    //std::cout<<"Starting global step\n";
    //list.back()->SetPosition(sf::Mouse::GetPosition().x, sf::Mouse::GetPosition().y);
    //list.back()->Collide();
    //list.back()->TakeAStep();
    for (it=list.begin(); it!=list.end(); it++)
        (*it)->TakeAStep();
        
}

bool CollisionEntity::Collide()
{
    UpdateRect();
    bool finish(0);
    //On teste les collisions
    for (std::list<CollisionEntity*>::iterator ite=list.begin(); ite!=list.end(); ite++)
    {
        //Collisionner avec tout sauf soit même
        //std::cout<<"Collision Check!\n";
        //La collision d'un solid est différente à celle d'un non solide
        if ((*ite)!=this)
        {
            if ((*ite)->IsSolid())
            {
                if (IsColliding(**ite))
                {
                    //RelativePosition relPos(GetRelativePosition(**it));
                    switch (GetRelativePosition(**ite)) {
                        case kLeft:
                        case kRight:
                            //std::cout<<"Sides\n";
                            mySpeed.x=-mySpeed.x*myBounce;
                            mySpeed.y=mySpeed.y*(1.f-myFriction);
                            finish=1;
                            break;
                        case kBottom:
                        case kTop:
                            //std::cout<<"Top or bottom\n";
                            mySpeed.x=mySpeed.x*(1.f-myFriction);
                            mySpeed.y=-mySpeed.y*myBounce;
                            finish=1;
                            break;
                            
                        default:
                            break;
                    }
                    
                }
            }
            
            if (finish)
                return 1;

        }
    }
    return 0;
}

bool CollisionEntity::CheckGround(const float &offsetY)
{
    for (std::list<CollisionEntity*>::iterator ite=list.begin(); ite!=list.end(); ite++)
    {
        if ((*ite)!=this && (*ite)->IsSolid())
        {
            if ((*ite)->Contains(GetPosition().x, GetPosition().y+offsetY))
                return 1;
        }
    }
    return 0;
}

void CollisionEntity::UpdateRect()
{
    Left=GetPosition().x-GetOrigin().x;
    Top=GetPosition().y-GetOrigin().y;
}

void CollisionEntity::SetPosition(const float &x, const float &y)
{
    sf::Transformable::SetPosition(x, y);
    UpdateRect();
}

void CollisionEntity::SetSpeed(const sf::Vector2f &aSpeed)
{
    mySpeed=aSpeed;
}

void CollisionEntity::SetPosition(sf::Vector2f const &vec)
{
    sf::Transformable::SetPosition(vec);
    UpdateRect();
}

void CollisionEntity::SetFriction(const float &friction)
{
    myFriction=friction;
}

void CollisionEntity::SetBounce(const float &bounce)
{
    myBounce=bounce;
}

float CollisionEntity::GetFriction()
{
    return myFriction;
}

float CollisionEntity::GetBounce()
{
    return myBounce;
}
