//
//  CollisionGrid.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 31/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "GridCell.h"
#include <vector>

///@brief Contient les cellules et permet d'associer les entity à des cellules pour savoir quelles collisions doivent être faites
///
///L'idée est que cette grille aloue les cellules nécessaires selon la taille de l'écran spécifié en paramètres. Il assignent aux cellules les entity. Celles-ci demandent d'être ajouté lorsqu'elles aparaissent ou changent de position. Le doute est savoir comment est communiqué l'information de qui est près d'une entité, l'entite contient une liste avec les cellules ou il se trouve? Collision grid peut avoir une liste qu'il rempli sur demande dune entite de pointeurs sur cellules, ainsi les entites peuvent demander leurs cellule et avori accès à tous les autre sentites ou faire collision

class CollisionGrid {
    //static GridCell **grid;
    static std::vector< std::vector<GridCell*> > grid;
    static bool ready;
    static float hCells, vCells;
    static sf::FloatRect gridRect;
public:
    static std::list<GridCell*> accessList;
    ///@brief Assignent les cellules a une entite
    ///
    ///Cette fonction est censé être appelé lorsque ins a été déplacée
    ///@param ins Entite
    ///@param createList si vrai, cree la liste des cellules contenant cette instance pour être utilisée après cet appel par l'instance
    static void AssignCells(CollisionEntity* ins, const bool &createList=1);
    ///@brief Cree et initialise un grille
    ///@param width longueur en pixels de la grille
    ///@param height hauteur en pixels de la grille
    static void CreateGrid(const float & width, const float & height);
    ///@brief libère l'espace mémoire de la grille
    static void DestroyGrid();
    ///@brief Ajoute manuellement les cellules dans la liste 
    ///
    ///Normalement l'appel à cet fonction est innécessaire car AssignCells fait déjà ce remplissage; 
    static void GetCells(CollisionEntity* ins);

};