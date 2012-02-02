//
//  CollisionGrid.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "CollisionGrid.h"
#include <cmath>
#include "CollisionEntity.h"
#include <iostream>

template <class T> const T& max ( const T& a, const T& b ) {
    return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

template <class T> const T& min ( const T& a, const T& b ) {
    return (a>b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

//GridCell **CollisionGrid::grid(NULL);
std::vector<std::vector<GridCell*> > CollisionGrid::grid;
bool CollisionGrid::ready(0);
std::list<GridCell*> CollisionGrid::accessList;
float CollisionGrid::hCells(0), CollisionGrid::vCells(0);
sf::FloatRect CollisionGrid::gridRect;

void CollisionGrid::CreateGrid(const float &width, const float &height)
{
    if (ready) return;
    hCells=static_cast<int>(ceilf(width/CellSize)); 
    vCells=static_cast<int>(ceilf(height/CellSize));
    gridRect.Top=0.f;
    gridRect.Left=0.f;
    gridRect.Width=hCells*CellSize;
    gridRect.Height=vCells*CellSize;
    
    grid.resize(hCells);
    
    for (int i=0; i<hCells; i++)
        grid[i].resize(vCells);
    
    for (int i=0; i<hCells; i++)
        for (int j=0; j<vCells; j++)
            grid[i][j]=new GridCell(i*CellSize, j*CellSize);
    
    /*grid= (GridCell**)malloc(sizeof(GridCell**)*w);
    for (int i=0; i<w; i++)
        grid[i]=(GridCell*)malloc(sizeof(GridCell*)*h);*/
    
    
    ready=1;
}

void CollisionGrid::DestroyGrid()
{
    for (int i=0; i<hCells; i++)
        for (int j=0; j<vCells; j++)
            delete grid[i][j];
    
    grid.clear();
    hCells=0;
    vCells=0;
    ready=0;
}

void CollisionGrid::AssignCells(CollisionEntity *ins, const bool &createList)
{
    //Don't add if it's out of the grid
    if (!ins->sf::Sprite::GetGlobalBounds().Intersects(gridRect))
        return;
    //Clear temporary list of cells containing the ins
    if (createList)
    accessList.clear();
    
    //GetGlobalBounds() donne la position du rectangle en tenant compte de la position de l'entite et de son origin
    float topCell(floorf(ins->sf::Sprite::GetGlobalBounds().Top/CellSize)), leftCell(floorf(ins->sf::Sprite::GetGlobalBounds().Left/CellSize)),
    bottomCell(floorf((ins->sf::Sprite::GetGlobalBounds().Top+ins->sf::Sprite::GetGlobalBounds().Height)/CellSize)),
    rightCell(floorf((ins->sf::Sprite::GetGlobalBounds().Left+ins->sf::Sprite::GetGlobalBounds().Width)/CellSize));
    //Limit to the bounds of the grid
    topCell=max(0.f, min(topCell, vCells-1));
    leftCell=max(0.f, min(leftCell, hCells-1));
    rightCell=max(0.f, min(rightCell, hCells-1));
    bottomCell=max(0.f, min(bottomCell, vCells-1));
    
    for (int i=leftCell; i<=rightCell; i++)
        for (int j=topCell; j<=bottomCell; j++)
        {
            grid[i][j]->AddInstance(ins);
            if (createList)
            accessList.push_back(grid[i][j]);
        }
    
}


void CollisionGrid::GetCells(CollisionEntity *ins)
{
    //Don't add if it's out of the grid
    if (!ins->sf::Sprite::GetGlobalBounds().Intersects(gridRect))
        return;
    //Clear temporary list of cells containing the ins
    accessList.clear();
    
    //GetGlobalBounds() donne la position du rectangle en tenant compte de la position de l'entite et de son origin
    float topCell(floorf(ins->sf::Sprite::GetGlobalBounds().Top/CellSize)), leftCell(floorf(ins->sf::Sprite::GetGlobalBounds().Left/CellSize)),
    bottomCell(floorf((ins->sf::Sprite::GetGlobalBounds().Top+ins->sf::Sprite::GetGlobalBounds().Height)/CellSize)),
    rightCell(floorf((ins->sf::Sprite::GetGlobalBounds().Left+ins->sf::Sprite::GetGlobalBounds().Width)/CellSize));
    //Limit to the bounds of the grid
    topCell=max(0.f, min(topCell, vCells-1));
    leftCell=max(0.f, min(leftCell, hCells-1));
    rightCell=max(0.f, min(rightCell, hCells-1));
    bottomCell=max(0.f, min(bottomCell, vCells-1));
    
    for (int i=leftCell; i<=rightCell; i++)
        for (int j=topCell; j<=bottomCell; j++)
        {
            //grid[i][j]->AddInstance(ins);
            accessList.push_back(grid[i][j]);
        }
    
}
