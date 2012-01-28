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

std::vector<Entity*> Entity::list;
std::vector<Entity*>::iterator Entity::it;
short Entity::maxDepth(0), Entity::minDepth(0);


Entity::Entity() :myIsVisible(1), myDepth(0)
{
	it = list.begin();
	while((it != list.end())&&((*it)->myDepth < myDepth))
	{
		it++;
	}
	list.insert(it, this);
	
    //list.push_back(this);
    //std::cout<<this<<" added to the Entity List\n";
}

Entity::Entity(short aDepth) :myIsVisible(1), myDepth(aDepth)
{
	it = list.begin();
	while((it != list.end())&&((*it)->myDepth < myDepth))
	{
		it++;
	}
	list.insert(it, this);
	
    //list.push_back(this);
    //std::cout<<this<<" added to the Entity List\n";
}

Entity::~Entity()
{
    for (it=list.begin(); it!=list.end(); it++)
    {
        if ((*it)==this)
            break;
    }
    
    list.erase(it);
    //std::cout<<(*it)<<" erased from the Entity List. Now list size is :"<<list.size()<<"\n";
}

void Entity::DestroyAll()
{
    while (list.size()>0)
        delete list[0];
}

void Entity::DrawAll(sf::RenderTarget &window)
{
    sf::Clock clock;
    clock.Restart();
	for(it = list.begin(); it != list.end; it++)
		if ((*it)->myIsVisible) window.Draw(**it), std::cout << "Drawn depth: " << (*it)->myDepth << std::endl;
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
    std::cout<<"Time to draw: "<<clock.GetElapsedTime().AsMicroseconds()<<" millisenconds\n";
}

void Entity::SetDepth(short aDepth)
{
    if (aDepth<minDepth)
        minDepth=aDepth;
    if (aDepth>maxDepth)
        maxDepth=aDepth;
    
    myDepth=aDepth;
}

short Entity::GetDepth() const
{
    return myDepth;
}

