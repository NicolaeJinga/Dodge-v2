#include "HUD.h"
#include<iostream>

HUD::HUD()
{
	m_panels.clear();
}

void HUD::init()
{
	for(int i=0;i<(int)m_panels.size();i++)
		m_panels[i]->init();
	
}

void HUD::addPanel(Panel* panel2BeAdded)
{
	m_panels.push_back(panel2BeAdded);
}


void HUD::update(float dt)
{
	for(int i=0;i<(int)m_panels.size();i++)
		m_panels[i]->update(dt);
}

void HUD::draw(sf::RenderTarget& renderTarget)
{

	for(int i=0;i<(int)m_panels.size();i++)
		m_panels[i]->draw(renderTarget);
}

void HUD::deletePanel(Panel* panel2BeDeleted)
{
	std::vector<Panel*>::iterator panel2BeDeletedIterator = std::find(m_panels.begin(),m_panels.end(),panel2BeDeleted);
	if(panel2BeDeletedIterator!=m_panels.end())
	{
		delete (*panel2BeDeletedIterator);
		m_panels.erase(panel2BeDeletedIterator);
	}
}

void HUD::clearAll()
{
	for(std::vector<Panel*>::iterator currentPanelIterator = m_panels.begin(); currentPanelIterator!=m_panels.end(); currentPanelIterator++)
	{
		(*currentPanelIterator)->clearAll();
		delete (*currentPanelIterator);
	}
	m_panels.clear();
}