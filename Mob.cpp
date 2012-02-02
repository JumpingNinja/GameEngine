#include "Mob.h"

std::list<Mob*> Mob::list;
std::list<Mob*>::iterator Mob::it;
float Mob::maxSpeed = 10; // A définir !

/// @brief Renvoi la norme de Vect (fonction temporaire ?)
float Norm(sf::Vector2f Vect)
{
	return sqrt(Vect.x*Vect.x + Vect.y*Vect.y);
}

Mob::Mob()
{
    Mob::list.push_back(this);
	
	myMaxSpeed = Mob::maxSpeed;
}

Mob::Mob(short aDepth) : Entity(aDepth)
{
	Mob();
}

Mob::Mob(sf::Texture &Texture) : Entity()
{
	Mob();
    SetTexture(Texture);
}

Mob::Mob(sf::Texture &Texture, short aDepth) : Entity(aDepth)
{
	Mob();
    SetTexture(Texture);
}

Mob::~Mob()
{
    for ( Mob::it=Mob::list.begin(); Mob::it!=Mob::list.end(); Mob::it++)
    {
        if ((*Mob::it)==this)
            break;
    }
    
    if ((*Mob::it)==this)
        Mob::list.erase(Mob::it);
}

void Mob::SetSpeed(sf::Vector2f aSpeed)
{
	if(Norm(aSpeed) > myMaxSpeed)
	{
		mySpeed = (aSpeed/Norm(aSpeed))*myMaxSpeed;
	} else {
		mySpeed = aSpeed;
	}
}

void Mob::AddSpeed(sf::Vector2f aSpeed)
{
	if(Norm(mySpeed + aSpeed) > myMaxSpeed)
	{
		mySpeed = ((mySpeed + aSpeed)/Norm(mySpeed + aSpeed))*myMaxSpeed;
	} else {
		mySpeed = mySpeed + aSpeed;
	}
}

void Mob::ApplySpeed()
{
	Move(mySpeed);
}