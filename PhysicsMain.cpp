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
	window.EnableVerticalSync(1);
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
		image.LoadFromFile(ResourcePath() + "cute.png");
		#else
		image.LoadFromFile("cute.png");
		#endif

		glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	}

	// Bind our texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);


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
	new Rigid(P4, P6, sqrt(20000.f));
	new Rigid(P5, P7, sqrt(20000.f));

	Point* pLeftTop = new Point(), *pRightTop = new Point(), *pRightBottom = new Point(), *pLeftBottom = new Point();
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
		//new Polygon(4, FLAG_NULL, new Point(taille_cubes*i,taille_cubes*i, i), new Point(taille_cubes*i+taille_cubes,taille_cubes*i), new Point(taille_cubes*i+taille_cubes,taille_cubes*i+taille_cubes), new Point(taille_cubes*i,taille_cubes*i+taille_cubes));
		//new Rectangle(taille_cubes, taille_cubes, 1, 1, 1, 1);


	//Point* P8 = new Point();
	
	
	
	//Un corps ?? Il faudrait ajouter des verices, mais cela ferait plusieurs polygones (no problem)
	Point* pB1, *pB2, *pB3, *pB4;
	//corps
	pB1=new Point();
	pB1->SetPosition(Vec2(50.f, 50.f));
	pB2=new Point();
	pB2->SetPosition(Vec2(50.f, 100.f));
	pB1->SetFixe();
	pB2->SetFixe();
	new Polygon(2, FLAG_NULL, pB1, pB2);
	
	//Les bras
	pB3=new Point();
	pB3->SetPosition(Vec2(25.f, 50.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);
	pB4=new Point();
	pB4->SetPosition(Vec2(15.f, 50.f));
	new Polygon(2, FLAG_NULL, pB4, pB3);
	
	pB3=new Point();
	pB3->SetPosition(Vec2(75.f, 50.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);
	pB4=new Point();
	pB4->SetPosition(Vec2(85.f, 50.f));
	new Polygon(2, FLAG_NULL, pB4, pB3);
	
	//les jambes
	pB3=new Point();
	pB3->SetPosition(Vec2(45.f, 125.f));
	new Polygon(2, FLAG_NULL, pB2, pB3);
	
	pB1=new Point();
	pB1->SetPosition(Vec2(45.f, 145.f));
	new Polygon(2, FLAG_NULL, pB3, pB1);
	
	pB3=new Point();
	pB3->SetPosition(Vec2(55.f, 125.f));
	new Polygon(2, FLAG_NULL, pB2, pB3);
	
	pB1=new Point();
	pB1->SetPosition(Vec2(55.f, 145.f));
	new Polygon(2, FLAG_NULL, pB1, pB3);
	
	
	P4=new Point(100.f, 20.f);
	P4->SetRadius(50.f);
	
	
	//De l'eau?
	const int waterN(30); //MULTIPLE DE 2
	Point *pWater[waterN], *pWaterFixed[waterN];
	for (int i=0; i<waterN; i++)
	{
		pWater[i]= new Point(50.f+i*10.f, 300.f);
		pWater[i]->SetMass(0.f);
		if (i==0 || i==waterN-1)
			pWater[i]->SetFixe();
		pWaterFixed[i]=new Point(50.f+i*10.f, 300.f);
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
	Point* pRideau[rows*colums]={NULL};
	for (int i=0; i<colums; i++)
		for (int j=0; j<rows; j++)
		{
			pRideau[i+j*colums]=new Point();
			pRideau[i+j*colums]->SetPosition(Vec2(300.f+i*tailleCarre, 30.f+j*tailleCarre));
			pRideau[i+j*colums]->SetMass(0.01f);
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
			 */
		}


	int i = 0;
	float prevdt = 0.4f, dt = 0.1f;

	Point *grab = NULL;
	Elastic* MouseElastic = NULL;
	Point* Mouse = new Point();
	
	Rectangle* rP;
	rP=new Rectangle(100.f, 20.f);
	rP->GetTopLeft().SetPosition(Vec2(10.f,400.f));
	//rP->SetFixed();

	float polygon = 20.f;

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
			if (event.Type == sf::Event::KeyPressed)
                switch (event.Key.Code)
                {
                    case sf::Keyboard::Escape:
                        window.Close();
                        break;
                    case sf::Keyboard::R:
                        (new Rectangle(50.f, 50.f))->GetTopLeft().SetPosition(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));
                        break;
                    case sf::Keyboard::P:
                         //new Polygon(8, FLAG_NULL, new Point(0.f, 1.f*polygon), new Point(1.f*polygon, 0.f), new Point(2.f*polygon, 0.f),
                                    // new Point(3.f*polygon, 1.f*polygon), new Point(3.f*polygon, 2.f*polygon), new Point(2.f*polygon, 3.f*polygon),
                                    // new Point(1.f*polygon, 3.f*polygon), new Point(0.f, 2.f*polygon));
                         new Polygon(6, FLAG_NULL, new Point(0.f, 1.f*polygon), new Point(1.f*polygon, 0.f),
                                     new Point(2.f*polygon, 1.f*polygon), new Point(2.f*polygon, 2.f*polygon),
                                     new Point(1.f*polygon, 3.f*polygon), new Point(0.f, 2.f*polygon));
                    default:
                        break;
                }


			// Adjust the viewport when the window is resized
            if (event.Type == sf::Event::Resized)
                glViewport(0, 0, event.Size.Width, event.Size.Height);

			if (event.Type == sf::Event::MouseButtonPressed)
			{
					
				grab=Point::GetNearest(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));
				if(event.MouseButton.Button == sf::Mouse::Left)
					delete MouseElastic,
					MouseElastic = new Physics::Elastic(grab, Mouse, 1.f, 5.f);
				if(event.MouseButton.Button == sf::Mouse::Middle || event.MouseButton.Button == sf::Mouse::XButton1)
					(new Rectangle(25.f, 25.f))->GetTopLeft().SetPosition(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));
			}


		}

		if (sf::Mouse::IsButtonPressed(sf::Mouse::Right) && grab!=NULL)
		{
			if (sf::Keyboard::IsKeyPressed(sf::Keyboard::H))
				grab->SetPosition(Vec2(sf::Mouse::GetPosition(window).x, grab->GetPosition().y));
			else
			{
				if (sf::Keyboard::IsKeyPressed(sf::Keyboard::V))
					grab->SetPosition(Vec2(grab->GetPosition().x, sf::Mouse::GetPosition(window).y));
				else
					grab->SetPosition(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));
			}
		}
			

		if (sf::Mouse::IsButtonPressed(sf::Mouse::Left))
				Mouse->SetPosition(Vec2(sf::Mouse::GetPosition(window).x, sf::Mouse::GetPosition(window).y));
		//else if(MouseElastic != NULL) delete MouseElastic, MouseElastic = NULL;
		else Mouse->SetFixe();

		glClear(GL_COLOR_BUFFER_BIT); //On efface le fond. Color car on est en 2D
		glClearColor(0.0f, 0.f, 0.f, 1.f); //Ici optionnel car par défaut couleur est rouge
		//glClear(GL_DEPTH_BUFFER_BIT);
		
		//On prepare la projection
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); //On charge l'identite pour dessiner normalement
		glTranslatef(0.375, 0.375, 0.0); //petit trick qui assure le dessin à la  bonne place

		if (vent.GetElapsedTime().AsSeconds()>=4.f)
			forceVent=(forceVent>0 ? -1 : 1)*((rand()%400)/100.f+3.f), vent.Restart();

		//i++;
		//while(i%10 > 0)
		for(int i = 0; i < 1; i++)
        {
            Physics::ForceAll(Vec2(forceVent, 0.f)); // Vent
            Physics::ForceAll(Vec2(0.f, 9.f), true); // Gravité
			//Physics::ForceAll(Vec2(0.f, 0.f));
			Physics::Update(prevdt, dt), i++;
			prevdt = dt; // Permet de gérer des framerate inconstants
        }

				//On affiche le rideau
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glBegin(GL_QUADS);

		for (int i=0; i<colums; i++) //On fait de 4 en quatre ??
			for (int j=0; j<rows; j++)
			{
				if (i>=colums-1 || j>=rows-1) continue;

				//left top
				glTexCoord2f(static_cast<float>(i)/static_cast<float>(colums), static_cast<float>(j)/static_cast<float>(rows));
				glVertex2f(pRideau[i+j*colums]->GetPosition().x, pRideau[i+j*colums]->GetPosition().y);

				//right top
				glTexCoord2f(static_cast<float>(i+1)/static_cast<float>(colums), static_cast<float>(j)/static_cast<float>(rows));
				glVertex2f(pRideau[i+j*colums+1]->GetPosition().x, pRideau[i+j*colums+1]->GetPosition().y);

				//right bottom
				glTexCoord2f(static_cast<float>(i+1)/static_cast<float>(colums), static_cast<float>(j+1)/static_cast<float>(rows));
				glVertex2f(pRideau[i+(j+1)*colums+1]->GetPosition().x, pRideau[i+(j+1)*colums+1]->GetPosition().y);

				//Left bottom
				glTexCoord2f(static_cast<float>(i)/static_cast<float>(colums), static_cast<float>(j+1)/static_cast<float>(rows));
				glVertex2f(pRideau[i+(j+1)*colums]->GetPosition().x, pRideau[i+(j+1)*colums]->GetPosition().y);
			}

		glEnd();
		
		//on affiche l'eau
		glColor4f(0.f, 0.1f, 1.f, 0.5f);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i=0; i<waterN-1; i++)
		{
			glVertex2f(pWaterFixed[i]->GetPosition().x, pWaterFixed[i]->GetPosition().y+200.f);
			glVertex2f(pWater[i]->GetPosition().x, pWater[i]->GetPosition().y);
			glVertex2f(pWaterFixed[i+1]->GetPosition().x, pWaterFixed[i+1]->GetPosition().y+200.f);
			glVertex2f(pWater[i+1]->GetPosition().x, pWater[i+1]->GetPosition().y);
			
					   
		}
		glEnd();
		
		
		
		//for (int i=0; i<10; i++)
		//	glDrawCube(sf::Vector2f(i*20.f, 400.f), 20.f);

		/*glBegin(GL_QUADS);
		glColor4f(1.f, 1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f); glVertex2f(pRideau[0]->GetPosition().x, pRideau[0]->GetPosition().y);
		glTexCoord2f(1.f, 0.f); glVertex2f(pRideau[1]->GetPosition().x, pRideau[1]->GetPosition().y);
		glTexCoord2f(1.f, 1.f); glVertex2f(pRideau[colums*1+1]->GetPosition().x, pRideau[colums*1+1]->GetPosition().y);
		glTexCoord2f(0.f, 1.f); glVertex2f(pRideau[colums*1]->GetPosition().x, pRideau[colums*1]->GetPosition().y);

		glEnd();
		 */

		/*
		 glBegin(GL_QUADS);
		 glColor4f(1.f, 1.f, 1.f, 1.f);
		 glTexCoord2f(0.f, 0.f); glVertex2f(pRideau[0]->GetPosition().x, pRideau[0]->GetPosition().y);
		 glTexCoord2f(1.f, 0.f); glVertex2f(pRideau[colums-1]->GetPosition().x, pRideau[colums-1]->GetPosition().y);
		 glTexCoord2f(1.f, 1.f); glVertex2f(pRideau[colums*rows-1]->GetPosition().x, pRideau[colums*rows-1]->GetPosition().y);
		 glTexCoord2f(0.f, 1.f); glVertex2f(pRideau[colums*(rows-1)]->GetPosition().x, pRideau[colums*(rows-1)]->GetPosition().y);

		 glEnd();
		 */

		/*
		glMatrixMode(GL_PROJECTION); //On va ainsi définir le viewport
		glLoadIdentity();
		glOrtho(0.0, 800.0, 600.0, 0.0, 0.0, 100.0);
*/
		
		

		//Point::DrawAll();
		//Constraint::DrawAll();

		window.Display();
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
