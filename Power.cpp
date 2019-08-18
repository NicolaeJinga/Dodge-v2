#include "Power.h"
#include <iostream>

Power::Power()
{
	m_type=NO_POWER;
	m_cooldown=0;
	m_nrUsagesLeft=0;
	m_duration=0;
	m_ellapsedTime = 0;
	m_wasActive = false;
	m_isActive = false;
}

void Power::init(Power::PowerType tip, float cd, int nrUsages, float duration)
{
	m_type = tip;
	m_cooldown = cd;
	m_nrUsagesLeft = nrUsages;
	m_duration = duration;
	m_ellapsedTime = m_cooldown;
	m_wasActive = false;
	m_isActive = false;
}

char* Power::getTypeAsString()
{
	switch (m_type)
	{
	case 0:
		return "NO POWER";
		break;
	case 1:
		return "PLAYER SHRINK (U)";
		break;
	case 2:
		return "PRIZE MAGNET (L)";
		break;
	case 3:
		return "FREEZE ENEMIES (K)";
		break;
	case 4:
		return "SLOW ENEMIES (J)";
		break;
	case 5:
		return "PLAYER SPEED BOOST (I)";
		break;
	default:
		return "UNKNOWN POWER";
	}
}

int Power::getType()
{
	return m_type;
}

float Power::getCooldown()
{
	return m_cooldown;
}

int Power::getNrUsagesLeft()
{
	return m_nrUsagesLeft;
}

float Power::getDuration()
{
	return m_duration;
}

float Power::getEllapsedTime()
{
	return m_ellapsedTime;
}

bool Power::isReady()
{
	if(getEllapsedTime()>=m_cooldown)
		return true;
	return false;
}

bool Power::isOnCooldown()
{
	if(getEllapsedTime()<m_cooldown)
		return true;
	return false;
}

bool Power::isActive()
{
	return m_isActive;
}

bool Power::hasUsagesLeft()
{
	if(getNrUsagesLeft()>0 || getNrUsagesLeft() == -1)
		return true;
	return false;
}

bool Power::activate()
{
	if(!isReady() || !hasUsagesLeft())
		return false;
	if(m_nrUsagesLeft!= -1)
	{
		m_nrUsagesLeft--;
		std::cout<<m_nrUsagesLeft<<std::endl;
	}
	m_isActive = true;
	m_ellapsedTime=0;
	//sunet
	//effect
	return true;
}

bool Power::justActivated()
{
	return m_ellapsedTime==0;
}

bool Power::justFinished()
{
	return !isActive() && m_wasActive;
}

void Power::update(float dt)
{
	m_wasActive = m_isActive;
	if(isActive())
	{
		m_isActive = m_ellapsedTime < getDuration();
	}
	m_ellapsedTime += dt;
}

float Power::getRemainingTime()
{
	float remainingTime = getDuration()-getEllapsedTime();
	if(remainingTime >= 0)
	{
		return remainingTime;
	}
	else
	{
		return 0;
	}
}

float Power::getRemainingCooldown()
{
	float remainingTime = getCooldown()-getEllapsedTime();
	if(remainingTime >= 0)
	{
		return remainingTime;
	}
	else
	{
		return 0;
	}
}