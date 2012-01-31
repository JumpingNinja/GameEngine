#ifndef MOB_H
#define MOB_H

#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"

/** @class Classe gérant les objets mobiles
* Hérite d'Entity, donc affichable.
**/
class Mob : public Entity
{
    /**@brief Vector où sont stockés les pointeurs vers les instances des objets mobiles.
	*
	**/
    static std::vector<Mob*> list;
    /**@brief Itérateur de Mob::list
	*
	**/
    static std::vector<Mob*>::iterator it;
    /**@brief Vitesse limite générale.
	*
	**/
	static float maxSpeed;
	
	public:
	
	/** @brief Constructeur simple.
	*
	**/
	Mob();
	/** @brief Constructeur avec profondeur.
	* @param aDepth Profondeur
	**/
	Mob(short aDepth);
	/** @brief Constructeur avec texture.
	* @param aTexture Texture
	**/
	Mob(sf::Texture aTexture);
	/** @brief Constructeur avec texture et profondeur.
	* @param aTexture Texture
	**/
	Mob(sf::Texture aTexture, short aDepth);
	
	/** @brief Accesseur de la vitesse.
	*
	**/	
	sf::Vector2f GetSpeed() { return mySpeed; }
		/** @brief Accesseur de la gravité.
	*
	**/	
	float GetGravity() { return myGravity; }
	
	/** @brief Modificateur de la vitesse.
	* @param aSpeed Nouvelle vitesse.
	**/
	void SetSpeed(sf::Vector2f aSpeed);
	
	/** @brief Ajout de vitesse.
	* Accélération/Décélération
	* @param aSpeed Vitesse à ajouter.
	**/
	void AddSpeed(sf::Vector2f aSpeed);
	
	/** @brief Applique la vitesse actuelle
	*
	**/
	void ApplySpeed();
	
	private:
	
	/** @brief Vitesse maximale spécifique à cet objet.
	* Doit être inférieure à Mob::maxSpeed (Vérifiée dans constructeur et modificateur).
	**/
	float myMaxSpeed;
	
	/** @brief Vecteur vitesse.
	* Limitée par myMaxSpeed et donc Mob::maxSpeed
	**/
	sf::Vector2f mySpeed;
	
	/** @brief Application de la gravité sur l'objet.
	* Détermine la réaction du mobile à la gravité :
	* 0 => Aucun action
	* 1 => Gravité Normale
	* -1 => Inversée
	* Etc...
	**/
	float myGravity;
};

#endif