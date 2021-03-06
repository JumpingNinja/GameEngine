#include "KeyStatus.h"

std::map<sf::Keyboard::Key, KeyStatus*> KeyStatus::map;


KeyStatus::KeyStatus(sf::Keyboard::Key Key) : InputStatus(static_cast<gb::Key>(Key))
{
	KeyStatus::map[Key] = this;
}

KeyStatus::~KeyStatus()
{
	std::map<sf::Keyboard::Key, KeyStatus*>::iterator it;
    for (it = KeyStatus::map.begin(); it!=KeyStatus::map.end(); it++)
    {
        if ((*it).second == this)
			KeyStatus::map.erase(it);
            break;
    }
}

void KeyStatus::UpdateAll()
{
	for(std::map<sf::Keyboard::Key, KeyStatus*>::iterator it = KeyStatus::map.begin(); it != KeyStatus::map.end(); it++)
	{
		if((sf::Keyboard::IsKeyPressed(it->first))&&!(it->second->myIsKeyPressed))
			it->second->myJustPressed = 1;
		else
			it->second->myJustPressed = 0;

		if(!(sf::Keyboard::IsKeyPressed(it->first))&&(it->second->myIsKeyPressed))
			it->second->myJustReleased = 1;
		else
			it->second->myJustReleased = 0;

		it->second->myIsKeyPressed = sf::Keyboard::IsKeyPressed(it->first);
	}
}

void KeyStatus::DestroyAll()
{
	while(!KeyStatus::map.empty())
	{
		delete KeyStatus::map.begin()->second;
	}
}
