//
//  MyClass.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 29/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

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
