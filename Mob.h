#ifndef MOB_H
#define MOB_H

#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"

/** @class Classe g�rant les objets mobiles
* H�rite d'Entity, donc affichable.
**/
class Mob : public Entity
{
    /**@brief Vector o� sont stock�s les pointeurs vers les instances des objets mobiles.
	*
	**/
    static std::vector<Mob*> list;
    /**@brief It�rateur de Mob::list
	*
	**/
    static std::vector<Mob*>::iterator it;
    /**@brief Vitesse limite g�n�rale.
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
		/** @brief Accesseur de la gravit�.
	*
	**/	
	float GetGravity() { return myGravity; }
	
	/** @brief Modificateur de la vitesse.
	* @param aSpeed Nouvelle vitesse.
	**/
	void SetSpeed(sf::Vector2f aSpeed);
	
	/** @brief Ajout de vitesse.
	* Acc�l�ration/D�c�l�ration
	* @param aSpeed Vitesse � ajouter.
	**/
	void AddSpeed(sf::Vector2f aSpeed);
	
	/** @brief Applique la vitesse actuelle
	*
	**/
	void ApplySpeed();
	
	private:
	
	/** @brief Vitesse maximale sp�cifique � cet objet.
	* Doit �tre inf�rieure � Mob::maxSpeed (V�rifi�e dans constructeur et modificateur).
	**/
	float myMaxSpeed;
	
	/** @brief Vecteur vitesse.
	* Limit�e par myMaxSpeed et donc Mob::maxSpeed
	**/
	sf::Vector2f mySpeed;
	
	/** @brief Application de la gravit� sur l'objet.
	* D�termine la r�action du mobile � la gravit� :
	* 0 => Aucun action
	* 1 => Gravit� Normale
	* -1 => Invers�e
	* Etc...
	**/
	float myGravity;
};

#endif