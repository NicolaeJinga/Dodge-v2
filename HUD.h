#ifndef __HUD_H__
#define __HUD_H__

#include "SFML\Graphics.hpp"
#include "Panel.h"

class HUD
{
	std::vector<Panel*> m_panels;
public:
	HUD();
	void init();
	void addPanel(Panel* panel2BeAdded);
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void deletePanel(Panel* panel2bBeDeleted);
	void clearAll();
};


#endif //__HUD_H__