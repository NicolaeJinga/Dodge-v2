#ifndef __MATH_H__
#define __MATH_H__

#include "SFML/Graphics.hpp"

class Math
{
public:
	static const float Deg2Rad;
	static const float Rad2Deg;

	static float Distanta(sf::Vector2f A, sf::Vector2f B);
	static float Modul(sf::Vector2f V);
	static sf::Vector2f Rotate(sf::Vector2f v,float alfa);
	//inner product (produs scalar)
	static float Dot(sf::Vector2f u, sf::Vector2f v);
	//outer product (produs vectorial dar in 2D)
	static float Cross(sf::Vector2f u, sf::Vector2f v);
	static sf::Vector2f Reflect(sf::Vector2f n, sf::Vector2f v);
	static bool Collision(sf::Vector2f center,float radius, sf::Vector2f A, sf::Vector2f B);
	static bool Collision(sf::Vector2f c1,float r1, sf::Vector2f c2, float r2);
	static sf::Vector2f UnitVectorFromAngle(float angle, bool sexagesimal);
	static sf::Vector2f Normalize(sf::Vector2f vector);
};

#endif __MATH_H__