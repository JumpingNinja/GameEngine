#include <cstdlib>
#include <iostream>

#include "Verlet.h"

using namespace std;

int main(int argc, char** argv)
{
	VerletPoint* P1 = new VerletPoint();
	P1->SetPosition(sf::Vector2f(50, 50));
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << endl;
	VerletPoint* P2 = new VerletPoint();
	P2->SetPosition(sf::Vector2f(150, 50));
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
	VerletConstraint* VC1 = new VerletConstraint(P1, P2, 50, 1);

	while(1)
	{
		VC1->Resolve();
		P1->ApplyMomentum(.1, .1);
		P2->ApplyMomentum(.1, .1);
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << endl;
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
		system("PAUSE");
	}

	delete VC1;
}
