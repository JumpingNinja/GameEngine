//
//  GridCell.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include <list>
#include <SFML/Graphics/Rect.hpp>

class CollisionEntity;

static const float CellSize(32);
///@brief classe d'une cellule de grille permettant d'optimiser les collisions
///
///Il faut définir une constante comme taille des cellules. Si les objects sont toujours plus petit qu ela taille de la grille l'implémentation est plus facile, ici on va considérer que les élemet peuvent être plus grands qu'une case. Les cellules eliminent automatiquement les instances qui ne sont plus dans elles, cependant ce sont les entités qui doivent se charger de s'ajouter dans la case selon la grille definie en static dans collisionentity. GridCell::Update doit être appelé sur le step

class GridCell {
protected:
    
    sf::FloatRect BBox;
public:
    std::list<CollisionEntity*> myInstances;
    ///@brief Ajoute une instance dans la liste
    ///@param ins pointeur sur un CollisionEntity
    void AddInstance(CollisionEntity* ins);
    ///@brief Fait une mise a jour des instances qui ne sont plus dans cette case
    void Update();
    ///@brief clear the instances pointers stored
    void Clear();
    
    ///@brief Detsructor
    ~GridCell();
    ///@brief Constructor
    ///@param x Top Left position of the cell
    ///@param y Top left position of the cell
    GridCell(const float &x, const float & y);
    ///@brief Constructor
    GridCell();
    ///@brief Change la position
    void SetPosition(const float &x, float const &y);
};