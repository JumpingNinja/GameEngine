#include <cstdlib>
#include <iostream>

#include "Physics.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

/* Simple test de Physics.h */

using namespace std;

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.EnableVerticalSync(1);
	//window.SetFramerateLimit(30);

	glMatrixMode(GL_PROJECTION); //On va ainsi définir le viewport
	glLoadIdentity();
	glOrtho(0.0, 800.0, 600.0, 0.0, 0.0, 1.0);
	glDisable(GL_DEPTH_TEST);


//	Point* P1 = new Point();
//	P1->SetPosition(Vec2(50, 50));
//	P1->SetMass(2);
//	Point* P2 = new Point();
//	P2->SetPosition(Vec2(150, 50));
//	Point* P3 = new Point();
//	P3->SetPosition(Vec2(150, 150));
	Point* P4 = new Point();
	P4->SetPosition(Vec2(100, 25));
	P4->SetFixe();
	Point* P5 = new Point();
	P5->SetPosition(Vec2(50, 50));
	Point* P6 = new Point();
	P6->SetPosition(Vec2(100, 150));
	Point* P7 = new Point();
	P7->SetPosition(Vec2(150, 50));
//	Elastic* VC1 = new Elastic(P1, P2, 50, 11);
//	Elastic* VC2 = new Elastic(P1, P3, 50, 1);
//	Elastic* VC3 = new Elastic(P4, P1, 25, 1);
	/*Rigid* VR1 = new Rigid(P4, P5, 50);
	Rigid* VR2 = new Rigid(P5, P6, 50);
	Rigid* VR3 = new Rigid(P6, P7, 50);
	Rigid* VR4 = new Rigid(P7, P4, 50);*/
	Polygon* VP1 = new Polygon(4, WITH_LENGTH, P4, 100.f, P5, 100.f, P6, 100.f, P7, 100.f);
	//Polygon* VP1 = new Polygon(4, FLAG_NULL, P4, P5, P6, P7);

	Point* pLeftTop = new Point(), *pRightTop = new Point(), *pRightBottom = new Point(), *pLeftBottom = new Point();
	pLeftTop->SetPosition(Vec2(300.f, 10.f));
	pRightTop->SetPosition(Vec2(400.f, 10.f));
	pLeftBottom->SetPosition(Vec2(300.f, 110.f));
	pRightBottom->SetPosition(Vec2(400.f, 110.f));

	new Polygon(4, FLAG_NULL, pLeftTop, pRightTop, pRightBottom, pLeftBottom);
	//new Polygon(4, WITH_LENGTH, pLeftTop, 100.f, pRightTop, 100.f, pRightBottom, 100.f, pLeftBottom, 100.f);

	//new Rigid(pLeftTop, pRightBottom);// sqrt(20000.f));
	//new Rigid(pLeftBottom, pRightTop);// sqrt(20000.f));

	//Point* P8 = new Point();
	new Rigid(P4, P6, sqrt(20000.f));
	new Rigid(P5, P7, sqrt(20000.f));


	int i = 0;
	float prevdt = 0.1, dt = 0.1;

	Point *grab=NULL;

	while(window.IsOpen())
	{
		// Process events
		sf::Event event;
		while (window.PollEvent(event))
		{
			// Close window : exit
			if (event.Type == sf::Event::Closed)
				window.Close();

			// Escape pressed : exit
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Escape)
				window.Close();
			// Adjust the viewport when the window is resized
            if (event.Type == sf::Event::Resized)
                glViewport(0, 0, event.Size.Width, event.Size.Height);
			if (event.Type == sf::Event::MouseButtonPressed)
				std::cout<<"Grab!\n", grab=Point::GetNearest(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y) );

		}

		if (sf::Mouse::IsButtonPressed(sf::Mouse::Left) && grab!=NULL)
			grab->SetPosition(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));

		glClear(GL_COLOR_BUFFER_BIT); //On efface le fond. Color car on est en 2D
		glClearColor(0.0f, 0.f, 0.f, 1.f); //Ici optionnel car par défaut couleur est rouge

		//On prepare la projection
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); //On charge l'identite pour dessiner normalement
		glTranslatef(0.375, 0.375, 0.0); //petit trick qui assure le dessin à la  bonne place

		/*cout << "Frame #" << i << endl;
		cout << "P1 : " << P1->GetPosition().x << " " << P1->GetPosition().y << " Length P1 P4 : " << (P1->GetPosition() - P4->GetPosition()).GetLength() << endl;
		cout << "P2 : " << P2->GetPosition().x << " " << P2->GetPosition().y << endl;
		cout << "P3 : " << P3->GetPosition().x << " " << P3->GetPosition().y << endl;
		cout << "P4 : " << P4->GetPosition().x << " " << P4->GetPosition().y << endl;
		cout << "\nLengths : P4P5 : " << (P4->GetPosition() - P5->GetPosition()).GetLength() << " P5P6 : " << (P5->GetPosition() - P6->GetPosition()).GetLength() << " P6P7 : " << (P6->GetPosition() - P7->GetPosition()).GetLength() << " P7P4 : " << (P7->GetPosition() - P4->GetPosition()).GetLength() << endl;

		 */

		i++;
		//while(i%10 > 0)
			Physics::ForceAll(Vec2(0, 1)), // Gravité
			Physics::Update(prevdt, dt), i++,
			prevdt = dt; // Permet de gérer des framerate inconstants

		//system("PAUSE");


		Point::DrawAll();
		Constraint::DrawAll();

		window.Display();
	}

	Physics::DeleteAll();
}
