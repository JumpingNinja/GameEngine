#include "KeyStatus.h"

std::map<sf::Keyboard::Key, KeyStatus*> KeyStatus::map;


KeyStatus::KeyStatus(sf::Keyboard::Key Key) : myIsKeyPressed(0), myJustPressed(0), myJustReleased(0)
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

void KeyStatus::Update(sf::RenderWindow &myMainWindow)
{
	for(std::map<sf::Keyboard::Key, KeyStatus*>::iterator it = KeyStatus::map.begin(); it != KeyStatus::map.end(); it++)
	{
		it->second->myIsKeyPressed = sf::Keyboard::IsKeyPressed(it->first);
		it->second->myJustPressed = 0;
		it->second->myJustReleased = 0;
	}

	sf::Event Event;

    // à faire ailleurs pour pouvoir prendre en compte tout les types d'événements !
	while(myMainWindow.PollEvent(Event))
	{
		if (Event.Type == sf::Event::KeyPressed)
		{
			KeyStatus::map[Event.Key.Code]->myJustPressed = 1;
		} else if(Event.Type == sf::Event::KeyReleased) {
			KeyStatus::map[Event.Key.Code]->myJustReleased = 1;
		}
	}
}
