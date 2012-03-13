#include "PhysicsRectangle.h"

namespace Physics
{

Rectangle::Rectangle(float Width, float Height) :
	Polygon(4, FLAG_NULL, new Vertex(0.f, 0.f), new Vertex(Width, 0.f), new Vertex(Width, Height), new Vertex(0.f, Height))
{
}

Rectangle::Rectangle(float Width, float Height, float Mass) :
	Polygon(4, FLAG_NULL, new Vertex(0.f, 0.f, Mass), new Vertex(Width, 0.f, Mass), new Vertex(Width, Height, Mass), new Vertex(0.f, Height, Mass))
{
}

Rectangle::Rectangle(float Width, float Height, float Mass1, float Mass2, float Mass3, float Mass4) :
	Polygon(4, FLAG_NULL, new Vertex(0.f, 0.f, Mass1), new Vertex(Width, 0.f, Mass2), new Vertex(Width, Height, Mass3), new Vertex(0.f, Height, Mass4))
{
}

Vertex& Rectangle::GetTopLeft()
{
	return *(Vertices[0]);
}

void Rectangle::SetFixed()
{
	for (std::vector<Vertex*>::iterator it=Vertices.begin(); it!=Vertices.end(); it++)
		(*it)->SetFixe();
}

}

