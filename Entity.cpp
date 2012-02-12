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
std::list<Entity*>::iterator Entity::it;
short Entity::maxDepth(0), Entity::minDepth(0);


Entity::Entity() : sf::Sprite(), myIsVisible(1), myDestroy(0), myDepth(0), myKind(kEK_Any), myBlendMode(sf::BlendNone)
{
	Entity::it = Entity::list.begin();
	while(Entity::it != Entity::list.end() && myDepth<(*Entity::it)->myDepth)
		Entity::it++;
    
	Entity::list.insert(Entity::it, this);
}

Entity::Entity(short Depth) : sf::Sprite(),  myIsVisible(1), myDestroy(0), myDepth(Depth), myKind(kEK_Any), myBlendMode(sf::BlendNone)
{
    if (Depth<minDepth)
        minDepth=Depth;
    if (Depth>maxDepth)
        maxDepth=Depth;
    
	Entity::it = Entity::list.begin();
	while(Entity::it != Entity::list.end() && myDepth<(*Entity::it)->myDepth)
		Entity::it++;

	Entity::list.insert(Entity::it, this);
}

Entity::~Entity()
{
    for (Entity::it=Entity::list.begin(); Entity::it!=Entity::list.end(); Entity::it++)
    {
        if ((*Entity::it)==this)
            break;
    }
    
    if ((*Entity::it)==this)
        Entity::list.erase(Entity::it);

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
	for(Entity::it = Entity::list.begin(); Entity::it != Entity::list.end(); Entity::it++)
    {
        if ((*Entity::it)->myIsVisible)
		{
			if ((*Entity::it)->myBlendMode==sf::BlendNone)
				window.Draw(**Entity::it);
			else
				window.Draw(**Entity::it, sf::RenderStates((*Entity::it)->myBlendMode));
		}
            
        if ((*Entity::it)->myDestroy)
            delete (*Entity::it), it--;
            
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
    Entity::it = Entity::list.begin();
	while((*Entity::it) != this) //ICI ON SUPPOSE QUE L'élement est déjà dans la liste!!
		Entity::it++;
    Entity::list.erase(Entity::it);
    
    //Et on le replace
	Entity::it = Entity::list.begin();
	while(Entity::it != Entity::list.end() && myDepth<(*Entity::it)->myDepth)
		Entity::it++;
    
	Entity::list.insert(Entity::it, this);
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
