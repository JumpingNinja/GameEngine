#include "PhysicsRectangle.h"

namespace Physics
{

Rectangle::Rectangle(float Width, float Height) :
	Polygon(4, FLAG_NULL, new Point(0.f, 0.f), new Point(Width, 0.f), new Point(Width, Height), new Point(0.f, Height))
{
}

Rectangle::Rectangle(float Width, float Height, float Mass) :
	Polygon(4, FLAG_NULL, new Point(0.f, 0.f, Mass), new Point(Width, 0.f, Mass), new Point(Width, Height, Mass), new Point(0.f, Height, Mass))
{
}

Rectangle::Rectangle(float Width, float Height, float Mass1, float Mass2, float Mass3, float Mass4) :
	Polygon(4, FLAG_NULL, new Point(0.f, 0.f, Mass1), new Point(Width, 0.f, Mass2), new Point(Width, Height, Mass3), new Point(0.f, Height, Mass4))
{
}

}
