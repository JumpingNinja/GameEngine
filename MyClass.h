//
//  MyClass.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 29/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "Entity.h"

///@brief Exemple de classe (qui forme un groupe) hérité d'entité

class MyClass : public Entity {
    ///@brief Vector où sont stockés des pointeurs sur les instances
    static std::list<MyClass*> list;
    static std::list<MyClass*>::iterator it;
public:
    ///@brief Constructeur avec Depth
    ///@param Depth profondeur
    MyClass(short Depth);
    MyClass();
    virtual ~MyClass();
};
