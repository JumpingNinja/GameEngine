//
//  Entity.cpp
//  Game Engine Template
//
//  Created by Edu San Martin Morote on 28/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Entity.h"
#include <iostream>

template <class T> const T& max ( const T& a, const T& b ) {
    return (a<b)?b:a;     // or: return comp(a,b)?b:a; for the comp version
}

std::list<Entity*> Entity::list;
std::list<Entity*>::iterator Entity::it;
short Entity::maxDepth(0), Entity::minDepth(0);


Entity::Entity() : sf::Sprite(), myIsVisible(1), myDepth(0)
{
	Entity::it = Entity::list.begin();
	while(Entity::it != Entity::list.end() && myDepth<(*Entity::it)->myDepth)
		Entity::it++;
    
	Entity::list.insert(Entity::it, this);
}

Entity::Entity(short Depth) : sf::Sprite(), myIsVisible(1), myDepth(Depth)
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
		if ((*Entity::it)->myIsVisible)
            window.Draw(**Entity::it);// std::cout << "Drawn depth: " << (*it)->myDepth << std::endl;
	/*
    unsigned int nDrawn(0);
    short currentDepth(maxDepth), nextDepth(maxDepth);
    while (nDrawn<list.size())
    {
        currentDepth=nextDepth;
        nextDepth=minDepth; //la plus basse profondeur
        for (it=list.begin(); it!=list.end(); it++)
        {
            if ((*it)->myDepth==currentDepth)
            {
                if ((*it)->myIsVisible)
                    window.Draw(**it);
                nDrawn++;
            }
            if ((*it)->myDepth<currentDepth) //Cette profondeur n'a pas encore été dessinné
                nextDepth=max(nextDepth, (*it)->myDepth); //On prend la profondeur plus grande non dessinnée
        }
        //std::cout<<"Drawn depth: "<<currentDepth<<std::endl;
    }
	*/
    //std::cout<<"Time to draw: "<<clock.GetElapsedTime().AsMicroseconds()<<" millisenconds\n";
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
