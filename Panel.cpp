#include "Panel.h"

Panel::Panel()
{
	m_fields.clear();
}

void Panel::init()
{

}

void Panel::addField(Field* field2BeAdded)
{
	m_fields.push_back(field2BeAdded);	
}

sf::Vector2f Panel::getPosition()
{
	return m_position;
}

void Panel::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Panel::update(float dt)
{
	for(int i=0; i<(int)m_fields.size();i++)
		m_fields[i]->update(dt);
}

void Panel::draw(sf::RenderTarget& renderTarget)
{
	for(int i=0;i<(int)m_fields.size();i++)
		m_fields[i]->draw(renderTarget);
}

void Panel::autoPositionFields(float spacingY)
{
	m_fields[0]->setPosition(sf::Vector2f(0.0f,0.0f));
	for(int i=1; i<(int)m_fields.size();i++)
		m_fields[i]->setPosition(m_fields[i-1]->getPosition()+sf::Vector2f(0.0f, m_fields[i-1]->getHeight()+spacingY));
}

void Panel::deleteField(Field* field2BeDeleted)
{
	std::vector<Field*>::iterator field2BeDeletedIterator = std::find(m_fields.begin(),m_fields.end(),field2BeDeleted);
	if(field2BeDeletedIterator!=m_fields.end())
		m_fields.erase(field2BeDeletedIterator);
}

void Panel::clearAll()
{
	m_fields.clear();
}
