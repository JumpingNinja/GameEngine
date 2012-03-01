#include "VerletRigid.h"
#include <iostream>

std::list<VerletRigid*> VerletRigid::VRList;

VerletRigid::VerletRigid(VerletPoint* P1, VerletPoint* P2,
								float Length) :
								P1(P1), P2(P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = ComputeLength(P1->GetPosition() - P2->GetPosition());
	VerletRigid::VRList.push_back(this);
}

VerletRigid::VerletRigid(VerletPoint &P1, VerletPoint &P2,
								float Length) :
								P1(&P1), P2(&P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = ComputeLength(P1.GetPosition() - P2.GetPosition());
	VerletRigid::VRList.push_back(this);
}

VerletRigid::~VerletRigid()
{
	VerletRigid::VRList.remove(this);
}

void VerletRigid::ReplaceAll(int iterations)
{
	for(std::list<VerletRigid*>::iterator ite = VerletRigid::VRList.begin();
		ite != VerletRigid::VRList.end(); ite++)
		(*ite)->Replace(iterations);
}

void VerletRigid::DeleteAll()
{
    while (VerletRigid::VRList.size()>0)
        delete (VerletRigid::VRList.front());
}

void VerletRigid::Replace(int iterations)
{
	for(int i = 0; i < iterations; i++)
	{
		// Vecteur P1P2
		sf::Vector2f Vect = P2->GetPosition() - P1->GetPosition();

		// Précalcul de la distance P1P2 - Peut être optimisée par une approximation
		float acLength = ComputeLength(Vect);

		float factor = (acLength - myLength);

		// Normalisation du vecteur (pas besoin de Normalize(), on a déjà acLength)
		Vect = Vect/acLength;

		if(P2->IsFixe())
			P1->CorrectPosition(Vect*factor);
		else if(P1->IsFixe())
			P2->CorrectPosition(-Vect*factor);
		else
			P2->CorrectPosition(-Vect*factor*0.5f),
			P1->CorrectPosition(Vect*factor*0.5f);
	}
}

