#ifndef __FIELD_H__
#define __FIELD_H__


#include "SFML\Graphics.hpp"

class Panel;

class Field
{
public:
	
	sf::Text m_fieldName;
	sf::Text m_fieldValue;
	sf::Vector2f m_position;
	Panel* m_parentPanel;
	sf::Font m_fieldFont;

	Field();
	void init(char* fieldName, char* fieldValue, Panel* parentPanel, sf::Vector2f position=sf::Vector2f(0.0f,0.0f));
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
	void setValue(int value);
	void setValue(float value);
	void setValue(char* value);
	void setValue(bool value);
	float getHeight();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
};

#endif //__FIELD_H__