#include <cstdlib>
#include <iostream>

#include "Physics.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#ifdef SFML_SYSTEM_MACOS
	#include "ResourcePath.hpp"
#endif
/* Simple test de Physics.h */

using namespace Physics;


void glDrawCube(const sf::Vector2f &Position, float size);


int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	window.setVerticalSyncEnabled(1);
	//window.SetFramerateLimit(30);

	glMatrixMode(GL_PROJECTION); //On va ainsi définir le viewport
	glLoadIdentity();
	glOrtho(0.0, 800.0, 600.0, 0.0, 0.0, 100.0);
	//gluPerspective(90.f, 1.f, 1.f, 500.f);
	glDisable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
    //glClearDepth(1.f);

	sf::Clock vent;
	float forceVent(1.f);

	/*sf::Music music;
	music.OpenFromFile(ResourcePath()+"infect.ogg");
	music.SetLoop(1);
	//music.Play();

	sf::SoundBuffer sndB;
	sndB.LoadFromFile(ResourcePath()+"mono.ogg");

	sf::Sound snd;
	snd.SetBuffer(sndB);
	snd.Play();
	 */

	//Une texture OpenGL
	GLuint texture=0;
	{
		sf::Image image;
		#ifdef SFML_SYSTEM_MACOS
		image.loadFromFile(ResourcePath() + "cute.png");
		#else
		image.loadFromFile("cute.png");
		#endif

		glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getWidth(), image.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	}

	// Bind our texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);


//	Vertex* P1 = new Vertex();
//	P1->SetPosition(Vec2(50, 50));
//	P1->SetMass(2);
//	Vertex* P2 = new Vertex();
//	P2->SetPosition(Vec2(150, 50));
//	Vertex* P3 = new Vertex();
//	P3->SetPosition(Vec2(150, 150));
	Vertex* P4 = new Vertex();
	P4->SetPosition(Vec2(100, 25));
	P4->SetFixe();
	Vertex* P5 = new Vertex();
	P5->SetPosition(Vec2(50, 50));
	Vertex* P6 = new Vertex();
	P6->SetPosition(Vec2(100, 150));
	Vertex* P7 = new Vertex();
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
	new Rigid(P4, P6, sqrt(20000.f));
	new Rigid(P5, P7, sqrt(20000.f));

	Vertex* pLeftTop = new Vertex(), *pRightTop = new Vertex(), *pRightBottom = new Vertex(), *pLeftBottom = new Vertex();
	pLeftTop->SetPosition(Vec2(300.f, 10.f));
	pRightTop->SetPosition(Vec2(400.f, 10.f));
	pLeftBottom->SetPosition(Vec2(300.f, 110.f));
	pRightBottom->SetPosition(Vec2(400.f, 110.f));

	new Polygon(4, FLAG_NULL, pLeftTop, pRightTop, pRightBottom, pLeftBottom);
	//new Polygon(4, WITH_LENGTH, pLeftTop, 100.f, pRightTop, 100.f, pRightBottom, 100.f, pLeftBottom, 100.f);
	new Rigid(pLeftTop, pRightBottom);// sqrt(20000.f));
	new Rigid(pLeftBottom, pRightTop);// sqrt(20000.f));

	float taille_cubes = 50.f;
	//for(int i = 1; i < 10; i++)
		//new Polygon(4, FLAG_NULL, new Vertex(taille_cubes*i,taille_cubes*i, i), new Vertex(taille_cubes*i+taille_cubes,taille_cubes*i), new Vertex(taille_cubes*i+taille_cubes,taille_cubes*i+taille_cubes), new Vertex(taille_cubes*i,taille_cubes*i+taille_cubes));
		//new Rectangle(taille_cubes, taille_cubes, 1, 1, 1, 1);


	Vertex* P41 = new Vertex();
	P41->SetPosition(Vec2(150, 150));
	P41->SetFixe();
	Vertex* P42 = new Vertex();
	P42->SetPosition(Vec2(250, 150));
	P42->SetFixe();
	Vertex* P43 = new Vertex();
	P43->SetPosition(Vec2(100, 300));
	P43->SetFixe();

	new Polygon(3, FLAG_NULL, P41, P42, P43);

	//Vertex* P8 = new Vertex();


	/*
	//Un corps ?? Il faudrait ajouter des verices, mais cela ferait plusieurs polygones (no problem)
	Vertex* pB1, *pB2, *pB3, *pB4;
	//corps
	pB1=new Vertex();
	pB1->SetPosition(Vec2(50.f, 50.f));
	pB2=new Vertex();
	pB2->SetPosition(Vec2(50.f, 100.f));
	pB1->SetFixe();
	pB2->SetFixe();
	new Polygon(2, FLAG_NULL, pB1, pB2);

	//Les bras
	pB3=new Vertex();
	pB3->SetPosition(Vec2(25.f, 50.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);
	pB4=new Vertex();
	pB4->SetPosition(Vec2(15.f, 50.f));
	new Polygon(2, FLAG_NULL, pB4, pB3);

	pB3=new Vertex();
	pB3->SetPosition(Vec2(75.f, 50.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);
	pB4=new Vertex();
	pB4->SetPosition(Vec2(85.f, 50.f));
	new Polygon(2, FLAG_NULL, pB4, pB3);

	//les jambes
	pB3=new Vertex();
	pB3->SetPosition(Vec2(45.f, 125.f));
	new Polygon(2, FLAG_NULL, pB2, pB3);

	pB1=new Vertex();
	pB1->SetPosition(Vec2(45.f, 145.f));
	new Polygon(2, FLAG_NULL, pB3, pB1);

	pB3=new Vertex();
	pB3->SetPosition(Vec2(55.f, 125.f));
	new Polygon(2, FLAG_NULL, pB2, pB3);

	pB1=new Vertex();
	pB1->SetPosition(Vec2(55.f, 145.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);

	P4=new Vertex(100.f, 20.f);
	P4->SetRadius(50.f);


	//De l'eau?
	const int waterN(30); //MULTIPLE DE 2
	Vertex *pWater[waterN], *pWaterFixed[waterN];
	for (int i=0; i<waterN; i++)
	{
		pWater[i]= new Vertex(50.f+i*10.f, 300.f);
		pWater[i]->SetMass(0.f);
		if (i==0 || i==waterN-1)
			pWater[i]->SetFixe();
		pWaterFixed[i]=new Vertex(50.f+i*10.f, 300.f);
		pWaterFixed[i]->SetFixe();
		pWaterFixed[i]->SetMass(3.f);
		new Elastic(pWaterFixed[i], pWater[i], 0.f, 0.75f);
		if (i>0)
			new Elastic(pWater[i], pWater[i-1]);
	}

	//Un petit rideau :D
	const int rows=20, colums=20, cTimes(2);
	bool cType(1);
	const float tailleCarre(5.f);
	Vertex* pRideau[rows*colums]={NULL};
	for (int i=0; i<colums; i++)
		for (int j=0; j<rows; j++)
		{
			pRideau[i+j*colums]=new Vertex();
			pRideau[i+j*colums]->SetPosition(Vec2(300.f+i*tailleCarre, 30.f+j*tailleCarre));
			pRideau[i+j*colums]->SetMass(0.1f);
			//On fixe deux des points
			if ((i==0 && j==0) || (i==0  && j==rows-1))// || (i==colums-1 && j==0) || (i==colums-1  && j==rows-1))
				pRideau[i+j*colums]->SetFixe();
			if (j!=0 && i==0)
				pRideau[i+j*colums]->SetFixe();

			//On fait le lien avec celui qui est à gauche est en haut
			if (i>0) //on peut faire le lien sur la gauche
				for (int a=0; a<cTimes; a++)
				{
					if (cType)
						new Elastic(pRideau[i+j*colums-1], pRideau[i+j*colums], -1.f, 5.f);
					else
						new Rigid(pRideau[i+j*colums-1], pRideau[i+j*colums]);
				}

			if (j>0) //on peut faire le lien sur la gauche
				for (int a=0; a<cTimes; a++)
				{
					if (cType)
						new Elastic(pRideau[i+(j-1)*colums], pRideau[i+j*colums], -1.f, 5.f);
					else
						new Rigid(pRideau[i+(j-1)*colums], pRideau[i+j*colums]);
				}
			/*
			if (i==1 && j==0)
				new Elastic(pRideau[i+j*colums-1], pRideau[i+j*colums], -1.f, 2.f);
			if (i==0 && j==1)
				new Elastic(pRideau[i+(j-1)*colums], pRideau[i+j*colums], -1.f, 2.f);

		}
	*/

	int i = 0;
	float prevdt = 0.1f, dt = 0.1f;

	Vertex *grab = NULL;
	Elastic* MouseElastic = NULL;
	Vertex* Mouse = new Vertex();

	Rectangle* rP;
	rP=new Rectangle(40.f, 60.f);
	rP->GetTopLeft().SetPosition(Vec2(10.f,400.f));
	//rP->SetFixed();

	float polygon = 20.f;

	while(window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();

			// Escape pressed : exit
			if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::R:
                        (new Rectangle(50.f, 50.f))->GetTopLeft().SetPosition(Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
                        break;
                    case sf::Keyboard::P:
                         //new Polygon(8, FLAG_NULL, new Vertex(0.f, 1.f*polygon), new Vertex(1.f*polygon, 0.f), new Vertex(2.f*polygon, 0.f),
                                    // new Vertex(3.f*polygon, 1.f*polygon), new Vertex(3.f*polygon, 2.f*polygon), new Vertex(2.f*polygon, 3.f*polygon),
                                    // new Vertex(1.f*polygon, 3.f*polygon), new Vertex(0.f, 2.f*polygon));
                         new Polygon(6, FLAG_NULL, new Vertex(0.f, 1.f*polygon), new Vertex(1.f*polygon, 0.f),
                                     new Vertex(2.f*polygon, 1.f*polygon), new Vertex(2.f*polygon, 2.f*polygon),
                                     new Vertex(1.f*polygon, 3.f*polygon), new Vertex(0.f, 2.f*polygon));
                    default:
                        break;
                }


			// Adjust the viewport when the window is resized
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);

			if (event.type == sf::Event::MouseButtonPressed)
			{

				grab=Vertex::GetNearest(Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
				if(event.mouseButton.button == sf::Mouse::Left)
					delete MouseElastic,
					MouseElastic = new Physics::Elastic(grab, Mouse, 1.f, 5.f);
				if(event.mouseButton.button == sf::Mouse::Middle || event.mouseButton.button == sf::Mouse::XButton1)
					(new Rectangle(25.f, 25.f))->GetTopLeft().SetPosition(Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
			}


		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && grab!=NULL)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				grab->SetPosition(Vec2(sf::Mouse::getPosition(window).x, grab->GetPosition().y));
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					grab->SetPosition(Vec2(grab->GetPosition().x, sf::Mouse::getPosition(window).y));
				else
					grab->SetPosition(Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				rP->ApplyForce(Vec2(50.f,0.f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				rP->ApplyForce(Vec2(-50.f,0.f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				rP->ApplyForce(Vec2(0.f,-50.f));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				Mouse->SetPosition(Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
		//else if(MouseElastic != NULL) delete MouseElastic, MouseElastic = NULL;
		else Mouse->SetFixe();

		glClear(GL_COLOR_BUFFER_BIT); //On efface le fond. Color car on est en 2D
		glClearColor(0.0f, 0.f, 0.f, 1.f); //Ici optionnel car par défaut couleur est rouge
		//glClear(GL_DEPTH_BUFFER_BIT);

		//On prepare la projection
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); //On charge l'identite pour dessiner normalement
		glTranslatef(0.375, 0.375, 0.0); //petit trick qui assure le dessin à la  bonne place

		if (vent.getElapsedTime().asSeconds()>=4.f)
			forceVent=(forceVent>0 ? -1 : 1)*((rand()%400)/100.f+3.f), vent.restart();

		for(int i = 0; i < 1; i++)
        {
            //Physics::ForceAll(Vec2(forceVent, 0.f)); // Vent
            Physics::ForceAll(Vec2(0.f, 12.f), true); // Gravité
			//Physics::ForceAll(Vec2(0.f, 0.f));
			Physics::Update(prevdt, dt), i++;
			prevdt = dt; // Permet de gérer des framerate inconstants
        }


		Vertex::DrawAll();
		Constraint::DrawAll();

		window.display();
	}

	Physics::DeleteAll();
	//On libere la texture
	glDeleteTextures(1, &texture);
}


void glDrawCube(const sf::Vector2f &Position, float size)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(Position.x, Position.y, 0.f);

	glBegin(GL_QUADS);

	//glColor3f(1.f, 0.f, 0.f);
	//front
	/*
	glTexCoord2f(0, 0); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(0, 1); glVertex3f(0.f,  size, 0.f);
	glTexCoord2f(1, 1); glVertex3f( size,  size, 0.f);
	glTexCoord2f(1, 0); glVertex3f( size, 0.f, 0.f);
	*/
	//back
	glTexCoord2f(0, 0); glVertex3f(0.f, 0.f, size);
	glTexCoord2f(0, 1); glVertex3f(0.f,  size, size);
	glTexCoord2f(1, 1); glVertex3f( size,  size, size);
	glTexCoord2f(1, 0); glVertex3f( size, 0.f, size);

	//left side
	glTexCoord2f(0, 0); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(0, 1); glVertex3f(0.f,  size, 0.f);
	glTexCoord2f(1, 1); glVertex3f(0.f,  size,  size);
	glTexCoord2f(1, 0); glVertex3f(0.f, 0.f,  size);

	//right side
	glTexCoord2f(0, 0); glVertex3f(size, 0.f, 0.f);
	glTexCoord2f(0, 1); glVertex3f(size,  size, 0.f);
	glTexCoord2f(1, 1); glVertex3f(size,  size,  size);
	glTexCoord2f(1, 0); glVertex3f(size, 0.f,  size);

	//Top
	glTexCoord2f(0, 1); glVertex3f(0.f, 0.f,  size);
	glTexCoord2f(0, 0); glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2f(1, 0); glVertex3f( size, 0.f, 0.f);
	glTexCoord2f(1, 1); glVertex3f( size, 0.f,  size);

	//bottom
	glTexCoord2f(0, 1); glVertex3f(0.f, size,  size);
	glTexCoord2f(0, 0); glVertex3f(0.f, size, 0.f);
	glTexCoord2f(1, 0); glVertex3f( size, size, 0.f);
	glTexCoord2f(1, 1); glVertex3f( size, size,  size);

	glEnd();

	glPopMatrix();
}
