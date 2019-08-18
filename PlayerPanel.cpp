#include "PlayerPanel.h"
#include "Player.h"

PlayerPanel::PlayerPanel(Player* player)
{
	m_player = player;
}

void PlayerPanel::init()
{
	m_fieldScore.init("Score: ", "INVALID", this);
	for (int i = 0; i < 5; ++i)
	{
		m_fieldType[i].init("Type: ", "INVALID", this);
		m_fieldCooldown[i].init("Cooldown: ", "INVALID", this);
		m_fieldDuration[i].init("Duration: ", "INVALID", this);
		m_fieldUsages[i].init("Usages: ", "INVALID", this);
		addField(&m_fieldType[i]);
		addField(&m_fieldDuration[i]);
		addField(&m_fieldCooldown[i]);
		addField(&m_fieldUsages[i]);
	}

	addField(&m_fieldScore);
	
	autoPositionFields(15.0f);
}

void PlayerPanel::update(float dt)
{
	m_fieldScore.setValue(m_player->m_score);
	for (int i = 0; i < 5; ++i)
	{
		m_fieldType[i].setValue(m_player->m_character->getPower(i).getTypeAsString());
		m_fieldDuration[i].setValue(m_player->m_character->getPower(i).getRemainingTime());
		m_fieldUsages[i].setValue(m_player->m_character->getPower(i).getNrUsagesLeft());
		m_fieldCooldown[i].setValue(m_player->m_character->getPower(i).getRemainingCooldown());
	}
	
	Panel::update(dt);
}

