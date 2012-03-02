#include "PhysicsPoint.h"

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

Point::~Point()
{
	Point::List.remove(this);
}

void Point::UpdateAll(float prevdt, float dt)
{
	for(std::list<Point*>::iterator ite = Point::List.begin();
		ite != Point::List.end(); ite++)
		(*ite)->ApplyMomentum(prevdt, dt);
}

void Point::ForceAll(Vec2 Force)
{
	for(std::list<Point*>::iterator ite = Point::List.begin();
		ite != Point::List.end(); ite++)
		(*ite)->ApplyForce(Force);
}

void Point::DeleteAll()
{
    while (Point::List.size()>0)
        delete (Point::List.front());
}

bool Point::SetPosition(Vec2 newPos, bool oldToo)
{
	//if(myFixe) return false;
	myPosition = newPos;
	if(oldToo) myOldPosition = newPos;
	return true;
}

bool Point::CorrectPosition(Vec2 add)
{
	//if(myFixe) return false;
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
	glColor3f(1.f, 1.f, 1.f);
	//centre du cercle
	glVertex2f(0.f, 0.f);
	for (int i=0; i<=quality; i++)
		glVertex2f(myMass*4.0*cos((2.0*M_PI)*(i/static_cast<double>(quality))), myMass*4.0*sin((2.0*M_PI)*(i/static_cast<double>(quality))));
	
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
	
	std::list<Point*>::iterator it(List.begin()); Point* P((*it));
	float dis((P->GetPosition()-v).GetLength());
	for (std::list<Point*>::iterator it=List.begin(); it!=List.end(); it++)
	{
		if (dis>((*it)->GetPosition()-v).GetLength())
		{
			dis=((*it)->GetPosition()-v).GetLength();
			P=(*it);
		}
	}
	return P;
}