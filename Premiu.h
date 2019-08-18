#ifndef __PREMIU_H__
#define __PREMIU_H__

#include "SFML/Graphics.hpp"
#include "Character.h"

class Premiu
{

public:
	enum PremiuType
	{
		STATIC = 0,
		RUNNING,
		COUNT
	};

private:
	PremiuType m_type;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	Character* m_pointer2Char;
	float m_hitboxRadius;
	sf::Texture m_texture;
	sf::Sprite m_sprite;


public:

	Premiu();
	void init(float radius,PremiuType type, sf::Vector2f velocity, sf::Vector2f position);
	bool InitTexture(PremiuType type);
	void setPointer2Char(Character* pointer2Char);
	void updateVelocity(float dt);
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void setVelocity(sf::Vector2f newVelocity);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	float getHitboxRadius();
};

#endif //__PREMIU_H__