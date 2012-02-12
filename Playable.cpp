//
//  Playable.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 12/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include "Playable.h"

bool Playable::IsControled() const
{ return myControled; }

void Playable::SetControled(bool aControled)
{ myControled = aControled; }

Playable::Playable() : myControled(1)
{}

Playable::Playable(bool aControled) : myControled(aControled)
{}

Playable::~Playable()
{}