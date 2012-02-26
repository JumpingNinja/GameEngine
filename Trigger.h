//
//  Trigger.h
//  GameEngine
//
//  Created by Edu San Martin Morote on 26/02/12.
//  Copyright 2012 Posva Games. All rights reserved.
//
#pragma once
#include <list>

class TriggerImpl {
protected:
	static std::list<TriggerImpl*> list;
	int myTimesToBeLaunched;
	bool myDestroy;
	
public:
	virtual void Launch()=0;
	virtual void Update(float timerate)=0;
	
	TriggerImpl(int times=1);
	virtual ~TriggerImpl();
	
	static void UpdateAll(float timerate);
	static void DestroyAll();
};


template <typename R>
class Trigger : public TriggerImpl {
private:
	

	R(*myFunction)();
	bool(*myCheckFunction)();
	float myTimer, myTime;
	
	enum Type
	{
		Timer,
		Auto,
		Manual
	} myType;

	
public:
	
    Trigger(R(*function)(), int times=1) : TriggerImpl(times), myFunction(function), myTimer(0.f), myTime(0.f), myType(Manual)
	{}
	
	Trigger(R(*function)(), bool(*checkFunction)(), int times=1) : TriggerImpl(times), myFunction(function), myCheckFunction(checkFunction), myTimer(0.f), myTime(0.f), myType(Auto)
	{}
	
	Trigger(R(*function)(), float timer, int times=1) : TriggerImpl(times), myFunction(function), myTimer(timer), myTime(timer), myType(Timer)
	{}
	
	~Trigger()
	{}

	virtual void Launch()
	{
		myFunction();
		
		if (myTimesToBeLaunched>0)
		{	
			--myTimesToBeLaunched;
			if (myTimesToBeLaunched==0)
				myDestroy=1;
		}
	}
	
	
	void Update(float timerate);
	
	
};

typedef Trigger<void> VoidTrigger;


template <typename R>
void Trigger<R>::Update(float timerate)
{
	switch (myType) {
		case Timer:
			myTimer-=timerate;
			if (myTimer<=0.f)
				Launch(), myTimer=myTime;				
			break;
		case Auto:
			if (myCheckFunction())
				Launch();
			break;
		default:
			break;
	}
}