#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "SFML/Graphics.hpp"
#include "Math.h"
#include "Character.h"

class Enemy
{

public:

	enum EnemyType
	{
		CHASE = 0,
		REFLECT,
		STATIC,
		UNPREDICTABLE,
		COUNT
	};

private:

	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_hitboxRadius;
	EnemyType m_type;
	int m_level;
	Character* m_pointer2Char;
	float m_directionAngle;
	float m_velocityModulation;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Clock m_lifeTime;
	float m_angularSpeed;
	float m_angularSpeedModulation;
	float m_graphicAngle; //the angle at which the texture is rotated.

public:

	Enemy();
	void init(EnemyType type, int level, sf::Vector2f velocity, sf::Vector2f position);
	bool InitTexture(EnemyType type);
	void setPointer2Char(Character* pointer2Char);
	float getSpeedFromType(int type);
	float getRadiusFromType(int type);
	void computeVelocity();
	sf::Vector2f getVelocity();
	void applyPowers();
	float getAngularSpeed();
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void setVelocity(sf::Vector2f newVelocity);
	void setVelocity(float angle, float magnitude);
	void reflect(sf::Vector2f n);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	float getHitboxRadius();
};

#endif //__ENEMY_H__