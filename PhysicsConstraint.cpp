#include "PhysicsConstraint.h"
#include <iostream>

Constraint::Constraint(Point* P1, Point* P2, float Length) :
								P1(P1), P2(P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = (P1->GetPosition() - P2->GetPosition()).GetLength();
}

Constraint::Constraint(Point &P1, Point &P2, float Length) :
								P1(&P1), P2(&P2)
{
	if(Length > 0)
		myLength = Length;
	else
		myLength = (P1.GetPosition() - P2.GetPosition()).GetLength();
}

Constraint::~Constraint()
{
}
