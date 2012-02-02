#include "Mob.h"

std::vector<Mob*> Mob::list;
std::vector<Mob*>::iterator Mob::it;
float Mob::maxSpeed = 10; // A définir !

/// @brief Renvoi la norme de Vect (fonction temporaire ?)
float Norm(sf::Vector2f Vect)
{
	return sqrt(Vect.x*Vect.x + Vect.y*Vect.y);
}

Mob::Mob()
{
	Mob::it = Mob::list.begin();
	while(Mob::it != Mob::list.end() && myDepth<(*Mob::it)->myDepth)
		Mob::it++;
    
	Mob::list.insert(Mob::it, this);
	
	myMaxSpeed = Mob::maxSpeed;
}

Mob::Mob(short aDepth) : Entity(aDepth)
{
	Mob();
}

Mob::Mob(sf::Texture &Texture) : Entity(Texture)
{
	Mob();
}

Mob::Mob(sf::Texture &Texture, short aDepth) : Entity(Texture, aDepth)
{
	Mob();
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