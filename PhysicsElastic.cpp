#include "PhysicsElastic.h"

std::list<Elastic*> Elastic::List;

Elastic::Elastic(Point* P1, Point* P2,
								float Length, float Spring) :
								Constraint(P1, P2, Length),
								mySpring(Spring)
{
	Elastic::List.push_back(this);
}

Elastic::Elastic(Point &P1, Point &P2,
								float Length, float Spring) :
								Constraint(P1, P2, Length),
								mySpring(Spring)
{
	Elastic::List.push_back(this);
}

Elastic::~Elastic()
{
	Elastic::List.remove(this);
}

void Elastic::ResolveAll()
{
	for(std::list<Elastic*>::iterator ite = Elastic::List.begin();
		ite != Elastic::List.end(); ite++)
		/*if ((*ite)->GetVector().GetLength()>10.f*(*ite)->myLength)
		{
			Elastic* E=(*ite);
			ite--;
			delete <#expression#>
		}
		else*/
			(*ite)->Resolve();
}

void Elastic::DeleteAll()
{
    while (Elastic::List.size()>0)
        delete (Elastic::List.front());
}

void Elastic::Resolve()
{
	// Vecteur P1P2
	Vec2 Vect = P2->GetPosition() - P1->GetPosition();

	// Précalcul de la distance P1P2 - Peut être optimisée par une approximation
	float acLength = Vect.GetLength();

	// Loi de Hooke
	float factor = mySpring*(acLength - myLength);

	// Normalisation du vecteur (pas besoin de GetNormalized(), on a déjà acLength)
	Vect = Vect/acLength;

	P2->ApplyForce(-Vect*factor/P1->GetMass()),
	P1->ApplyForce(Vect*factor/P2->GetMass());
}
