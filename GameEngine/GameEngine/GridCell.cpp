//
//  GridCell.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "GridCell.h"
#include "CollisionEntity.h"

void GridCell::Clear()
{
    myInstances.clear();
}

GridCell::~GridCell()
{
    myInstances.clear();
}

GridCell::GridCell(const float &x, const float & y) : BBox(sf::FloatRect(x, y, CellSize, CellSize))
{}

GridCell::GridCell() : BBox(sf::FloatRect(0, 0, CellSize, CellSize))
{}

void GridCell::SetPosition(const float &x, const float &y)
{
    BBox.Left=x;
    BBox.Top=y;
}

void GridCell::AddInstance(CollisionEntity *ins)
{
    //check if it is on the list
    for (std::list<CollisionEntity*>::iterator it(myInstances.begin()); it!=myInstances.end(); it++)
        if ((*it)==ins)
            return;
    myInstances.push_back(ins);
}

void GridCell::Update()
{
    for (std::list<CollisionEntity*>::iterator it(myInstances.begin()); it!=myInstances.end(); it++)
    {
        if (!(*it)->IsSolid()) //Pas besoin de faire une mise à jour sur les objets qui ne bougents pas!
        {
            if (!BBox.Intersects((*it)->sf::Sprite::GetGlobalBounds()))
                myInstances.erase(it), it--;
                
        }
    }
}