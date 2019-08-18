#include<iostream>
#include "Character.h"
#include "Power.h"
#include "Math.h"


Character::Character()
{
	m_color = sf::Color::White;
	m_hitboxRadius = 10.0f;
	m_velocity = sf::Vector2f(0,0);
	m_position = sf::Vector2f(0,0);
	m_directionAngle = 0.0f;
	m_radiusModulator = 1.0f;
	m_speedModulator = 1.0f;
}

void Character::init(sf::Color color, float radius, sf::Vector2f velocity, sf::Vector2f position)
{
	m_color=color;
	m_hitboxRadius=radius; 
	m_velocity=velocity;
	m_position=position;
	if(m_texture.loadFromFile("Resources/PlayerCharacter.png")==false)
		std::cout<<"could not load PlayerCharacter.png. error in character.init"<<std::endl;
	m_sprite.setTexture(m_texture);

	if(m_magnetPowerTexture.loadFromFile("Resources/MagnetPower.png")==false)
		std::cout<<"could not load MagnetPower.png. error in gameitself.update"<<std::endl;
	m_magnetPowerSprite.setTexture(m_magnetPowerTexture);
	m_powers[0].init(Power::SLOW_ENEMIES, 10, -1, 4);
	m_powers[1].init(Power::FREEZE_ENEMIES, 10, -1, 3);
	m_powers[2].init(Power::PRIZE_MAGNET, 10, -1, 8);
	m_powers[3].init(Power::CHARACTER_SHRINK, 10, -1, 3);
	m_powers[4].init(Power::CHARACTER_SPEED_BOOST, 6, -1, 1);
	m_nrPowers = 5;
	m_radiusModulator = 1.0f;
}

void Character::updatePowers(float dt)
{
	for(int i =0; i<m_nrPowers; i++)
		m_powers[i].update(dt);
}

void Character::updateVelocity(float dt)
{
	sf::Vector2f vel(0.0f,0.0f);

	//Keyboard
	sf::Vector2f charKbDirUp;
	sf::Vector2f charKbDirDown;
	sf::Vector2f charKbDirLeft;
	sf::Vector2f charKbDirRight;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		charKbDirLeft = Math::UnitVectorFromAngle(180.0f, true);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		charKbDirRight = Math::UnitVectorFromAngle(0.0f, true);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		charKbDirUp = Math::UnitVectorFromAngle(270, true);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		charKbDirDown = Math::UnitVectorFromAngle(90.0f, true);
	
	vel = Math::Normalize(charKbDirUp + charKbDirDown + charKbDirLeft + charKbDirRight);
	vel.x *= 400 * m_speedModulator;
	vel.y *= 400 * m_speedModulator;

	//Joystick
	vel.x += sf::Joystick::getAxisPosition(0, sf::Joystick::X)/100*200 * m_speedModulator;
	vel.y += sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/100*200 * m_speedModulator; 
	if (Math::Modul(vel)<0.2f*200)
	{
		vel.x=0;
		vel.y=0;
	}
	setVelocity(vel);
}

void Character::update(float dt)
{
	updateVelocity(dt);
	m_position = m_position + m_velocity*dt;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		m_powers[0].activate();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		m_powers[1].activate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		m_powers[2].activate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		m_powers[3].activate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		m_powers[4].activate();

	for(int i =0; i<m_nrPowers; i++)
		applyPower(m_powers[i]);
}

void Character::draw(sf::RenderTarget& renderTarget)
{

	// draw character
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.0f,m_sprite.getTexture()->getSize().y/2.0f);
	m_sprite.setScale(1.0f/m_texture.getSize().x*getHitboxRadius()*2,1.0f/m_texture.getSize().y*getHitboxRadius()*2);
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_directionAngle*Math::Rad2Deg);
	renderTarget.draw(m_sprite);
	if(hasPowerOfType(Power::PRIZE_MAGNET))
	{
		if(getPowerByType(Power::PRIZE_MAGNET).isActive())
		{
			m_magnetPowerSprite = m_sprite;
			m_magnetPowerSprite.setTexture(m_magnetPowerTexture);
			renderTarget.draw(m_magnetPowerSprite);
		}
	}
}
void Character::setVelocity(sf::Vector2f newVelocity)
{
	m_velocity=newVelocity;
	if(m_velocity.x != 0 || m_velocity.y != 0)
		m_directionAngle=atan2(m_velocity.y,m_velocity.x);//angle between vector m_velocity with Ox axis
}

sf::Vector2f Character::getPosition()
{
	return m_position;
}

void Character::setPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
}

float Character::getHitboxRadius()
{
	return m_hitboxRadius * m_radiusModulator;
}

void Character::applyPower(Power& power)
{
	switch(power.getType())
	{
		case Power::CHARACTER_SHRINK:
		{
				if(power.justActivated())
				{
					m_radiusModulator = 0.5f;
				}
				else
					if(power.justFinished())
					{
						m_radiusModulator = 1.0f;
					}
					break;
		}

		case Power::CHARACTER_SPEED_BOOST:
		{
			if(power.justActivated())
			{
				m_speedModulator = 3;
			}
			else
				if(power.justFinished())
				{
					m_speedModulator = 1;
				}
			break;
		}
	}

}

Power& Character::getPower(int i)
{
	return m_powers[i];
}

int Character::getNrPowers()
{
	return m_nrPowers;
}

bool Character::hasPowerOfType(int type)
{
	for(int i=0; i< m_nrPowers; i++)
		if(m_powers[i].getType() == type)
			return true;
	return false;
}

Power& Character::getPowerByType(int type)
{
	for(int i=0; i< m_nrPowers; i++)
		if(m_powers[i].getType() == type)
			return m_powers[i];
	return m_powers[0];
}

sf::Vector2f Character::getVelocity()
{
	return m_velocity;
}
