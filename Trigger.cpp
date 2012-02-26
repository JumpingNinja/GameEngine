//
//  Trigger.cpp
//  GameEngine
//
//  Created by Edu San Martin Morote on 26/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//

#include <cstdlib>

#include "Trigger.h"

std::list<TriggerImpl*> TriggerImpl::list;

void TriggerImpl::UpdateAll(float timerate)
{
	for (std::list<TriggerImpl*>::iterator it=list.begin(); it!=list.end(); it++)
	{
		TriggerImpl* temp_ptr;
		(*it)->Update(timerate);
		if ((*it)->myDestroy)
			temp_ptr = (*it), --it, delete temp_ptr, temp_ptr = NULL;
	}
}

void TriggerImpl::DestroyAll()
{
	while (list.size()>0)
        delete (list.front());
}

TriggerImpl::TriggerImpl(int times) : myTimesToBeLaunched(times), myDestroy(0)
{
	list.push_back(this);
}

TriggerImpl::~TriggerImpl()
{
	list.remove(this);
}
