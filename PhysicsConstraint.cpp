#include "PhysicsConstraint.h"
#include <iostream>

namespace Physics
{

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

void Constraint::DrawAll()
{
	for (std::list<Constraint*>::iterator it=list.begin(); it!=list.end(); it++)
		(*it)->glDraw();
}

}
