//
//  Entity.h
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 L'idée du depth: la profondeur où se trouve lobjet deétermine quand il est dessiné. Plus la profondeur est petite avant il est dessiné.
 Deux options:
    -gerer tout dans la même liste et faire un while sur la liste qui dessine et parcour toute la liste plusieurs fois
    -gerer dans des listes separes ordonnés en croissant dans une autre liste contenants toutes ces listes
 
 Les deux méthodes sont à tester pour voir laquelle est plus efficace
**/

/**
 @brief Class pour gérer une entité
 
 Cette classe est abstraite, il faut l'hériter pour l'utiliser et redéfinir le constructeur et destructeur obligatoirement. Elle à une liste static à reimplementer chaque fois si nécessaire (ex pour grouper des objets comme les objets de physiques, les bullets, les ennemis etc) d'appliquer une action a un groupe d'objets
**/

class Entity : public sf::Sprite {
protected:
    static std::vector<Entity*> list;
    static std::vector<Entity*>::iterator it;
    static short maxDepth, minDepth;
    
    bool myIsVisible;
    short myDepth;
    
public:
    virtual ~Entity();
    Entity();
    
    ///@brief Détruit tous les objets manuellement (Déallocation manuelle). Normalement tout est géré automatiquement
    static void DestroyAll();
    
    /**
     @brief Déssine les entités à leur position selon leur depth (fenetre ou texture, d'où le renderTarget)
     @param window Cible où doit être dessinée l'entité
     **/
    static void DrawAll(sf::RenderTarget &window);
    
    ///@brief Change la profondeur de l'entité
    ///@param aDepth nouvelle profondeur
    void SetDepth(short aDepth);
    ///@brief Lit la profondeur de l'entité
    ///@return retourne la profondeur profondeur
    short GetDepth() const;

};