#pragma once

#include <list>

#include "Sound.h"
#include "Game.h"

/** @brief Objet pouvant émettre des sons (à hériter)
**/
class SoundEmitter
{
	private:
	/** @brief Contient les sons liés à l'objet
	**/
	std::list<Sound*> mySounds;

	public:
	SoundEmitter();
	~SoundEmitter();

	/** @brief Ajoute un son à l'objet et le joue
	*
	* @param key Chaine de caractère désignant un SoundBuffer de ResManager
	**/
	std::list<Sound*>::iterator AddSound(std::string key);

	/** @brief Joue un son persistant
	*
	* @param it Iterateur sur la liste de son de l'objet (mySounds)
	**/
	void PlaySound(std::list<Sound*>::iterator it);

	/** @brief Supprime un son de l'objet
	*
	* @param it Iterateur sur la liste de son de l'objet (mySounds)
	**/
	void RmSound(std::list<Sound*>::iterator it);


	/** @brief Supprime les sons non persistants et stoppés
	**/
	virtual void UpdateSoundList();
};
