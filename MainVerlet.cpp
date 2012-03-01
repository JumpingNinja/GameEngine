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
	VerletPoint* P5 = new VerletPoint();
	P5->SetPosition(sf::Vector2f(50, 50));
	VerletPoint* P6 = new VerletPoint();
	P5->SetPosition(sf::Vector2f(100, 150));
	VerletPoint* P7 = new VerletPoint();
	P5->SetPosition(sf::Vector2f(150, 50));
	VerletConstraint* VC1 = new VerletConstraint(P1, P2, 50, 0.1);
	VerletConstraint* VC2 = new VerletConstraint(P1, P3, 50, 0.1);
	VerletConstraint* VC3 = new VerletConstraint(P4, P1, 25, 1);
	VerletRigid* VR1 = new VerletRigid(P4, P5, 50);
	VerletRigid* VR2 = new VerletRigid(P5, P6, 50);
	VerletRigid* VR3 = new VerletRigid(P6, P7, 50);
	VerletRigid* VR4 = new VerletRigid(P7, P4, 50);

	VerletPoint* P8 = new VerletPoint();
	new VerletRigid(P6, P8, 50);
	new VerletRigid(P8, new VerletPoint(), 5);
	new VerletRigid(P8, new VerletPoint(), 5);
	new VerletRigid(P8, new VerletPoint(), 5);
	new VerletRigid(P8, new VerletPoint(), 5);
	new VerletRigid(P8, new VerletPoint(), 5);


	int i = 0;

	while(1)
	{
		i++;
		cout << "Frame #" << i << endl;
		VerletPoint::ForceAll(sf::Vector2f(0, 1));
		VerletRigid::ReplaceAll(10);
		VerletConstraint::ResolveAll();
		VerletPoint::UpdateAll(.1, .1);
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << " Length P1 P4 : " << ComputeLength(P1->GetPosition() - P4->GetPosition()) << endl;
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
		cout << "P3 : " << P3->GetPosition().x << " " << P3->GetPosition().y << endl;
		cout << "P4 : " << P4->GetPosition().x << " " << P4->GetPosition().y << endl;
		cout << "\nLengths : P4P5 : " << ComputeLength(P4->GetPosition() - P5->GetPosition()) << " P5P6 : " << ComputeLength(P5->GetPosition() - P6->GetPosition()) << " P6P7 : " << ComputeLength(P6->GetPosition() - P7->GetPosition()) << " P7P4 : " << ComputeLength(P7->GetPosition() - P4->GetPosition()) << endl;
		system("PAUSE");
	}

	VerletDeleteAll();
}
