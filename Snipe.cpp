#include<iostream>
#include "Snipe.h"
#include "Character.h"
#include "Math.h"

Snipe::Snipe()
{
	m_type = SNIPE;
	m_position = sf::Vector2f();
	m_velocity = sf::Vector2f();
	m_hitboxRadius = 20.0f;
	m_pointer2Char = NULL;
	m_hit = false;
}

void Snipe::init(float radius,Snipe::SnipeType type, sf::Vector2f position, float stunTime, float forceChaseTime, float chargeTime, bool state)
{
	m_hitboxRadius = radius;
	m_type = type;
	m_position = position;
	m_pointer2Char = NULL;
	m_state = state;
	if(initTexture(m_type))
	{
		m_sprite.setTexture(m_texture);
	}
	m_state = NORMAL;
}

bool Snipe::initTexture(Snipe::SnipeType type)
{
	switch(type)
	{

	case SNIPE:
		{
			if(!m_texture.loadFromFile("Resources/SnipeSnipe.png"))
			{
				std::cout<<"Couldn't Load Snipe Snipe in snipe.initTexture"<<std::endl;
				return false;
			}
			break;
		}

	case BURST:
		{
			if(!m_texture.loadFromFile("Resources/SnipeBurst.png"))
			{
				std::cout<<"Couldn't Load Snipe Burst in snipe.initTexture"<<std::endl;
				return false;
			}
			break;
		}

	default:
		{
			std::cout<<"Failed to load texture in snipe.initTexture: INVALID SNIPE TYPE"<<std::endl;
			break;
		}
	}
	return true;
}

void Snipe::setHit(bool hit)
{
	m_hit = hit;
}

bool Snipe::hasHitTarget()
{
	return m_hit;
}

void Snipe::setPointer2Char(Character* pointer2Char)
{
	m_pointer2Char = pointer2Char;
}

void Snipe::updateVelocity(float dt)
{
	sf::Vector2f vitezaSnipe;
	sf::Vector2f vectorSnipe2Char;
	sf::Vector2f unitSnipe2Char;

	vectorSnipe2Char.x = m_pointer2Char->getPosition().x - m_position.x;
	vectorSnipe2Char.y = m_pointer2Char->getPosition().y - m_position.y;

	float magnitudeSnipe2Char;
	magnitudeSnipe2Char=Math::Modul(vectorSnipe2Char);
	if(magnitudeSnipe2Char > 0)
	{
		unitSnipe2Char = Math::Normalize(vectorSnipe2Char);
	}
	if(m_type == SNIPE)
	{
		vitezaSnipe = unitSnipe2Char*300.0f;
	}
	if(m_type == BURST)
	{
		vitezaSnipe = sf::Vector2f();
	}
	//If snipe is not moving or we are in the FORCESCHASE state
	if(Math::Modul(m_pointer2Char->getVelocity())==0 || m_state == FORCECHASE)
	{
		//charge towards player
		setVelocity(vitezaSnipe);
	}
	else
	{
		//controlled by player
		setVelocity(m_pointer2Char->getVelocity()*1.5f);
	}
}

void Snipe::update(float dt)
{
	switch(m_state)
	{
	case NORMAL:
		{
			if(Math::Distanta(m_pointer2Char->getPosition(), m_position) > 300)
				m_state = FORCECHASE;
			//stuff to do in this state
			updateVelocity(dt);
			//transition to other states
			if(m_ellapsedTime.getElapsedTime().asSeconds() >= 10)
				m_state = FORCECHASE;
			if(Math::Distanta(m_pointer2Char->getPosition(), m_position) <= 5)
			{
				m_state = CHARGE;
				setVelocity(sf::Vector2f(0.0f,0.0f));
				m_ellapsedTime.restart();
			}
			break;
		}
	case FORCECHASE:
		{
			updateVelocity(dt);
			if(Math::Distanta(m_pointer2Char->getPosition(), m_position) <= 5)
			{
				m_state = CHARGE;
				m_ellapsedTime.restart();
				setVelocity(sf::Vector2f(0.0f,0.0f));
			}
			
			break;
		}
	case CHARGE:
		{
			//shoot
			if(m_ellapsedTime.getElapsedTime().asSeconds() >= 1)
			{
				m_state = STUN;
				m_ellapsedTime.restart();
				//did we hit?
				if(Math::Collision(m_pointer2Char->getPosition(),m_pointer2Char->getHitboxRadius(),m_position,m_hitboxRadius*0.75f))
					m_hit = true;
				//imprint image
			}

			break;
		}
	case STUN:
		{
			if(m_ellapsedTime.getElapsedTime().asSeconds()>=2)
			{
				m_state = NORMAL;
				m_ellapsedTime.restart();
			}
			break;
		}
	}
	m_position += m_velocity * dt;
}

void Snipe::draw(sf::RenderTarget& renderTarget)
{
	switch(m_type)
	{
	case SNIPE:
	case BURST:
		{
			sf::Color colorModulator;
			switch(m_state)
			{
			case NORMAL:
				colorModulator = sf::Color::Red;
				break;
			case FORCECHASE:
				colorModulator = sf::Color(255,200,0);
				break;
			case CHARGE:
				{
					float t=(float)sin(5*m_ellapsedTime.getElapsedTime().asSeconds()*2*3.141592f)*0.5f+0.5f;
					colorModulator.r = (sf::Uint8)(255	* (1-t) + 255	* t);
					colorModulator.g = (sf::Uint8)(  0	* (1-t) + 255	* t);
					colorModulator.b = (sf::Uint8)(  0	* (1-t) +   0	* t);
					break;
				}
			case STUN:
				{
					colorModulator = sf::Color(100,100,100);
					break;
				}
				
			}
			m_sprite.setColor(colorModulator);
			m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.0f,m_sprite.getTexture()->getSize().y/2.0f);
			m_sprite.setScale(1.0f/m_texture.getSize().x*getHitboxRadius()*2, 1.0f/m_texture.getSize().y*getHitboxRadius()*2);
			m_sprite.setPosition(m_position);
			renderTarget.draw(m_sprite);
			break;
		}
	default:
		{
			sf::CircleShape shape(m_hitboxRadius);
			shape.setFillColor(sf::Color::White);
			shape.setOrigin(sf::Vector2f(m_hitboxRadius,m_hitboxRadius));
			shape.setPosition(m_position);
			renderTarget.draw(shape);
			break;
		}
	}
}

void Snipe::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}

sf::Vector2f Snipe::getPosition()
{
	return m_position;
}

sf::Vector2f Snipe::getVelocity()
{
	return m_velocity;
}

void Snipe::setPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
}

float Snipe::getHitboxRadius()
{
	return m_hitboxRadius;
}

float Snipe::getStunTime()
{
	return m_stunTime;
}

float Snipe::getForceChaseTime()
{
	return m_forceChaseTime;
}

float Snipe::getChargeTime()
{
	return m_chargeTime;
}