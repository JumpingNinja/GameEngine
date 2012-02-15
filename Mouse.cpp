#include "Mouse.h"

std::map<sf::Mouse::Button, MouseStatus*> MouseStatus::map;


MouseStatus::MouseStatus(sf::Mouse::Button Button) : InputStatus(static_cast<gb::Key>(Button + gb::LastKeyboardKey))
{
	MouseStatus::map[Button] = this;
}

MouseStatus::~MouseStatus()
{
	std::map<sf::Mouse::Button, MouseStatus*>::iterator it;
    for (it = MouseStatus::map.begin(); it!=MouseStatus::map.end(); it++)
    {
        if ((*it).second == this)
			MouseStatus::map.erase(it);
            break;
    }
}

void MouseStatus::Update()
{
	for(std::map<sf::Mouse::Button, MouseStatus*>::iterator it = MouseStatus::map.begin(); it != MouseStatus::map.end(); it++)
	{
		if((sf::Mouse::IsButtonPressed(it->first))&&!(it->second->myIsKeyPressed))
			it->second->myJustPressed = 1;
		else
			it->second->myJustPressed = 0;

		if(!(sf::Mouse::IsButtonPressed(it->first))&&(it->second->myIsKeyPressed))
			it->second->myJustReleased = 1;
		else
			it->second->myJustReleased = 0;

		it->second->myIsKeyPressed = sf::Mouse::IsButtonPressed(it->first);
	}
}

void MouseStatus::DestroyAll()
{
	while(!MouseStatus::map.empty())
	{
		delete MouseStatus::map.begin()->second;
	}
}
