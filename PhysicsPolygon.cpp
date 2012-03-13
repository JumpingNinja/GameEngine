#include "PhysicsPolygon.h"

//#include <assert.h>
#include <iostream>

#define FORMINSEARCH 10000000.0

namespace Physics
{

std::list<Polygon*> Polygon::List;

Polygon::Polygon()
{
	Polygon::List.push_back(this);
}

Polygon::Polygon(int nb, unsigned int FLAGS, ...)
{
	va_list ap;
	va_start(ap, FLAGS);

	Vertices.reserve(nb);
	Edges.reserve(nb);

	if(FLAGS==FLAG_NULL)
	{
		InternContraints.reserve((nb-2)*(nb-3)/2 + 1);

		for(int i = 0; i < nb; i++)
			Vertices.push_back(va_arg(ap, Vertex*));
		for(int i = 0; i < nb; i++)
		{
			Edges.push_back(new Rigid(Vertices[i], Vertices[(i+1)%nb]));
            for(int j = i + 2; j < nb - (i==0?1:0); j++)
                InternContraints.push_back(new Rigid(Vertices[i], Vertices[j]));
		}

	} else if(FLAGS & WITH_LENGTH) {
		std::vector<float> Lengths;
		Lengths.reserve(nb);
		Edges.reserve(nb);
		for(int i = 0; i < nb; i++)
			Vertices.push_back(va_arg(ap, Vertex*)),
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

void Polygon::HandleCollisions()
{
	CollisionInfo Info;
	for(std::list<Polygon*>::iterator ite = Polygon::List.begin();
		ite != Polygon::List.end(); ite++)
	{
		//std::list<Polygon*>::iterator ite2 = ite;
		//ite2++;
		//while(ite2 != Polygon::List.end())
		for(std::list<Polygon*>::iterator ite2 = Polygon::List.begin(); ite2 != Polygon::List.end(); ite2++)
		{
			if( ite != ite2 ) {
				Info = (*ite)->Collide((*ite2));
				if(Info.P1 != 0) // Il y a collision
				{
					// On s'assure que la normal est dans le bon sens (pointe vers P1)
					if(Info.Normal*(Info.P2->GetCenter() - Info.P1->GetCenter()) < 0)
						Info.Normal *= -1;

					// Recherche du point de collision (=le plus proche de P1)
					float distP1Vertex = FORMINSEARCH; // On recherche un minimum
					Vec2 P1Center = Info.P1->GetCenter();
					float tmpDist;
					for(unsigned int i = 0; i < Info.P2->Vertices.size(); i++)
					{
						tmpDist = Info.Normal*(Info.P2->Vertices[i]->GetPosition()-P1Center);
						if(tmpDist < distP1Vertex)
							distP1Vertex = tmpDist,
							Info.P = Info.P2->Vertices[i];
					}

					// Réponse
					Vec2 CollisionVector = Info.Normal*Info.Depth;

					Vec2 PosE1 = Info.Edge->GetP1()->GetPosition();
					Vec2 PosE2 = Info.Edge->GetP2()->GetPosition();

					float PositionOnEdge; // Position du point sur la face
					// On évite les divisions par 0 !
					if(std::abs(PosE1.x - PosE2.x) > std::abs(PosE1.y - PosE2.y))
						PositionOnEdge = (Info.P->GetPosition().x - CollisionVector.x
						- PosE1.x)/(PosE2.x - PosE1.x);
					else
						PositionOnEdge = (Info.P->GetPosition().y - CollisionVector.y
						- PosE1.y)/(PosE2.y - PosE1.y);

					float CorrectionFactor = -1.0f/(PositionOnEdge*PositionOnEdge + (1 - PositionOnEdge)*(1 - PositionOnEdge));

					// Correction des positions
					Info.P->CorrectPosition(CollisionVector*0.5f); // Du point
					// De  la face
					Info.Edge->GetP1()->CorrectPosition(CollisionVector*
						CorrectionFactor*(1-PositionOnEdge)*0.5f);
					Info.Edge->GetP2()->CorrectPosition(CollisionVector*
						CorrectionFactor*(PositionOnEdge)*0.5f);
				}
			}
		}
    }
}

Vec2 Polygon::GetCenter()
{
	Vec2 Center(Vertices[0]->GetPosition());
	for(unsigned int i = 1; i < Vertices.size(); i++)
	{
		Center += Vertices[i]->GetPosition();
	}
	return Center/Vertices.size();
}

Vec2 Polygon::GetMassCenter()
{
	float Mass = Vertices[0]->GetMass();
	Vec2 Center(Vertices[0]->GetPosition());
	for(unsigned int i = 1; i < Vertices.size(); i++)
	{
		Center = (Vertices[i]->GetPosition()*Vertices[i]->GetMass()
					+ Center*Mass)/(Mass + Vertices[i]->GetMass());
		Mass += Vertices[i]->GetMass();
	}
	return Center;
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

        // Si la face est "nulle", on n'essaye pas de la tester !
        if(Edge->GetVector() == Vec2(0.f, 0.f)) continue;

		Axis = Edge->GetVector().GetPerpendicular().GetNormalized();

		ProjectToAxis(Min, Max, Axis);
		P->ProjectToAxis(MinP, MaxP, Axis);

		if(Min < MinP)
			Gap = MinP - Max;
		else Gap = Min - MaxP;

		if (Gap > 0) return CollisionInfo(); // Pas de collision

		if(std::abs(Gap) < Info.Depth)
			Info.Depth = std::abs(Gap),
			Info.Normal = Axis,
			Info.Edge = Edge;

        // Debug
	    //if(Info.Edge == NULL)
        //    std::cout << "Min Max MinP MaxP Gap : " << Min << " " << Max << " " << MinP << " " << MaxP << " " << Gap << std::endl;
	}

	// Gère le cas où le polygone se résume à un point (Tout ses points ont les mêmes coordonnées
	if(Info.Edge == NULL)
        return CollisionInfo();
	else //std::cout << "Collision !" << Info.Depth << std::endl;
        return Info;
}

void Polygon::ProjectToAxis(float &Min, float &Max, const Vec2 Axis)
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

void Polygon::ApplyForce(Vec2 V)
{
	for(int i = 0; i < Vertices.size(); i++)
	{
		Vertices[i]->ApplyForce(V);
	}
}

}
