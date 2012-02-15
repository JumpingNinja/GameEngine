#include "Input.h"

std::map<gb::Key, InputStatus*> InputStatus::map;

InputStatus::InputStatus(gb::Key Key) : myIsKeyPressed(0), myJustPressed(0), myJustReleased(0)
{
	InputStatus::map[Key] = this;
}

InputStatus::~InputStatus()
{
	std::map<gb::Key, InputStatus*>::iterator it;
    for (it = InputStatus::map.begin(); it!=InputStatus::map.end(); it++)
    {
        if ((*it).second == this)
			InputStatus::map.erase(it);
            break;
    }
}

void InputStatus::DestroyAll()
{
	while(!InputStatus::map.empty())
	{
		delete InputStatus::map.begin()->second;
	}
}
