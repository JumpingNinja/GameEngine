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

CollisionEntity::CollisionEntity(bool solid) : Entity::Entity(), mySolid(solid), myFriction(0.5f), myBounce(0.5f), myGravity(0.3f), myMass(1.f), myAirFriction(sf::Vector2f()), mySpeed(sf::Vector2f()), myStepSpeed(sf::Vector2f()), myMaxSpeed(sf::Vector2f(3000.f, 12.f))
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
    //std::cout<<"rectangle position:"<<Left<<", "<<Top<<" ("<<Width<<", "<<Height<<")\n";
    //std::cout<<"other rectangle position:"<<other.Left<<", "<<other.Top<<" ("<<other.Width<<", "<<other.Height<<")\n";
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
            if (relPos.x+other.Width<relPos.y+other.Height)
                return kLeft;
            else
                return kTop;
        }
        else
        {
            if (relPos.x+other.Width<abs(relPos.y-other.Height))
                return kLeft;
            else
                return kBottom;
        }
    }
    else //on est sur la gauche
    {
        if (!isPositive(relPos.y)) //on est en bas
        {
            //on calcule aussi la penetration
            if (Width-relPos.x<relPos.y+other.Height)
                return kRight;
            else
                return kTop;
        }
        else
        {
            if (Width-relPos.x<abs(relPos.y-other.Height)) //on est en haut :)
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
    if (!CheckGround(0.75f))
        mySpeed.y+=myGravity*gb::timerate;
    //else if (mySpeed.y>0.f)
      //  mySpeed.y=0.f;
        
    //else if (mySpeed.x>0.1f && mySpeed.y<0.1f) MoveOutside();
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
    //Cette vitesse temporelle permet de gérer les collisions entre objets dynamiques
    myStepSpeed=mySpeed;
    //if (!isPositive(maxSpeed)) tmpStep*=-1.f;
    //std::cout<<"Max: "<<max(static_cast<float>(abs(5.f)), static_cast<float>(abs(12.f)))<<std::endl;

    while (tmpSpeed>0.0001f)
    {
        if (tmpSpeed>=1.f)
            Move(gb::timerate*mySpeed.x/maxSpeed, gb::timerate*mySpeed.y/maxSpeed);
        else
            Move(gb::timerate*tmpSpeed*mySpeed.x/maxSpeed, gb::timerate*tmpSpeed*mySpeed.y/maxSpeed);
        
        Collide();
        //if (Collide())
          //  tmpSpeed=0.f;
        //else
            tmpSpeed-=tmpStep;
    }
    
    //std::cout<<this<<": mySpeed: "<<mySpeed.x<<", "<<mySpeed.y<<" myStepSpeed: "<<myStepSpeed.x<<", "<<myStepSpeed.y<<std::endl;
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
        //La collision d'un solid est différente à celle d'un non solide
        if ((*ite)!=this)
        {
            float off(0.5f);
            if ((*ite)->IsSolid())
            {
                if (IsColliding(**ite))
                {
                    switch (GetRelativePosition(**ite)) {
                        case kLeft:
                            Move(off, 0.f);
                            mySpeed.x=-mySpeed.x*myBounce;
                            mySpeed.y=mySpeed.y*(1.f-myFriction);
                            finish=1;
                            break;
                        case kRight:
                            Move(-off, 0.f);
                            mySpeed.x=-mySpeed.x*myBounce;
                            mySpeed.y=mySpeed.y*(1.f-myFriction);
                            finish=1;
                            break;
                        case kBottom:
                            Move(0.f, -off);
                            mySpeed.x=mySpeed.x*(1.f-myFriction);
                            mySpeed.y=-mySpeed.y*myBounce;
                            finish=1;
                            break;
                        case kTop:
                            Move(0.f, off);
                            mySpeed.x=mySpeed.x*(1.f-myFriction);
                            mySpeed.y=-mySpeed.y*myBounce;
                            finish=1;
                            break;
                            
                        default:
                            break;
                    }
                    
                }
            }
            else
            {
                if (IsColliding(**ite))
                {
                    
                    //std::cout<<"Dynamic collision\n";
                    switch (GetRelativePosition(**ite)) {
                        case kLeft:
                            Move(off, 0.f);
                            mySpeed.x=(-mySpeed.x/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass))*myBounce;
                            mySpeed.y=(mySpeed.y/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass))*(1.f-myFriction);
                            (*ite)->mySpeed.x=(-(*ite)->mySpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.x/((myMass+(*ite)->myMass)/myMass))*(*ite)->myBounce;
                            (*ite)->mySpeed.y=((*ite)->mySpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.y/((myMass+(*ite)->myMass)/myMass))*(1.f-(*ite)->myFriction);
                            finish=1;
                            break;
                        case kRight:
                            Move(-off, 0.f);
                            //std::cout<<"Sides\n";
                            //mySpeed.x=-mySpeed.x*myBounce;
                            //mySpeed.y=mySpeed.y*(1.f-myFriction);
                            mySpeed.x=(-mySpeed.x/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass))*myBounce;
                            mySpeed.y=(mySpeed.y/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass))*(1.f-myFriction);
                            (*ite)->mySpeed.x=(-(*ite)->mySpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.x/((myMass+(*ite)->myMass)/myMass))*(*ite)->myBounce;
                            (*ite)->mySpeed.y=((*ite)->mySpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.y/((myMass+(*ite)->myMass)/myMass))*(1.f-(*ite)->myFriction);
                            finish=1;
                            break;
                        case kBottom:
                            Move(0.f, -off);
                            mySpeed.x=(mySpeed.x/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass))*(1.f-myFriction);
                            mySpeed.y=(-mySpeed.y/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass))*myBounce;
                            (*ite)->mySpeed.x=((*ite)->mySpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.x/((myMass+(*ite)->myMass)/myMass))*(1.f-(*ite)->myFriction);
                            (*ite)->mySpeed.y=(-(*ite)->mySpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.y/((myMass+(*ite)->myMass)/myMass))*(*ite)->myBounce;
                            finish=1;
                            break;
                        case kTop:
                            Move(0.f, off);
                            //std::cout<<"Top or bottom\n";
                            //mySpeed.x=mySpeed.x*(1.f-myFriction);
                            //mySpeed.y=-mySpeed.y*myBounce;
                            mySpeed.x=(mySpeed.x/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass))*(1.f-myFriction);
                            mySpeed.y=(-mySpeed.y/((myMass+(*ite)->myMass)/myMass)+(*ite)->myStepSpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass))*myBounce;
                            (*ite)->mySpeed.x=((*ite)->mySpeed.x/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.x/((myMass+(*ite)->myMass)/myMass))*(1.f-(*ite)->myFriction);
                            (*ite)->mySpeed.y=(-(*ite)->mySpeed.y/((myMass+(*ite)->myMass)/(*ite)->myMass)+myStepSpeed.y/((myMass+(*ite)->myMass)/myMass))*(*ite)->myBounce;
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

bool CollisionEntity::CheckGround(float offsetY)
{
    Top+=offsetY; Left+=1.2f; Width-=2.4f;
    for (std::list<CollisionEntity*>::iterator ite=list.begin(); ite!=list.end(); ite++)
    {
        if ((*ite)!=this)// && (*ite)->IsSolid())
        {
            if (IsColliding(**ite))
            {
                Top-=offsetY; Left-=1.2f; Width+=2.4f;
                //MoveOutside();
                return 1;
            }
        }
    }
    Top-=offsetY; Left-=1.2f; Width+=2.4f;
    return 0;
}

void CollisionEntity::UpdateRect()
{
    Left=GetPosition().x-GetOrigin().x;
    Top=GetPosition().y-GetOrigin().y;
}

void CollisionEntity::SetPosition(float x, float y)
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

void CollisionEntity::Move(float x, float y)
{
    sf::Transformable::Move(x, y);
    UpdateRect();
}

void CollisionEntity::Move(sf::Vector2f const &vec)
{
    sf::Transformable::Move(vec);
    UpdateRect();
}

void CollisionEntity::SetFriction(float friction)
{
    myFriction=friction;
}

void CollisionEntity::SetBounce(float bounce)
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

float CollisionEntity::GetMass()
{
    return myMass;
}

void CollisionEntity::SetMass(float mass)
{
    myMass=mass;
}


void CollisionEntity::MoveOutside(sf::Vector2f const &dirVec, unsigned int maxSteps)
{
    bool turn(1); unsigned int times(0);
    while (turn && times<maxSteps)
    {
        turn=0;
        times++;
        for (std::list<CollisionEntity*>::iterator ite=list.begin(); ite!=list.end(); ite++)
            if (IsColliding(**ite))
                Move(dirVec), turn=1;
    }
}

void CollisionEntity::MoveOutside()
{
    float hDiff, vDiff;
    for (std::list<CollisionEntity*>::iterator ite=list.begin(); ite!=list.end(); ite++)
    {
        if (IsColliding(**ite))
        {
            hDiff=Left-(*ite)->Left-(*ite)->Width;
            if (hDiff<0.f)
            {
                RelativePosition relPos(GetRelativePosition(**ite));
                if (relPos==kLeft)
                    Move(-hDiff, 0.f);
                if (relPos==kRight)
                    Move(hDiff, 0.f);
            }
            
            vDiff=Top-(*ite)->Top+Height;
            if (vDiff<0.f)
            {
                RelativePosition relPos(GetRelativePosition(**ite));
                if (relPos==kTop)
                    Move(0.f, -vDiff);
                if (relPos==kBottom)
                    Move(0.f, vDiff);
            }
        }
    }
}

        /*
void CollisionEntity::GetMaxStep()
{
    float maxStepSpeed(0.f);
    for (it=list.begin(); it!=list.end(); it++)
    {
        maxStepSpeed=max(maxStepSpeed, max(static_cast<float>(abs((*it)->mySpeed.x)), static_cast<float>(abs((*it)->mySpeed.y))));
    }
    return maxStepSpeed;
}*/
