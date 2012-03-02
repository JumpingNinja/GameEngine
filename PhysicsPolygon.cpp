#include "PhysicsPolygon.h"

std::list<Polygon*> Polygon::List;

Polygon::Polygon(int nb, unsigned int FLAGS, ...)
{
	va_list ap;
	va_start(ap, FLAGS);

	Vertices.reserve(nb);
	Edges.reserve(nb);

	if(FLAGS & FLAG_NULL)
	{
		for(int i = 0; i < nb; i++)
			Vertices.push_back(va_arg(ap, Point*));
		for(int i = 0; i < nb; i++)
			Edges.push_back(new Rigid(Vertices[i], Vertices[(i+1)%nb]));

	} else if(FLAGS & WITH_LENGTH) {
		std::vector<float> Lengths;
		Lengths.reserve(nb);
		Edges.reserve(nb);
		for(int i = 0; i < nb; i++)
			Vertices.push_back(va_arg(ap, Point*)),
			Lengths.push_back(static_cast<float>(va_arg(ap, double)));
		for(int i = 0; i < nb; i++)
			Edges.push_back(new Rigid(Vertices[i],
											Vertices[(i+1)%nb],
											Lengths[i]));
	}

	va_end(ap);
	Polygon::List.push_back(this);
}

Polygon::~Polygon()
{
	while(Edges.size() > 0)
		Edges.pop_back(); // Appelle automatiquement le destructeur de l'élément.
	Polygon::List.remove(this);
}

void Polygon::DeleteAll()
{
    while (Polygon::List.size()>0)
        delete (Polygon::List.front());
}

CollisionInfo Polygon::Collide(Polygon* P)
{
	CollisionInfo Info;
	Vec2 Axis;
	float Min, Max, MinP, MaxP, Gap; // Valeur des projections, distance
	for(unsigned int i = 0; i < Edges.size() + P->Edges.size(); i++)
	{
		if(i < Edges.size())
			Axis = Edges[i]->GetVector().GetNormalized();
		else Axis = (*P)[i].GetVector().GetNormalized();

		ProjectToAxis(Min, Max, Axis);
		P->ProjectToAxis(MinP, MaxP, Axis);

		if(Min < MinP)
			Gap = MinP - Max;
		else Gap = Min - MaxP;
		if
	}
	return Info;
}

void Polygon::ProjectToAxis(float &Min, float &Max, Vec2 Axis)
{
	Min = Max = Vertices[0]->GetPosition()*Axis;

	for(unsigned int i = 1; i < Vertices.size(); i++)
	{
		Min = std::min(Vertices[i]->GetPosition()*Axis, Min);
		Max = std::max(Vertices[i]->GetPosition()*Axis, Max);
	}
}

Rigid& Polygon::operator[](const unsigned int i)
{
	return *Edges[i];
}
