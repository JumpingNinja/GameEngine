#include "PhysicsElastic.h"

namespace Physics
{

std::list<Elastic*> Elastic::List;

Elastic::Elastic(Vertex* P1, Vertex* P2,
								float Length, float Spring) :
								Constraint(P1, P2, Length),
								mySpring(Spring)
{
	Elastic::List.push_back(this);
}

Elastic::Elastic(Vertex &P1, Vertex &P2,
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

	// Rapport entre les masses : Si !=0.5, l'un des points sera moins enclin à bouger
	float MassFactor = P1->GetMass()/(P1->GetMass()+P2->GetMass());

	// Normalisation du vecteur (pas besoin de GetNormalized(), on a déjà acLength)
	Vect = Vect/acLength;

	// Si l'un des points est fixe, toute la force est appliquée à l'autre
	P2->ApplyForce(-Vect*factor*(P1->IsFixe()?MassFactor*1:1)),
	P1->ApplyForce(Vect*factor*(P1->IsFixe()?(1-MassFactor):1));
}

void Elastic::glDraw()
{
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	// Plus la contraite est forte, plus le lien est rouge
	glColor3f(std::abs(myLength - GetVector().GetLength())*mySpring*0.5f/myLength, 0.f, 0.f);
	glVertex2f(P1->GetPosition().x, P1->GetPosition().y);
	glVertex2f(P2->GetPosition().x, P2->GetPosition().y);
	glEnd();
	glPopMatrix();
}

}
