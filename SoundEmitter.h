#pragma once

#include <list>

#include "Sound.h"
#include "Game.h"

class SoundEmitter
{
	private:
	/** @brief Contient les sons liés à l'objet
	**/
	std::list<Sound*> mySounds;

	public:
	SoundEmitter();
	~SoundEmitter();

	std::list<Sound*>::iterator AddSound(std::string key);
	void PlaySound(std::list<Sound*>::iterator it);
	void RmSound(std::list<Sound*>::iterator it);

	virtual void UpdateSoundList();
};
