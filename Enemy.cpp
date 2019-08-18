#include <iostream>

#include "Enemy.h"
#include "Character.h"

Enemy::Enemy()
{
	m_type=STATIC;
	m_position=sf::Vector2f();
	m_velocity=sf::Vector2f();
	m_hitboxRadius = getRadiusFromType(m_type);
	m_directionAngle = 0.0f;
	m_pointer2Char = NULL;
	m_velocityModulation = 1.0f;
	m_lifeTime.restart();
	m_angularSpeed = 40.0f*Math::Deg2Rad;
	m_angularSpeedModulation = 1.0f;
	m_graphicAngle = 0.0f;
	m_level = 0;
}

void Enemy::init(Enemy::EnemyType type, int level, sf::Vector2f velocity, sf::Vector2f position)
{
	m_type = type;
	m_level = level;
	setVelocity(velocity);
	m_position = position;
	m_hitboxRadius = getRadiusFromType(m_type);
	m_pointer2Char = NULL;
	m_velocityModulation = 1.0f;
	m_lifeTime.restart();
	m_angularSpeedModulation = 1.0f;
	m_angularSpeed = 40.0f*Math::Deg2Rad;
	m_graphicAngle = 0.0f;
	if(InitTexture(m_type))
	{
		m_sprite.setTexture(m_texture);
	}
}

bool Enemy::InitTexture(Enemy::EnemyType type)
{
	switch(type)
	{
	case CHASE:
		{
			if(!m_texture.loadFromFile("Resources/MonsterChase.png"))
			{
				std::cout<<"Couldn't Load Monster Chase in enemies.initTexture"<<std::endl;
				return false;
			}
			break;
		}
	case REFLECT:
		{
			if(!m_texture.loadFromFile("Resources/MonsterReflect.png"))
			{
				std::cout<<"Couldn't Load Monster Reflect in enemies.initTexture"<<std::endl;
				return false;
			}
			break;
		}
	case STATIC:
		{
			if(!m_texture.loadFromFile("Resources/MonsterStatic.png"))
			{
				std::cout<<"Couldn't Load Monster Static in enemies.initTexture"<<std::endl;
				return false;
			}
			break;
		}
	case UNPREDICTABLE:
		{
			if(!m_texture.loadFromFile("Resources/MonsterUnpredictable.png"))
			{
				std::cout<<"Couldn't Load Monster Unpredictable in enemies.initTexture"<<std::endl;
				return false;
			}
			break;
		}
	default:
		{
			std::cout<<"Failed to load texture in enemies.initTexture: INVALID ENEMY TYPE"<<std::endl;
			return false;
		}
	}
	return true;
}

void Enemy::setPointer2Char(Character* pointer2Char)
{
	m_pointer2Char = pointer2Char;
}

float Enemy::getSpeedFromType(int type)
{
	switch(type)
	{
	case REFLECT:
		return 100.0f+10*m_level;
	case CHASE:
		return 100.0f+10*m_level;
	case STATIC:
		return 0.0f;
	case UNPREDICTABLE:
		return 100.0f+10*m_level;
	default:
		return 15.0f;
	}
}

float Enemy::getRadiusFromType(int type)
{
	switch(type)
	{
	case REFLECT:
		return 25.0f+2*m_level;
	case CHASE:
		return 25.0f+2*m_level;
	case UNPREDICTABLE: 
		return 25.0f+2*m_level;
	case STATIC:
		return 25.0f+2*m_level;
	default: 
		return 25.0f;
	}
}

void Enemy::computeVelocity()
{
	//player direction
	sf::Vector2f viteza;		//velocity 
	sf::Vector2f vectorEnemy2Char; //vector from enemy to player
	sf::Vector2f unitEnemy2Char;	//unit vector from enemy to player

	//computer vectorEnemy2Char
	vectorEnemy2Char.x = m_pointer2Char->getPosition().x - m_position.x;
	vectorEnemy2Char.y = m_pointer2Char->getPosition().y - m_position.y;

	float magnitudeEnemy2Char;
	magnitudeEnemy2Char=Math::Modul(vectorEnemy2Char);

	//compute unitEnemy2Char
	if (magnitudeEnemy2Char > 0)
	{
		unitEnemy2Char.x = vectorEnemy2Char.x / magnitudeEnemy2Char;
		unitEnemy2Char.y = vectorEnemy2Char.y / magnitudeEnemy2Char;
	}


	switch(m_type)
	{
	case CHASE:
		viteza.x = unitEnemy2Char.x * 50;
		viteza.y = unitEnemy2Char.y * 50;
		break;
	}
	setVelocity(viteza);
}

sf::Vector2f Enemy::getVelocity()
{
	return m_velocity * m_velocityModulation;
}

void Enemy::applyPowers()
{
	float velocityModulation = 1.0f;
	float angularSpeedModulation = 1.0f;

	//Slow Enemies
	if(m_pointer2Char->hasPowerOfType(Power::SLOW_ENEMIES))
	{
		if(m_pointer2Char->getPowerByType(Power::SLOW_ENEMIES).isActive())
		{
			velocityModulation *= 0.5f;
			angularSpeedModulation *= 0.5f;
		}
		if(m_pointer2Char->getPowerByType(Power::SLOW_ENEMIES).justFinished())
		{
			velocityModulation *= 1.0f;
			angularSpeedModulation *= 1.0f;
		}
	}

	//Freeze Enemies
	if(m_pointer2Char->hasPowerOfType(Power::FREEZE_ENEMIES))
	{
		if(m_pointer2Char->getPowerByType(Power::FREEZE_ENEMIES).isActive())
		{
			velocityModulation *= 0.0f;
			angularSpeedModulation *=0.0f;

		}
		if(m_pointer2Char->getPowerByType(Power::FREEZE_ENEMIES).justFinished())
		{
			velocityModulation *= 1.0f;
			angularSpeedModulation *= 1.0f;
		}
	}
	m_velocityModulation = velocityModulation;
	m_angularSpeedModulation = angularSpeedModulation;
}

float Enemy::getAngularSpeed()
{
	return m_angularSpeed*m_angularSpeedModulation;
}

void Enemy::update(float dt)
{
	switch(m_type)
	{
	case CHASE:
		{
			computeVelocity();
			bool following = true;
			if(m_pointer2Char->hasPowerOfType(Power::FREEZE_ENEMIES))
				if(m_pointer2Char->getPowerByType(Power::FREEZE_ENEMIES).isActive())
					following = false;
			if(following)
				m_graphicAngle = m_directionAngle;
			break;
		}
	case STATIC:
	case REFLECT:
	case UNPREDICTABLE:
		{
			m_graphicAngle += getAngularSpeed() * dt;
			break;
		}

	}
	applyPowers();
	m_position = m_position + getVelocity() * dt;

}

void Enemy::draw(sf::RenderTarget& renderTarget)
{
	switch(m_type)
	{
	case REFLECT:
	case CHASE:
	case UNPREDICTABLE:
	case STATIC:
		{
			//slow enemies;
			if(m_pointer2Char->hasPowerOfType(Power::SLOW_ENEMIES))
			{
				if(m_pointer2Char->getPowerByType(Power::SLOW_ENEMIES).isActive())
				{
					m_sprite.setColor(sf::Color::Cyan);
				}
			}
			//freeze enemies;
			if(m_pointer2Char->hasPowerOfType(Power::FREEZE_ENEMIES))
			{
				if(m_pointer2Char->getPowerByType(Power::FREEZE_ENEMIES).isActive())
				{
					m_sprite.setColor(sf::Color::Blue);
				}
			}
			m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.0f, m_sprite.getTexture()->getSize().y/2.0f);
			m_sprite.setScale(1.0f/m_texture.getSize().x*getHitboxRadius()*2, 1.0f/m_texture.getSize().y*getHitboxRadius()*2);
			m_sprite.setPosition(m_position);
			m_sprite.setRotation(m_graphicAngle*Math::Rad2Deg);
			renderTarget.draw(m_sprite);
			m_sprite.setColor(sf::Color::White);
			break;
		}
	default: 
		{
			sf::CircleShape shape(m_hitboxRadius);
			shape.setFillColor(sf::Color::Red);
			if(m_pointer2Char->hasPowerOfType(Power::SLOW_ENEMIES))
			{
				if(m_pointer2Char->getPowerByType(Power::SLOW_ENEMIES).isActive())
				{
					shape.setFillColor(sf::Color::Blue);
				}
			}

			shape.setOrigin(sf::Vector2f(m_hitboxRadius,m_hitboxRadius));
			shape.setPosition(m_position);
			renderTarget.draw(shape);
		}
	}
}

void Enemy::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity=newVelocity;
	if(!Math::Modul(m_velocity) == 0)
		m_directionAngle = atan2(m_velocity.y,m_velocity.x);
}

//angle este dat in grade
void Enemy::setVelocity(float angle, float magnitude)
{

	angle = angle*Math::Deg2Rad;
	m_directionAngle = angle;
	m_velocity.x = magnitude*cos(angle);
	m_velocity.y = magnitude*sin(angle);
}

void Enemy::reflect(sf::Vector2f n)
{
	switch(m_type)
	{
	case REFLECT:
	case UNPREDICTABLE:
		m_velocity = Math::Reflect(n,sf::Vector2f(-m_velocity.x,-m_velocity.y));
		break;
	default:
		break;
	}
}

sf::Vector2f Enemy::getPosition()
{
	return m_position;
}

void Enemy::setPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
}

float Enemy::getHitboxRadius()
{
	return m_hitboxRadius;
}