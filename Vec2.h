#ifndef _VEC2_H_
#define _VEC2_H_

#include <cmath>

/// @brief Classe simple décrivant un vecteur de R²
class Vec2
{
	public:
		float x; ///< Composante x
		float y; ///< Composante y

		Vec2();
		Vec2(float, float);
		~Vec2();

		float GetLength();
		Vec2 GetNormalized();
		Vec2 GetPerpendicular();

		Vec2& operator+=(const Vec2& V);
		Vec2& operator-=(const Vec2& V);
		Vec2& operator*=(const float& f);
		Vec2& operator/=(const float& f);

		friend Vec2 operator-(const Vec2& V);
		friend Vec2 operator+(const Vec2& V1, const Vec2& V2);
		friend Vec2 operator-(const Vec2& V1, const Vec2& V2);
		friend Vec2 operator*(const Vec2& V, const float& f);
		friend Vec2 operator*(const float& f, const Vec2& V);
		friend Vec2 operator/(const Vec2& V, const float& f);
		/// @brief Produit scalaire
		friend float operator*(const Vec2& V1, const Vec2& V2);

		friend bool operator==(const Vec2& V1, const Vec2& V2);
		friend bool operator!=(const Vec2& V1, const Vec2& V2);
		/// @brief Teste les normes
		friend bool operator>(Vec2& V1, Vec2& V2);
		friend bool operator<(Vec2& V1, Vec2& V2);
		friend bool operator>=(Vec2& V1, Vec2& V2);
		friend bool operator<=(Vec2& V1, Vec2& V2);
};

#endif
