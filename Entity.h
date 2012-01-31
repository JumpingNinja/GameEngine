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
#include <iostream>

/**
 L'idée du depth: la profondeur où se trouve lobjet deétermine quand il est dessiné. Plus la profondeur est petite avant il est dessiné.
 Deux options:
    @li gerer tout dans la même liste et faire un while sur la liste qui dessine et parcour toute la liste plusieurs fois
    @li gerer dans des listes separes ordonnés en croissant dans une autre liste contenants toutes ces listes
    @li gerer dans une seule liste triée et faire chaque insert à sa bonne place pour quelle soit toujours triée
 
 La @b troisème méthode semble la plus efficace, c'est celle qui a été implémentée.
**/

/**
 @brief Class pour gérer une entité
 
 Cette classe est abstraite, il faut l'hériter pour l'utiliser et redéfinir le constructeur et destructeur obligatoirement. Elle a une liste static à reimplementer chaque fois si nécessaire (ex pour grouper des objets comme les objets de physiques, les bullets, les ennemis etc) d'appliquer une action a un groupe d'objets
 Voilà un exemple d'utilisation:
 @code
 MyClass.h
 
 #include "Entity.h"
 
 class MyClass : public Entity {
    static std::vector<MyClass*> list;
    static std::vector<MyClass*>::iterator it;
public:
    MyClass(short Depth);
    MyClass();
    virtual ~MyClass();
 };
 
 MyClass.cpp

#include "MyClass.h"

std::vector<MyClass*> MyClass::list;
std::vector<MyClass*>::iterator MyClass::it;

MyClass::MyClass(short Depth) : Entity::Entity(Depth)
{ 
    //Ici pas besoin d'ordre
    MyClass::list.push_back(this);
}

MyClass::MyClass() : Entity::Entity(3) //Depth par défaut de la classe. Très utile!
{ 
    //Ici pas besoin d'ordre
    MyClass::list.push_back(this);
}

MyClass::~MyClass()
{
    for ( MyClass::it=MyClass::list.begin(); MyClass::it!=MyClass::list.end(); MyClass::it++)
    {
        if ((*MyClass::it)==this)
            break;
    }
    
    if ((*MyClass::it)==this)
        MyClass::list.erase(MyClass::it);
    
    //Entity destructor called implicetly
}
 @endcode
 
**/

class Entity : public sf::Sprite {
private:
    static std::vector<Entity*> list;
    static std::vector<Entity*>::iterator it;
    static short maxDepth, minDepth;
protected:
    bool myIsVisible;
    short myDepth;
    
public:
    virtual ~Entity();//=0; pou abstraite
    ///@brief Contructeur, UTILISER PLUTOT new Entity
    Entity();
    /**
     @brief Contructeur avec profondeur de l'entité
     @param aDepth Profondeur. D'abord sont dessinés les entités ayant une profondeur haute, puis par dessus sont dessinés es entités avec une plus petite densité
     **/
    Entity(short Depth);
    /**
     @brief Contructeur avec texture
     @param Texture Texture à appliquer.
     **/
    Entity(sf::Texture Texture);
    /**
     @brief Contructeur avec texture et profondeur
     @param Texture Texture à appliquer.
     @param aDepth Profondeur. D'abord sont dessinés les entités ayant une profondeur haute, puis par dessus sont dessinés es entités avec une plus petite densité
     **/
    Entity(sf::Texture Texture, short aDepth);
    
    ///@brief Détruit tous les objets manuellement (Déallocation manuelle). Normalement tout est géré automatiquement
    static void DestroyAll();
    
    /**
     @brief Déssine les entités à leur position selon leur depth (fenetre ou texture, d'où le renderTarget)
     @param window Cible où doit être dessinée l'entité
     **/
    static void DrawAll(sf::RenderTarget &window);
    
    ///@brief Change la profondeur de l'entité
    ///@param Depth nouvelle profondeur
    void SetDepth(short Depth);
    ///@brief Lit la profondeur de l'entité
    ///@return retourne la profondeur profondeur
    short GetDepth() const;
    ///@brief Modifie la visibilité de l'entité
    ///@param aVisible Défini si l'entité doit être dessinée ou pas
    void SetVisible(bool Visible);
    ///@brief Retourne la visibilité de l'entité
    ///@return retourne la visibilté de l'entité
    bool GetVisible() const;
    

};