#ifndef __POWER_H__
#define __POWER_H__

class Power
{
	
public:

	enum PowerType
	{
		NO_POWER = 0,
		CHARACTER_SHRINK,
		PRIZE_MAGNET,
		FREEZE_ENEMIES,
		SLOW_ENEMIES,
		CHARACTER_SPEED_BOOST,
		COUNT
	};

private:

	PowerType m_type; //type of power
	float m_cooldown; //cooldown. it starts as soon as the power is activated
	int m_nrUsagesLeft; //number of times a power can be activated
	float m_duration; //how much time the power is active after it has been activated
	float m_ellapsedTime; //time elapsed since activation
	bool m_isActive; //is true if the power is currently active
	bool m_wasActive; //true if the power was active the previous frame

public:
	Power();
	void init(PowerType tip, float cd, int nrUsages, float duration);
	int getType();
	char* getTypeAsString();
	float getCooldown();
	float getRemainingCooldown();
	int getNrUsagesLeft();
	float getDuration();
	float getEllapsedTime();
	float getRemainingTime();
	bool isReady();
	bool isOnCooldown();
	bool isActive();
	bool hasUsagesLeft();
	bool activate();
	bool justActivated();
	bool justFinished();
	void update(float dt);

};

#endif //__POWER_H__