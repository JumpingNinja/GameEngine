#include "Joystick.h"
#include <iostream>

std::map<gb::Key, JoystickAxis*> JoystickAxis::map;

JoystickAxis::JoystickAxis(unsigned int Joystick, sf::Joystick::Axis Axis) : myJoystick(Joystick), myAxis(Axis)
{
	JoystickAxis::map[static_cast<gb::Key>(gb::LastJoystickButton + myJoystick*8 + myAxis + 1)] = this;
}

float JoystickAxis::GetPosition()
{
	return sf::Joystick::GetAxisPosition(myJoystick, myAxis);
}

JoystickAxis::~JoystickAxis()
{
	std::map<gb::Key, JoystickAxis*>::iterator it;
    for (it = JoystickAxis::map.begin(); it!=JoystickAxis::map.end(); it++)
    {
        if ((*it).second == this)
			JoystickAxis::map.erase(it);
            break;
    }
}



std::map<unsigned int, JoyButtonStatus*> JoyButtonStatus::map;

JoyButtonStatus::JoyButtonStatus(unsigned int Button) : InputStatus(static_cast<gb::Key>(Button))
{
	JoyButtonStatus::map[Button] = this;
}

JoyButtonStatus::~JoyButtonStatus()
{
	std::map<unsigned int, JoyButtonStatus*>::iterator it;
    for (it = JoyButtonStatus::map.begin(); it!=JoyButtonStatus::map.end(); it++)
    {
        if ((*it).second == this)
			JoyButtonStatus::map.erase(it);
            break;
    }
}

void JoyButtonStatus::UpdateAll()
{
	// sf::Joystick::Update();
	for(std::map<unsigned int, JoyButtonStatus*>::iterator it = JoyButtonStatus::map.begin(); it != JoyButtonStatus::map.end(); it++)
	{
		if((sf::Joystick::IsButtonPressed(it->first/(int)32, it->first%32))&&!(it->second->myIsKeyPressed))
			it->second->myJustPressed = 1;
		else
			it->second->myJustPressed = 0;

		if(!(sf::Joystick::IsButtonPressed(it->first/(int)32, it->first%32))&&(it->second->myIsKeyPressed))
			it->second->myJustReleased = 1;
		else
			it->second->myJustReleased = 0;

		it->second->myIsKeyPressed = sf::Joystick::IsButtonPressed(it->first/(int)32, it->first%32);
	}
}

void JoyButtonStatus::DestroyAll()
{
	while(!JoyButtonStatus::map.empty())
	{
		delete JoyButtonStatus::map.begin()->second;
	}
}

