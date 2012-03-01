#ifndef _VERLETPOINT_H_
#define _VERLETPOINT_H_

#include <cmath>
#include <list>
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
		float myRadius; ///< Rayon, utilisé pour les collisions
		float myMass; ///< Masse
		float myBounce; ///< Coefficient de restitution
		bool myFixe; ///< Détermine si le point est fixe ou non (ApplyForce n'aura alors aucun effet)

	public:
		/// @brief Constructeur par défaut
		VerletPoint();

		/// @brief Destructeur par défaut
		~VerletPoint();

		/// @brief Liste des VerletPoint créés
		static std::list<VerletPoint*> VPList;

		/** @brief Appelle ApplyMomentum pour tout les VerletPoints
		 *
		 * @param prevdt Intervalle de temps lors de la frame précédente
		 * @param dt Intervalle de temps
		**/
		static void UpdateAll(float prevdt, float dt);

		/** @brief Applique une force à tout les VP
		 *
		 * Usage typique : Gravité
		 * @param Force Force à appliquer
		**/
		static void ForceAll(sf::Vector2f Force);

		/// @brief Détruit tout les VP
		static void DeleteAll();

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
		float GetRadius() { return myRadius; }

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
		 * @return Vrai si l'accélération effectivement été changée, faux sinon
		**/
		bool SetAcceleration(sf::Vector2f newAcc);

		/** @brief Mutateur du rayon
		 *
		 * @return Vrai si le rayon a effectivement été changée, faux sinon
		**/
		bool SetRadius(float newRadius);

		/** @brief Mutateur de la masse
		 *
		 * @return Vrai si la masse a effectivement été changée, faux sinon
		**/
		bool SetMass(float newMass);

		/// @brief Mutateur de myFixe
		void SetFixe(bool newFixe = true) { myFixe = newFixe; }

		/** @brief Applique une force à la particule
		 *
		 * La force n'est appliquée qu'à partir du seuil
		 * @param Force Force à ajouter/appliquer à la particule
		 * @param threshold Permet d'outrepasser le seuil par défaut
		 * @return Vrai si la force a été prise en compte
		**/
		bool ApplyForce(sf::Vector2f Force, float threshold = 0.1f);

		/** @brief Déplace la particule selon son momentum
		 *
		 * @param prevdt Intervalle de temps lors de la frame précédente
		 * @param dt Intervalle de temps
		**/
		void ApplyMomentum(float prevdt, float dt);

		/** @brief Test et Réaction aux collisions
		 *
		 * @param other Autre VerletPoint à tester
        **/
        void Collide(VerletPoint* other);
};

// A fouttre ailleurs, probablement
inline float Length(sf::Vector2f v) { return sqrt(v.x*v.x + v.y*v.y); }
inline sf::Vector2f Normalize(sf::Vector2f v) { return v/Length(v); }

#endif
