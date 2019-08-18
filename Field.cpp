#include "Field.h"
#include "Panel.h"
#include <iostream>

Field::Field()
{
	m_parentPanel = NULL;
}

void Field::init(char* fieldName, char* fieldValue, Panel* parentPanel, sf::Vector2f position)
{
	if(!m_fieldFont.loadFromFile("Resources/arial.ttf"))
	{
		std::cout<<"Couldn't load arial.tff in field.init"<<std::endl;
	}
	m_fieldName.setFont(m_fieldFont);
	m_fieldName.setString(sf::String(fieldName));
	m_fieldName.setCharacterSize(14);
	m_fieldValue.setFont(m_fieldFont);
	m_fieldValue.setString(sf::String(fieldValue));
	m_fieldValue.setCharacterSize(14);
	m_position = position;
	m_parentPanel = parentPanel;
}

void Field::update(float dt)
{
	
}

void Field::draw(sf::RenderTarget& renderTarget)
{
	if(m_parentPanel!=NULL)
		m_fieldName.setPosition(m_parentPanel->getPosition() + m_position + sf::Vector2f(5.0f,0.0f));
	else
		m_fieldName.setPosition(m_position);
	sf::Vector2f fieldValueOffset(m_fieldName.getLocalBounds().width + 15, 0.0f);
	m_fieldValue.setPosition(m_fieldName.getPosition()+fieldValueOffset);
	m_fieldName.setFillColor(sf::Color::Green);
	m_fieldValue.setFillColor(sf::Color::Red);
	renderTarget.draw(m_fieldName);
	renderTarget.draw(m_fieldValue);
}

void Field::setValue(int value)
{
	char valueAsString[20];
	if(value == -1)
	{
		_itoa_s(value,valueAsString,10);
		m_fieldValue.setString("Infinite");
	}
	else
	{
		_itoa_s(value,valueAsString,10);
		m_fieldValue.setString(sf::String(valueAsString));
	}
}

void Field::setValue(float value)
{
	char valueAsString[20];
	sprintf_s(valueAsString,"%.2f",value);
	m_fieldValue.setString(sf::String(valueAsString));
}

void Field::setValue(char* value)
{
	m_fieldValue.setString(sf::String(value));
}

void Field::setValue(bool value)
{
	if(value)
	{
		m_fieldValue.setString("True");
	}
	else
	{
		m_fieldValue.setString("False");
	}
}

float Field::getHeight()
{
	return m_fieldName.getLocalBounds().height;
}

void Field::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Field::getPosition()
{
	return m_position;
}
