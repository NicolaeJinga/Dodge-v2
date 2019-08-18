#include <iostream>
#include "Premiu.h"
#include "Character.h"

Premiu::Premiu()
{
	m_type = STATIC;
	m_position = sf::Vector2f();
	m_velocity = sf::Vector2f();
	m_hitboxRadius = 10.0f;
	m_pointer2Char = NULL;
}

void Premiu::init(float radius,Premiu::PremiuType type, sf::Vector2f velocity, sf::Vector2f position)
{
	m_hitboxRadius=radius; 
	m_type = type;
	m_velocity=velocity;
	m_position=position;
	m_pointer2Char = NULL;
	if(InitTexture(m_type))
	{
		m_sprite.setTexture(m_texture);
	}
}

bool Premiu::InitTexture(Premiu::PremiuType type)
{
	switch(type)
	{

	case STATIC:
		{
			if(!m_texture.loadFromFile("Resources/PremiuStatic.png"))
			{
				std::cout<<"Couldn't Load Premiu Static in premiu.initTexture"<<std::endl;
				return false;
			}
			break;
		}

	case RUNNING:
		{
			if(!m_texture.loadFromFile("Resources/PremiuRunning.png"))
			{
				std::cout<<"Couldn't Load Premiu Running in premiu.initTexture"<<std::endl;
				return false;
			}
			break;
		}

	default:
		{
			std::cout<<"Failed to load texture in premiu.initTexture: INVALID PREMIU TYPE"<<std::endl;
			break;
		}
	}
	return true;

}

void Premiu::setPointer2Char(Character* pointer2Char)
{
	m_pointer2Char = pointer2Char;
}

void Premiu::updateVelocity(float dt)
{
	//compute player direction
	sf::Vector2f vitezaPremiu;		//premiu velocity
	sf::Vector2f vectorPremiu2Char; //vector from premiu to player
	sf::Vector2f unitPremiu2Char;	//unit vector from premiu to player

	//compute vectorPremiu2Char
	vectorPremiu2Char.x = m_pointer2Char->getPosition().x - m_position.x;
	vectorPremiu2Char.y = m_pointer2Char->getPosition().y - m_position.y;

	float magnitudePremiu2Char;
	magnitudePremiu2Char=sqrt(vectorPremiu2Char.x*vectorPremiu2Char.x+vectorPremiu2Char.y*vectorPremiu2Char.y);

	//compute versorului unitPremiu2Char
	if (magnitudePremiu2Char >0)
	{
		unitPremiu2Char.x = vectorPremiu2Char.x / magnitudePremiu2Char;
		unitPremiu2Char.y = vectorPremiu2Char.y / magnitudePremiu2Char;
	}

	if(m_type == STATIC)
	{
		//premiu staying still
		vitezaPremiu = sf::Vector2f();
	}

	if(m_type == RUNNING)
	{
		// compute velocity
		if(magnitudePremiu2Char < 100)
		{
			// run since player is close
			vitezaPremiu.x =-150*unitPremiu2Char.x;
			vitezaPremiu.y =-150*unitPremiu2Char.y;				
		}
		else
		{
			// stop running since player is far away
			vitezaPremiu = sf::Vector2f();
		}
	}																					
	//compute velocity: power magnet interaction
	if(m_pointer2Char->hasPowerOfType(Power::PRIZE_MAGNET))
	{
		if(m_pointer2Char->getPowerByType(Power::PRIZE_MAGNET).isActive())
		{
			if(magnitudePremiu2Char < 101)
			{
				vitezaPremiu.x = 150*unitPremiu2Char.x;
				vitezaPremiu.y = 150*unitPremiu2Char.y;
			}
		}
	}
	setVelocity(vitezaPremiu);
}

void Premiu::update(float dt)
{
	updateVelocity(dt);
	m_position += m_velocity*dt;
}

void Premiu::draw(sf::RenderTarget& renderTarget)
{	
	switch(m_type)
	{
	case STATIC:
	case RUNNING:
		{
			m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.0f, m_sprite.getTexture()->getSize().y/2.0f);
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

void Premiu::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity=newVelocity;
}

sf::Vector2f Premiu::getPosition()
{
	return m_position;
}

void Premiu::setPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
}

float Premiu::getHitboxRadius()
{
	return m_hitboxRadius;
}