#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "SFML/Graphics.hpp"
#include "Power.h"

class Character
{
private:
	sf::Color m_color;
	float m_hitboxRadius;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_magnetPowerTexture;
	sf::Sprite m_magnetPowerSprite;


	float m_directionAngle;
	int m_nrPowers;
	Power m_powers[5];
	float m_radiusModulator;
	float m_speedModulator;

public:

	Character();
	~Character()
	{
	}

	void init(sf::Color color, float radius, sf::Vector2f velocity, sf::Vector2f position);
	void updatePowers(float dt);
	void updateVelocity(float dt);
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void setVelocity(sf::Vector2f newVelocity);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	float getHitboxRadius();
	void applyPower(Power& power);
	Power& getPower(int i);
	int getNrPowers();
	bool hasPowerOfType(int type);
	Power& getPowerByType(int type);
	sf::Vector2f getVelocity();
};

#endif //__CHARACTER_H__