#include "PhysicsConstraint.h"
#include <iostream>

std::list<Constraint*> Constraint::list;

Constraint::Constraint(Point* P1, Point* P2, float Length) :
								P1(P1), P2(P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = (P1->GetPosition() - P2->GetPosition()).GetLength();
	
	list.push_back(this);
}

Constraint::Constraint(Point &P1, Point &P2, float Length) :
								P1(&P1), P2(&P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = (P1.GetPosition() - P2.GetPosition()).GetLength();
	
	list.push_back(this);
}

Constraint::~Constraint()
{
	list.remove(this);
}


void Constraint::glDraw()
{
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	glColor3f(0.f, 0.f, 1.f);
	glVertex2f(P1->GetPosition().x, P1->GetPosition().y);
	glVertex2f(P2->GetPosition().x, P2->GetPosition().y);
	glEnd();
	glPopMatrix();
}

void Constraint::DrawAll()
{
	for (std::list<Constraint*>::iterator it=list.begin(); it!=list.end(); it++)
		(*it)->glDraw();
}