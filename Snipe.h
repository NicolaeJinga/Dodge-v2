#ifndef __SNIPE_H__
#define __SNIPE_H__

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Character.h"

class Snipe
{
public:
	enum SnipeType
	{
		SNIPE = 0,
		BURST,
		SMOKE
	};

	enum SnipeState
	{
		NORMAL = 0,
		FORCECHASE,
		CHARGE,
		STUN,
		COUNT
	};
private:
	SnipeType m_type;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	Character* m_pointer2Char;
	float m_hitboxRadius;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::SoundBuffer m_snipeBuffer;
	sf::Sound m_snipeSound;
	float m_stunTime;//time it's stunned after it lands a hit
	float m_forceChaseTime;//time after ignore player movement and comes straight to player
	float m_chargeTime;//time it takes to shoot the player after its aiming
	sf::Clock m_ellapsedTime;
	int m_state;
	bool m_hit;

public:

	Snipe();
	void init(float radius,Snipe::SnipeType type, sf::Vector2f position, float stunTime, float forceChaseTime, float chargeTime, bool state);
	bool initTexture(SnipeType type);
	bool initDamageTexture(SnipeType type);
	void setPointer2Char(Character* pointer2Char);
	void updateVelocity(float dt);
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void setVelocity(sf::Vector2f newVelocity);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getStunTime();
	float getForceChaseTime();
	float getChargeTime();
	void setPosition(sf::Vector2f newPosition);
	float getHitboxRadius();
	bool hasHitTarget();
	void setHit(bool hit);

};


#endif //__SNIPE_H__