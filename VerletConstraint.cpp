#include "VerletConstraint.h"
#include <iostream>

std::list<VerletConstraint*> VerletConstraint::VCList;

VerletConstraint::VerletConstraint(VerletPoint* P1, VerletPoint* P2,
								float Length, float Spring) :
								P1(P1), P2(P2), myLength(Length),
								mySpring(Spring)
{
	VerletConstraint::VCList.push_back(this);
}

VerletConstraint::~VerletConstraint()
{
	VerletConstraint::VCList.remove(this);
}

void VerletConstraint::ResolveAll()
{
	for(std::list<VerletConstraint*>::iterator ite = VerletConstraint::VCList.begin();
		ite != VerletConstraint::VCList.end(); ite++)
		(*ite)->Resolve();
}

void VerletConstraint::DeleteAll()
{
    while (VerletConstraint::VCList.size()>0)
        delete (VerletConstraint::VCList.front());
}

void VerletConstraint::Resolve()
{
	// Vecteur P1P2
	sf::Vector2f Vect = P2->GetPosition() - P1->GetPosition();

	// Précalcul de la distance P1P2 - Peut être optimisée par une approximation
	float acLength = Length(Vect);

	// Formule à vérifier... Diviser par la masse ? Par acLength pour normaliser ?...
	// float factor = mySpring*(acLength - myLength)/(P1->GetMass() + P1->GetMass());
	float factor = mySpring*(acLength - myLength);

	// Normalisation du vecteur (pas besoin de Normalize(), on a déjà acLength)
	Vect = Vect/acLength;

	P2->ApplyForce(-Vect*factor/P2->GetMass()),
	P1->ApplyForce(Vect*factor/P1->GetMass());
}
