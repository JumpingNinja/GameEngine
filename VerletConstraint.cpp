#include "VerletConstraint.h"
#include <iostream>

VerletConstraint::VerletConstraint(VerletPoint* P1, VerletPoint* P2,
								float Length, float Spring) :
								P1(P1), P2(P2), myLength(Length), mySpring(Spring)
{
}

void VerletConstraint::Resolve()
{
	// Vecteur P1P2
	sf::Vector2f Vect = P2->GetPosition() - P1->GetPosition();
	float acLength = Length(Vect);
	float factor = 0.9*mySpring*(acLength - myLength)/(P1->GetMass()*P1->GetMass());
	std::cout << "Length : " << acLength << std::endl;
	Vect = Vect/acLength;
	// Si l'un des deux points est fixe, la force est entièrement appliquée à l'autre
	if(P1->IsFixe())
		P2->ApplyForce(-Vect*factor);
	else if(P2->IsFixe())
		P1->ApplyForce(Vect*factor);
	else
		P2->ApplyForce(-Vect*factor*0.5f),
		P1->ApplyForce(Vect*factor*0.5f);
}
