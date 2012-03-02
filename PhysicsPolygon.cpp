#include "PhysicsPolygon.h"
#include <iostream>

#define FORMINSEARCH 10000.0

std::list<Polygon*> Polygon::List;

Polygon::Polygon(int nb, unsigned int FLAGS, ...)
{
	va_list ap;
	va_start(ap, FLAGS);

	Vertices.reserve(nb);
	Edges.reserve(nb);

	if(FLAGS==FLAG_NULL)
	{
		for(int i = 0; i < nb; i++)
			Vertices.push_back(va_arg(ap, Point*));
		for(int i = 0; i < nb; i++)
			Edges.push_back(new Rigid(Vertices[i], Vertices[(i+1)%nb]));
		std::cout<<"Flag Null\n";

	} else if(FLAGS==WITH_LENGTH) {
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

#include <iostream>

void Polygon::HandleCollisions()
{
	CollisionInfo Info;
	for(std::list<Polygon*>::iterator ite = Polygon::List.begin();
		ite != Polygon::List.end(); ite++)
	{
		std::list<Polygon*>::iterator ite2 = ite;
		ite2++;
		while(ite2 != Polygon::List.end())
		{
			Info = (*ite)->Collide((*ite2));
			if(Info.P1 != 0) // Il y a collision
			{
				if(Info.Normal*((*ite)->GetCenter() - (*ite2)->GetCenter()) < 0)
					Info.Normal *= -1;

				// Recherche du point de collision (le plus proche de P2)
				float distP2Point = FORMINSEARCH; // On recherche un minimum
				float tmpDist;
				for(unsigned int i = 0; i < (*ite)->Vertices.size(); i++)
				{
					tmpDist = Info.Normal*((*ite)->Vertices[i]->GetPosition()-(*ite2)->GetCenter());
					if(tmpDist < distP2Point)
						distP2Point = tmpDist,
						Info.P = (*ite)->Vertices[i];
				}

				// Réponse
				Vec2 CollisionVector = Info.Normal*Info.Depth*0.5f;

				Info.P->CorrectPosition(CollisionVector); // Du point

				Vec2 PosE1 = Info.Edge->GetP1()->GetPosition();
				Vec2 PosE2 = Info.Edge->GetP2()->GetPosition();

				// Des points de la face
				float PositionOnEdge; // Position du point sur la face
				if(std::abs(PosE1.x - PosE2.x) > std::abs(PosE1.y - PosE2.y))
					PositionOnEdge = (Info.P->GetPosition().x - CollisionVector.x
					- PosE1.x)/(PosE2.x - PosE1.x);
				else
					PositionOnEdge = (Info.P->GetPosition().y - CollisionVector.y
					- PosE1.y)/(PosE2.y - PosE1.y);

				float CorrectionFactor = -1.0f/(PositionOnEdge*PositionOnEdge +
						(1 - PositionOnEdge)*(1 - PositionOnEdge));

				Info.Edge->GetP1()->CorrectPosition(CollisionVector*
					CorrectionFactor*(1-PositionOnEdge));
				Info.Edge->GetP2()->CorrectPosition(CollisionVector*
					CorrectionFactor*PositionOnEdge);
			}
			ite2++;
		}
    }
}

Vec2 Polygon::GetCenter()
{
	Vec2 Center(0,0);
	for(unsigned int i = 0; i < Vertices.size(); i++)
	{
		Center += Vertices[i]->GetPosition();
	}
	return Center/Vertices.size();
}

CollisionInfo Polygon::Collide(Polygon* P)
{
	Vec2 Axis;
	Rigid* Edge;
	CollisionInfo Info;
	Info.P1 = this;
	Info.P2 = P;
	Info.Depth = FORMINSEARCH; // Pour le minimum
	float Min, Max, MinP, MaxP, Gap; // Valeur des projections, distance

	for(unsigned int i = 0; i < Edges.size() + P->Edges.size(); i++)
	{
		if(i < Edges.size())
			Edge = Edges[i];
		else Edge = P->Edges[i - Edges.size()], Info.P1 = P, Info.P2 = this;
		// P1 est toujours le polygone dont on teste la face

		Axis = Edge->GetVector().GetPerpendicular().GetNormalized();

		ProjectToAxis(Min, Max, Axis);
		P->ProjectToAxis(MinP, MaxP, Axis);

		if(Min < MinP)
			Gap = MinP - Max;
		else Gap = Min - MaxP;

		if (Gap > 0) return CollisionInfo(); // Pas de collision

		if(std::abs(Gap) < Info.Depth)
			Info.Depth = Gap,
			Info.Normal = Axis,
			Info.Edge = Edge;
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
