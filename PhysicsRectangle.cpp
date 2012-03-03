#include "PhysicsRectangle.h"

#include <iostream>

namespace Physics
{

Rectangle::Rectangle(float Width, float Height)
{
	Vertices.reserve(4);
	Edges.reserve(4);

	try
	{
		this->Vertices[0] = new Point(0.f, 0.f);
		this->Vertices[1] = new Point(Width, 0.f);
		this->Vertices[2] = new Point(Width, Height);
		this->Vertices[3] = new Point(0.f, Height);
		std::cout << this->Vertices[0] << " " << this->Vertices[1] << " " << this->Vertices[2] << " " << this->Vertices[3] << std::endl;
	}
	catch ( const std::bad_alloc & )
	{
		delete this->Vertices[0];
		delete this->Vertices[1];
		delete this->Vertices[2];
		throw;
	}

	for(int i = 0; i < 4; i++)
		Edges.push_back(new Rigid(Vertices[i], Vertices[(i+1)%4]));

	InternContraints.reserve(4); // C'est trop ! (Double)
	for(int i = 0; i < 3; i++)
		InternContraints.push_back(new Rigid(Vertices[i], Vertices[(i+2)%4]));
}

Rectangle::Rectangle(float Width, float Height, float Mass) :
	Polygon(4, FLAG_NULL, new Point(0.f, 0.f, Mass), new Point(Width, 0.f, Mass), new Point(Width, Height, Mass), new Point(0.f, Height, Mass))
{
}

Rectangle::Rectangle(float Width, float Height, float Mass1, float Mass2, float Mass3, float Mass4) :
	Polygon(4, FLAG_NULL, new Point(0.f, 0.f, Mass1), new Point(Width, 0.f, Mass2), new Point(Width, Height, Mass3), new Point(0.f, Height, Mass4))
{
}

Point& Rectangle::GetTopLeft()
{
	return *(Vertices[0]);
}

}
