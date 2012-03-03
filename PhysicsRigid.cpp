#include "PhysicsRigid.h"

namespace Physics
{

std::list<Rigid*> Rigid::List;

Rigid::Rigid(Point* P1, Point* P2,
								float Length) :
								Constraint(P1, P2, Length)
{
	Rigid::List.push_back(this);
}

Rigid::Rigid(Point &P1, Point &P2,
								float Length) :
								Constraint(P1, P2, Length)
{
	Rigid::List.push_back(this);
}

Rigid::~Rigid()
{
	Rigid::List.remove(this);
}

void Rigid::ResolveAll(int iterations)
{
	for(std::list<Rigid*>::iterator ite = Rigid::List.begin();
		ite != Rigid::List.end(); ite++)
		(*ite)->Resolve(iterations);
}

void Rigid::DeleteAll()
{
    while (Rigid::List.size()>0)
        delete (Rigid::List.front());
}

void Rigid::Resolve()
{
	Resolve(10);
}

void Rigid::Resolve(int iterations)
{
	for(int i = 0; i < iterations; i++)
	{
		// Vecteur P1P2
		Vec2 Vect = P2->GetPosition() - P1->GetPosition();

		// Précalcul de la distance P1P2 - Peut être optimisée par une approximation
		float acLength = Vect.GetLength();

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

void Rigid::glDraw()
{
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	glColor3f(0.f, 0.f, 1.f);
	glVertex2f(P1->GetPosition().x, P1->GetPosition().y);
	glVertex2f(P2->GetPosition().x, P2->GetPosition().y);
	glEnd();
	glPopMatrix();
}

}
