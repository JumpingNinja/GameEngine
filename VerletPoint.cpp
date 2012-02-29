#include "VerletPoint.h"
#include <iostream>

VerletPoint::VerletPoint() :
	myPosition(0, 0),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myMass(1),
	myBounce(0),
	myFixe(0)
{
}

bool VerletPoint::SetPosition(sf::Vector2f newPos, bool oldToo)
{
	// Tests...
	myPosition = newPos;
	if(oldToo) myOldPosition = newPos;
	return true;
}

bool VerletPoint::SetAcceleration(sf::Vector2f newAcc)
{
	// Tests...
	myAcceleration = newAcc;
	return true;
}

bool VerletPoint::ApplyForce(sf::Vector2f Force)
{
	myAcceleration += Force;
	return true;
}

void VerletPoint::ApplyMomentum(float prevdt, float dt)
{
	sf::Vector2f tmp = myPosition;
	myPosition += ((myPosition - myOldPosition)*(dt/prevdt)) + myAcceleration*dt*dt;
	std::cout << "Acc : " << myAcceleration.x << " " << myAcceleration.y << std::endl;
	std::cout << "Momentum : " << (myPosition - myOldPosition).x << " " << (myPosition - myOldPosition).y << std::endl;
	myOldPosition = tmp;
	myAcceleration = sf::Vector2f(0,0);
}
