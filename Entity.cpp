//
//  Entity.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Entity.h"
#include <iostream>


std::list<Entity*> Entity::list;
short Entity::maxDepth(0), Entity::minDepth(0);


Entity::Entity() : sf::Sprite(), myIsVisible(1), myDestroy(0), myDepth(0), myKind(kEK_Any), myBlendMode(sf::BlendNone)
{
	std::list<Entity*>::iterator ite = Entity::list.begin();
	while(ite != Entity::list.end() && myDepth<(*ite)->myDepth+1)
		ite++;

	Entity::list.insert(ite, this);
}

Entity::Entity(short Depth) : sf::Sprite(),  myIsVisible(1), myDestroy(0), myDepth(Depth), myKind(kEK_Any), myBlendMode(sf::BlendNone)
{
    if (Depth<minDepth)
        minDepth=Depth;
    if (Depth>maxDepth)
        maxDepth=Depth;

	std::list<Entity*>::iterator ite = Entity::list.begin();
	while(ite != Entity::list.end() && myDepth<(*ite)->myDepth+1)
		ite++;

	Entity::list.insert(ite, this);
}

Entity::~Entity()
{
	Entity::list.remove(this);
}

void Entity::DestroyAll()
{
    while (Entity::list.size()>0)
        delete (list.front());
}

void Entity::DrawAll(sf::RenderTarget &window)
{
    sf::Clock clock;
    clock.Restart();
    Entity* temp_ptr;
    std::list<Entity*>::iterator ite;
	for(ite = Entity::list.begin(); ite != Entity::list.end(); ite++)
    {
        //std::cerr << &(*Entity::list.begin()) << " " << &(*ite) << " " << &(*Entity::list.end()) << " " << Entity::list.size() << std::endl;
        if ((*ite)->myIsVisible)
		{
			if ((*ite)->myBlendMode==sf::BlendNone)
				window.Draw(**ite);
			else
				window.Draw(**ite, sf::RenderStates((*ite)->myBlendMode));
		}

        if ((*ite)->myDestroy)
            //std::cerr << "Deleted " << &(*ite) << std::endl, ite = ite, ite--, delete (*ite), ite = ite, std::cerr << "Next step " << &(*ite) << std::endl;
            temp_ptr = (*ite), --ite, delete temp_ptr, temp_ptr = NULL;
    }
}

void Entity::SetDepth(short Depth)
{
    if (Depth<minDepth)
        minDepth=Depth;
    if (Depth>maxDepth)
        maxDepth=Depth;

    myDepth=Depth;

    //On l'enlève de la liste
    std::list<Entity*>::iterator ite = Entity::list.begin();
	while((*ite) != this) //ICI ON SUPPOSE QUE L'élement est déjà dans la liste!!
		ite++;
    Entity::list.erase(ite);

    //Et on le replace
	ite = Entity::list.begin();
	while(ite != Entity::list.end() && myDepth<(*ite)->myDepth)
		ite++;

	Entity::list.insert(ite, this);
}

short Entity::GetDepth() const
{
    return myDepth;
}

void Entity::SetVisible(bool Visible)
{
    myIsVisible=Visible;
}

bool Entity::GetVisible() const
{
    return myIsVisible;
}

void Entity::SetAlpha(sf::Uint8 alpha)
{
    SetColor(sf::Color(GetColor().r, GetColor().g, GetColor().b, alpha));
}

sf::Uint8 Entity::GetAlpha() const
{
    return GetColor().a;
}
