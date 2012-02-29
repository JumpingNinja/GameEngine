#ifndef _VERLETPOINT_H_
#define _VERLETPOINT_H_

#include <cmath>
#include <SFML/System/Vector2.hpp>

/** @class VerletPoint
 * @brief Décrit une particule dans une approximation de Verlet
 *
 * Dans un premier temps, l'approximation de Verlet pose que la dérivée de
 * l'accélération est nulle. Une prédiction de cette accélération peut elle
 * améliorer significativement la simulation ?
 *
 * L'initialisation simple suppose une vitesse et une accélération initiale
 * nulle. Une initilisation plus fine DOIT préciser une accélération initiale
 * valide (i.e. réaliste) pour une simulation précise.
**/
class VerletPoint
{
	private:
		sf::Vector2f myPosition; ///< Position actuelle
		sf::Vector2f myOldPosition; ///< Ancienne position
		sf::Vector2f myAcceleration; ///< Acceleration courante
		// sf::Vector2f myOldAcceleration; ///< Pourrait être utilisé pour
		// calculer la dérivée de l'accélération (approx. rang 3)
		float myMass; ///< Masse
		float myBounce; ///< Coefficient de restitution
		bool myFixe; ///< Détermine si le point est fixe ou non (ApplyForce n'aura alors aucun effet)

	public:
		/// @brief Constructeur par défaut
		VerletPoint();

		/// @brief Destructeur par défaut
		~VerletPoint();


		/** @brief Accesseur de la position
		 *
		 * @return sf::Vector2f
		**/
		sf::Vector2f GetPosition() { return myPosition; }

		/** @brief Accesseur de l'ancienne position
		 *
		 * @return sf::Vector2f
		**/
		sf::Vector2f GetOldPosition() { return myOldPosition; }

		/** @brief Accesseur de l'accélération
		 *
		 * @return sf::Vector2f
		**/
		sf::Vector2f GetAcceleration() { return myAcceleration; }

		/** @brief Accesseur de la Masse
		 *
		 * @return float Masse
		**/
		float GetMass() { return myMass; }

		/// @brief Accesseur de myFixe
		bool IsFixe() { return myFixe; }

		/** @brief Mutateur de la position
		 *
		 * @param newPos Nouvelle Position
		 * @param oldToo Vrai si l'ancienne position doit être également changée
		 * @return Vrai si la position a effectivement été changée, faux sinon
		**/
		bool SetPosition(sf::Vector2f newPos, bool oldToo = 1);

		/** @brief Mutateur de l'accélération
		 *
		 * @return Vrai si la position a effectivement été changée, faux sinon
		**/
		bool SetAcceleration(sf::Vector2f newAcc);

		/** @brief Applique une force à la particule
		 *
		 * @return Vrai si la force a été prise en compte
		**/
		bool ApplyForce(sf::Vector2f Force);

		/** @brief Déplace la particule selon son momentum
		 *
		 * @param prevdt Intervalle de temps lors de la fram précédente
		 * @param dt Intervalle de temps
		 * @return Nouvelle position
		**/
		void ApplyMomentum(float prevdt, float dt);
};

// A fouttre ailleurs, probablement
inline float Length(sf::Vector2f v) { return sqrt(v.x*v.x + v.y*v.y); }
inline sf::Vector2f Normalize(sf::Vector2f v) { return v/Length(v); }

#endif
