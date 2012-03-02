#include <cstdlib>
#include <iostream>

#include "Physics.h"

/* Simple test de Physics.h */

using namespace std;

int main(int argc, char** argv)
{
	Point* P1 = new Point();
	P1->SetPosition(Vec2(50, 50));
	P1->SetMass(2);
	Point* P2 = new Point();
	P2->SetPosition(Vec2(150, 50));
	Point* P3 = new Point();
	P3->SetPosition(Vec2(150, 150));
	Point* P4 = new Point();
	P4->SetPosition(Vec2(100, 25));
	P4->SetFixe();
	Point* P5 = new Point();
	P5->SetPosition(Vec2(50, 50));
	Point* P6 = new Point();
	P6->SetPosition(Vec2(100, 150));
	Point* P7 = new Point();
	P7->SetPosition(Vec2(150, 50));
	Elastic* VC1 = new Elastic(P1, P2, 50, 11);
	Elastic* VC2 = new Elastic(P1, P3, 50, 1);
	Elastic* VC3 = new Elastic(P4, P1, 25, 1);
	/*Rigid* VR1 = new Rigid(P4, P5, 50);
	Rigid* VR2 = new Rigid(P5, P6, 50);
	Rigid* VR3 = new Rigid(P6, P7, 50);
	Rigid* VR4 = new Rigid(P7, P4, 50);*/
	Polygon* VP1 = new Polygon(4, WITH_LENGTH, P4, 10.f, P5, 10.f, P6, 10.f, P7, 10.f);

	Point* P8 = new Point();
	new Rigid(P6, P8, 50);
	new Rigid(P8, new Point(), 5);
	new Rigid(P8, new Point(), 5);
	new Rigid(P8, new Point(), 5);
	new Rigid(P8, new Point(), 5);
	new Rigid(P8, new Point(), 5);


	int i = 0;
	float prevdt = 0.1, dt = 0.1;

	while(1)
	{
		cout << "Frame #" << i << endl;
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << " Length P1 P4 : " << (P1->GetPosition() - P4->GetPosition()).GetLength() << endl;
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
		cout << "P3 : " << P3->GetPosition().x << " " << P3->GetPosition().y << endl;
		cout << "P4 : " << P4->GetPosition().x << " " << P4->GetPosition().y << endl;
		cout << "\nLengths : P4P5 : " << (P4->GetPosition() - P5->GetPosition()).GetLength() << " P5P6 : " << (P5->GetPosition() - P6->GetPosition()).GetLength() << " P6P7 : " << (P6->GetPosition() - P7->GetPosition()).GetLength() << " P7P4 : " << (P7->GetPosition() - P4->GetPosition()).GetLength() << endl;

		i++;
		while(i%10 > 0)
			Physics::ForceAll(Vec2(0, 1)), // Gravité
			Physics::Update(prevdt, dt), i++,
			prevdt = dt; // Permet de gérer des framerate inconstants

		system("PAUSE");
	}

	Physics::DeleteAll();
}
