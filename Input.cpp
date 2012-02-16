#include "Input.h"

std::map<gb::Key, InputStatus*> InputStatus::map;

InputStatus::InputStatus(gb::Key Key) : myIsKeyPressed(0), myJustPressed(0), myJustReleased(0), myJoystick(0), myAxis(sf::Joystick::X)
{
	InputStatus::map[Key] = this;
}

InputStatus::InputStatus(gb::Key Key, unsigned int Joystick, sf::Joystick::Axis Axis) : myIsKeyPressed(0), myJustPressed(0), myJustReleased(0), myJoystick(Joystick), myAxis(Axis)
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

float InputStatus::GetPosition()
{
	return sf::Joystick::GetAxisPosition(myJoystick, myAxis);
}

void InputStatus::UpdateAll()
{
	// Pas possible comme ça :p
	//KeyStatus::UpdateAll();
	//MouseStatus::UpdateAll();
	//JoyButtonStatus::UpdateAll();
}

void InputStatus::DestroyAll()
{
	while(!InputStatus::map.empty())
	{
		delete InputStatus::map.begin()->second;
	}
}
