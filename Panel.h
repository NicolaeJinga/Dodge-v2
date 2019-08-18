#ifndef __PANEL_H__
#define __PANEL_H__
#include<vector>
#include "Field.h"
#include "SFML\System\Vector2.hpp"

class Panel
{
protected:
	std::vector<Field*> m_fields;
	sf::Vector2f m_position;
public:
	Panel();
	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition();
	virtual void addField(Field* field2BeAdded);
	virtual void init();
	virtual void update(float dt);
	virtual void draw(sf::RenderTarget& renderTarget);
	virtual void autoPositionFields(float spacingY);
	virtual void deleteField(Field* filed2BeDeleted);
	virtual void clearAll();
};

#endif // __PANEL_H__