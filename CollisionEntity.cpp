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

CollisionEntity::CollisionEntity(const bool &solid) : Entity::Entity(), sf::FloatRect(), mySolid(solid), myFriction(0.5f), myBounce(0.5f), myAirFriction(sf::Vector2f()), mySpeed(sf::Vector2f()), myGravity(0.3f), myMaxSpeed(sf::Vector2f(8.f, 12.f))
{
    CollisionEntity::list.push_back(this);
    //mySpeed=sf::Vector2f(8.f,-3.f);
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
    std::cout<<"vect: "<<relPos.x<<", "<<relPos.y<<std::endl;
    
    if (0)//sign(relPos.x)==sign(relPos.y))
    {
        if (abs(mySpeed.x)>=abs(mySpeed.y))
            return kLeft;
        else
            return kTop;
    }
    else
    {
        if (!sign(relPos.x)) //positif
            return kTop;
        else
            return kLeft;   
    }
    
    
    if ((Top >= other.Top && Top <= other.Height+other.Top) || (Top+Height >= other.Top && Top+Height <= other.Height+other.Top) || (Top <= other.Top && Top+Height >= other.Top+other.Height))
    {
        if (Left >= other.Left)
            return kLeft;
        else
            return kRight;
    }
    else
    {
        if (Top >= other.Top)
            return kTop;
        else
            return kBottom;
    }
    
    //On considere que si ce n'es pas l'une c'est l'autre car cette fonction doit être utilisée lorsqu'il y a collision
}

void CollisionEntity::TakeAStep()
{
    if (mySolid) return;
    //std::cout<<"Step staken\n";
    if (!CheckGround(1.f+Height))
        mySpeed.y+=myGravity;
    
    //On limite la vitesse
    mySpeed.y=min(mySpeed.y, myMaxSpeed.y);
    if (mySpeed.x<=0)
        mySpeed.x=max(mySpeed.x, -myMaxSpeed.x);
    else
        mySpeed.x=min(mySpeed.x, myMaxSpeed.x);
    
    //Move(mySpeed);
    
    float maxSpeed(max(mySpeed.x, mySpeed.y)), tmpStep(1.f), tmpSpeed(maxSpeed);
    
    while (tmpSpeed>0.f)
    {
        Move(mySpeed.x/maxSpeed, mySpeed.y/maxSpeed);
        if (Collide())
            tmpSpeed=0.f;
        
        tmpSpeed-=tmpStep;
    }
    
    //std::cout<<"mySpeed: "<<mySpeed.x<<", "<<mySpeed.y<<std::endl;
}

void CollisionEntity::Step()
{
    //std::cout<<"Starting global step\n";
    //list.back()->SetPosition(sf::Mouse::GetPosition().x, sf::Mouse::GetPosition().y);
    //list.back()->Collide();
    list.back()->TakeAStep();
    /*for (it=list.begin(); it!=list.end(); it++)
    {
        if (!((*it)->IsSolid()))
            (*it)->TakeAStep();
    }*/
        
}

bool CollisionEntity::Collide()
{
    UpdateRect();
    //On teste les collisions
    for (it=list.begin(); it!=list.end(); it++)
    {
        //Collisionner avec tout sauf soit même
        if ((*it)==this) continue;
        //std::cout<<"Collision Check!\n";
        //La collision d'un solid est différente à celle d'un non solide
        if ((*it)->IsSolid())
        {
            if (IsColliding(**it))
            {
                //RelativePosition relPos(GetRelativePosition(**it));
                switch (GetRelativePosition(**it)) {
                    case kLeft:
                    case kRight:
                        std::cout<<"Sides\n";
                        mySpeed.x=-mySpeed.x*myBounce;
                        mySpeed.y=mySpeed.y*(1.f-myFriction);
                        return 1;
                        break;
                    case kBottom:
                    case kTop:
                        std::cout<<"Top or bottom\n";
                        mySpeed.x=mySpeed.x*(1.f-myFriction);
                        mySpeed.y=-mySpeed.y*myBounce;
                        return 1;
                        break;
                        
                    default:
                        break;
                }
                
            }
        }
    }
    return 0;
}

bool CollisionEntity::CheckGround(const float &offsetY)
{
    for (it=list.begin(); it!=list.end(); it++)
    {
        if ((*it)!=this && (*it)->IsSolid())
        {
            if ((*it)->Contains(GetPosition().x, GetPosition().y+offsetY))
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

void CollisionEntity::SetPosition(sf::Vector2f const &vec)
{
    sf::Transformable::SetPosition(vec);
    UpdateRect();
}
