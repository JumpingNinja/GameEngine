#ifndef _PHYSICSPOINT_H_
#define _PHYSICSPOINT_H_

#include <cmath>
#include <list>
#include <SFML/OpenGL.hpp>

#include "Vec2.h"

namespace Physics
{

/** @class Point
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
class Point
{
	private:
		Vec2	myPosition; ///< Position actuelle
		Vec2	myOldPosition; ///< Ancienne position
		Vec2	myAcceleration; ///< Acceleration courante
		// Vec2 myOldAcceleration; ///< Pourrait être utilisé pour
		// calculer la dérivée de l'accélération (approx. rang 3)
		float	myRadius; ///< Rayon, utilisé pour les collisions
		float	myMass; ///< Masse
		float	myBounce; ///< Coefficient de restitution
		bool	myFixe; ///< Détermine si le point est fixe ou non (ApplyForce n'aura alors aucun effet)

	public:
		/// @brief Constructeur par défaut
		Point();

		/// @brief Constructeur par coordonnées
		Point(float x, float y);

		/// @brief Constructeur par coordonnées et masse
		Point(float x, float y, float Mass);

		/// @brief Constructeur par Vec2
		Point(Vec2 Pos);

		/// @brief Destructeur par défaut
		~Point();

		/// @brief Liste des Point créés
		static std::list<Point*> List;

		/** @brief Appelle ApplyMomentum pour tout les Points
		 *
		 * @param prevdt Intervalle de temps lors de la frame précédente
		 * @param dt Intervalle de temps
		**/
		static void UpdateAll(float prevdt, float dt);

		/** @brief Applique une force à tout les VP
		 *
		 * Usage typique : Gravité
		 * @param Force Force à appliquer
		 * @param Mass Si true, la force est multipliée par la masse (Puisque l'on part du principe que l'on ne travaille pas dans le vide...)
		**/
		static void ForceAll(Vec2 Force, bool Mass = 0);

		/// @brief Détruit tout les VP
		static void DeleteAll();

		/** @brief Accesseur de la position
		 *
		 * @return Vec2
		**/
		Vec2 GetPosition() { return myPosition; }

		/** @brief Accesseur de l'ancienne position
		 *
		 * @return Vec2
		**/
		Vec2 GetOldPosition() { return myOldPosition; }

		/** @brief Accesseur de l'accélération
		 *
		 * @return Vec2
		**/
		Vec2 GetAcceleration() { return myAcceleration; }

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
		bool SetPosition(Vec2 newPos, bool oldToo = 1);

		/** @brief Corrige la position actuelle par un vecteur
		 *
		 * @param add Vecteur à ajouter (déplacement)
		 * @return Vrai si la position a effectivement été changée, faux sinon
		**/
		bool CorrectPosition(Vec2 add);

		/** @brief Mutateur de l'accélération
		 *
		 * @return Vrai si l'accélération effectivement été changée, faux sinon
		**/
		bool SetAcceleration(Vec2 newAcc);

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
		bool ApplyForce(Vec2 Force, float threshold = 0.001f);

		/** @brief Déplace la particule selon son momentum et son acceleration
		 *
		 * @param prevdt Intervalle de temps lors de la frame précédente
		 * @param dt Intervalle de temps
		**/
		void ApplyMomentum(float prevdt, float dt);


	void glDraw();
	static void DrawAll();

	static Point* GetNearest(const Vec2 &v);
};

}

#endif
