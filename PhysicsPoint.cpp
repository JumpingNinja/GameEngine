#include "PhysicsPoint.h"

namespace Physics
{

std::list<Point*> Point::List;

Point::Point() :
	myPosition(0, 0),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myRadius(0),
	myMass(1),
	myBounce(0),
	myFixe(0)
{
	Point::List.push_back(this);
}

Point::Point(float x, float y) :
	myPosition(x, y),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myRadius(0),
	myMass(1),
	myBounce(0),
	myFixe(0)
{
	Point::List.push_back(this);
}

Point::Point(float x, float y, float Mass) :
	myPosition(x, y),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myRadius(0),
	myMass(Mass),
	myBounce(0),
	myFixe(0)
{
	Point::List.push_back(this);
}

Point::Point(Vec2 Pos) :
	myPosition(Pos),
	myOldPosition(myPosition), // Vitesse nulle à la création
	myAcceleration(0, 0), // Accélération nulle à la création
	myRadius(0),
	myMass(1),
	myBounce(0),
	myFixe(0)
{
	Point::List.push_back(this);
}

Point::~Point()
{
	Point::List.remove(this);
}

void Point::UpdateAll(float prevdt, float dt)
{
	for(std::list<Point*>::iterator ite = Point::List.begin();
		ite != Point::List.end(); ite++)
	{
		(*ite)->ApplyMomentum(prevdt, dt);

		// Replace le point dans les limites du monde
		if((*ite)->GetPosition().x > 800)
			(*ite)->SetPosition(Vec2(800.f, (*ite)->GetPosition().y));
		if((*ite)->GetPosition().x < 0)
			(*ite)->SetPosition(Vec2(0.f, (*ite)->GetPosition().y));
		if((*ite)->GetPosition().y > 600)
			(*ite)->SetPosition(Vec2((*ite)->GetPosition().x, 600.f));
		if((*ite)->GetPosition().y < 0)
			(*ite)->SetPosition(Vec2((*ite)->GetPosition().x, 0.f));

        // Teste si une coordonnée vaut NaN
        if((*ite)->GetPosition().x != (*ite)->GetPosition().x ||
			(*ite)->GetPosition().y != (*ite)->GetPosition().y)
        {
            (*ite)->SetPosition(Vec2(0, 0), 1);
        }
	}
}

void Point::ForceAll(Vec2 Force, bool Mass)
{
	for(std::list<Point*>::iterator ite = Point::List.begin();
		ite != Point::List.end(); ite++)
		(*ite)->ApplyForce(Force*((Mass)?(*ite)->GetMass():1.f));
}

void Point::DeleteAll()
{
    while (Point::List.size()>0)
        delete (Point::List.front());
}

bool Point::SetPosition(Vec2 newPos, bool oldToo)
{
	myPosition = newPos;
	if(oldToo) myOldPosition = newPos;
	return true;
}

bool Point::CorrectPosition(Vec2 add)
{
	if(myFixe) return false;
	myPosition += add;
	return true;
}

bool Point::SetAcceleration(Vec2 newAcc)
{
	if(myFixe) return false;
	myAcceleration = newAcc;
	return true;
}

bool Point::SetRadius(float newRadius)
{
	if(newRadius > 0) {
		myRadius = newRadius;
		return true;
	} else return false;
}

bool Point::SetMass(float newMass)
{
	// Tests...
	myMass = newMass;
	return true;
}

bool Point::ApplyForce(Vec2 Force, float threshold)
{
	if (!myFixe && Force.GetLength() > threshold) {
		myAcceleration += Force;
		return true;
	} else return false;
}

void Point::ApplyMomentum(float prevdt, float dt)
{
	//if(myFixe) return;
	Vec2 tmp = myPosition;
	//            Dissipation d'énergie, dépend du milieu
	myPosition += 0.99f*((myPosition - myOldPosition)*(dt/prevdt)) // Inertie
	 + myAcceleration*dt*dt; // Accélération
	myOldPosition = tmp;
	myAcceleration = Vec2(0,0);
}


void Point::glDraw()
{
	int quality(16);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(myPosition.x, myPosition.y, 0.f);
	glBegin(GL_TRIANGLE_FAN);
	//centre du cercle
	glVertex2f(0.f, 0.f);
	for (int i=0; i<=quality; i++)
	{
		(myFixe) ? glColor3f(1.f, 0.2f, 0.2f) : glColor3f(1.f, 1.f, 1.f);
		glVertex2f(myMass*4.0*cos((2.0*M_PI)*(i/static_cast<double>(quality))), myMass*4.0*sin((2.0*M_PI)*(i/static_cast<double>(quality))));
	}

	glEnd();
	glPopMatrix();
}

void Point::DrawAll()
{
	for (std::list<Point*>::iterator it=List.begin(); it!=List.end(); it++)
		(*it)->glDraw();
}



Point* Point::GetNearest(const Vec2 &v)
{
	if (List.size()<=0)
		return NULL;

	std::list<Point*>::iterator it(List.begin());
	Point* P((*it)); it++;
	// Longueur au carré, fonction^2 strictement croissante... Plus rapide à calculer
	float dis = (P->GetPosition() - v)*(P->GetPosition() - v), tmp;
	while(it!=List.end())
	{
		tmp = ((*it)->GetPosition() - v)*((*it)->GetPosition() - v);
		if (dis > tmp)
		{
			dis = tmp;
			P = (*it);
		}
		it++;
	}
	return P;
}

}
