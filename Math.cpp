#include "Math.h"


const float Math::Rad2Deg = 180.0f/3.141592f;
const float Math::Deg2Rad = 3.141592f/180.0f;


float Math::Distanta(sf::Vector2f A, sf::Vector2f B)
{
	return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}
float Math::Modul(sf::Vector2f V)
{
	return sqrt(V.x*V.x+V.y*V.y);
}


sf::Vector2f Math::Rotate(sf::Vector2f v,float alfa)
{
	alfa = alfa * Deg2Rad;
	return sf::Vector2f(v.x*cos(alfa)+v.y*sin(alfa),-v.x*sin(alfa)+v.y*cos(alfa));
}

//inner product
float Math::Dot(sf::Vector2f u, sf::Vector2f v)
{
	return u.x*v.x+u.y*v.y;
}

//outer product
float Math::Cross(sf::Vector2f u, sf::Vector2f v)
{
	return u.x*v.y-u.y*v.x;
}

sf::Vector2f Math::Reflect(sf::Vector2f n, sf::Vector2f v)
{
	sf::Vector2f vperp, vparal;
	float modul_vperp,modul_vparal;
	//lungimea vperp cu semn
	modul_vperp = Dot(n,v);
	//descompunerea lui v de-a lungul directiei lui n - vector
	vperp.x = modul_vperp*n.x;
	vperp.y = modul_vperp*n.y;
	//lungimea vparal cu semn
	modul_vparal = Cross(n,v);
	//descompunerea lui v de-a lungul suprafetei de reflexie - vector
	vparal.x = modul_vparal*(-n.y);
	vparal.y = modul_vparal*(n.x);

	return vperp+(-vparal);
}

bool Math::Collision(sf::Vector2f center,float radius, sf::Vector2f A, sf::Vector2f B)
{
	//intializari
	float dist=0;
	sf::Vector2f n0;
	sf::Vector2f v0,v;
	float vModul = 1;
	//vector paralel cu dreapta AB
	v.x = B.x - A.x;
	v.y = B.y - A.y;
	//Lungimea lui v
	vModul=Modul(v);
	//Versor paralel cu v, ce da directia drepte AB
	v0.x = v.x / vModul;
	v0.y = v.y / vModul;
	//normala la AB, calculata ca fiind v0 rotit 90 grade in stanga
	n0.x = -v0.y;
	n0.y = v0.x;
	//formula distantei cand avem A,center si Normala
	dist = Dot(center-A, n0);
	//dist=abs(dist);
	//verificare coliziune
	if(dist < radius)
		return true;
	return false;
}
bool Math::Collision(sf::Vector2f c1,float r1, sf::Vector2f c2, float r2)
{
	if(r1+r2>Distanta(c1,c2))
		return true;
	return false;
}
sf::Vector2f Math::UnitVectorFromAngle(float angle, bool sexagesimal)
{
	if (!sexagesimal)
		return sf::Vector2f(cos(angle), sin(angle));
	else
		return sf::Vector2f(cos(angle * Deg2Rad), sin(angle * Deg2Rad));
}

sf::Vector2f Math::Normalize(sf::Vector2f vector)
{
	float m = Modul(vector);
	if (m > 0)
		return sf::Vector2f(vector.x / m, vector.y / m);
	// no valid vector to return
	return sf::Vector2f(0.0f, 0.0f);
}
