#ifndef __CHARACTERPANEL_H__
#define __CHARACTERPANEL_H__
#include "Panel.h"
#include "Player.h"

class PlayerPanel : public Panel
{
	Field m_fieldCooldown[5];
	Field m_fieldDuration[5];
	Field m_fieldUsages[5];
	Field m_fieldType[5];
	Field m_fieldScore;
	Player* m_player;

public:

	PlayerPanel(Player* player);
	void update(float dt);
	void init();

};
#endif //__CHARACTERPANEL_H__