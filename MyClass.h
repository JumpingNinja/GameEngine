//
//  MyClass.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 29/01/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once

#include "Entity.h"

class MyClass : public Entity {
    static std::vector<MyClass*> list;
    static std::vector<MyClass*>::iterator it;
public:
    MyClass(short Depth);
    MyClass();
    virtual ~MyClass();
};
