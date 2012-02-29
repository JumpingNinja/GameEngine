#include <cstdlib>
#include <iostream>

#include "Verlet.h"

/* Simple test de Verlet.h */

using namespace std;

int main(int argc, char** argv)
{
	VerletPoint* P1 = new VerletPoint();
	P1->SetPosition(sf::Vector2f(50, 50));
	P1->SetMass(2);
	VerletPoint* P2 = new VerletPoint();
	P2->SetPosition(sf::Vector2f(150, 50));
	VerletPoint* P3 = new VerletPoint();
	P3->SetPosition(sf::Vector2f(150, 150));
	VerletPoint* P4 = new VerletPoint();
	P4->SetPosition(sf::Vector2f(100, 25));
	P4->SetFixe();
	VerletConstraint* VC1 = new VerletConstraint(P1, P2, 50, 0.1);
	VerletConstraint* VC2 = new VerletConstraint(P1, P3, 50, 0.1);
	VerletConstraint* VC3 = new VerletConstraint(P4, P1, 25, 0.1);

	while(1)
	{
		VerletPoint::ForceAll(sf::Vector2f(0, 1));
		VerletConstraint::ResolveAll();
		VerletPoint::UpdateAll(.1, .1);
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << endl;
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
		cout << "P3 : " << P3->GetPosition().x << " " << P3->GetPosition().y << endl;
		cout << "P4 : " << P4->GetPosition().x << " " << P4->GetPosition().y << endl;
		system("PAUSE");
	}

	VerletDeleteAll();
}
