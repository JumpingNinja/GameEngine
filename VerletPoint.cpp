#include "VerletPoint.h"

std::list<VerletPoint*> VerletPoint::VPList;

VerletPoint::VerletPoint() :
	myPosition(0, 0),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myRadius(0),
	myMass(1),
	myBounce(0),
	myFixe(0)
{
	VerletPoint::VPList.push_back(this);
}

VerletPoint::~VerletPoint()
{
	VerletPoint::VPList.remove(this);
}

void VerletPoint::UpdateAll(float prevdt, float dt)
{
	for(std::list<VerletPoint*>::iterator ite = VerletPoint::VPList.begin();
		ite != VerletPoint::VPList.end(); ite++)
		(*ite)->ApplyMomentum(prevdt, dt);
}

void VerletPoint::ForceAll(sf::Vector2f Force)
{
	for(std::list<VerletPoint*>::iterator ite = VerletPoint::VPList.begin();
		ite != VerletPoint::VPList.end(); ite++)
		(*ite)->ApplyForce(Force);
}

void VerletPoint::DeleteAll()
{
    while (VerletPoint::VPList.size()>0)
        delete (VerletPoint::VPList.front());
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
	if(myFixe) return false;
	myAcceleration = newAcc;
	return true;
}

bool VerletPoint::SetRadius(float newRadius)
{
	if(newRadius > 0) {
		myRadius = newRadius;
		return true;
	} else return false;
}

bool VerletPoint::SetMass(float newMass)
{
	// Tests...
	myMass = newMass;
	return true;
}

bool VerletPoint::ApplyForce(sf::Vector2f Force, float threshold)
{
	if (!myFixe && Length(Force) > threshold) {
		myAcceleration += Force;
		return true;
	} else return false;
}

void VerletPoint::ApplyMomentum(float prevdt, float dt)
{
	//if(myFixe) return;
	sf::Vector2f tmp = myPosition;
	myPosition += 0.99f*((myPosition - myOldPosition)*(dt/prevdt)) // Inertie
	 + myAcceleration*dt*dt; // Accélération
	myOldPosition = tmp;
	myAcceleration = sf::Vector2f(0,0);
}
