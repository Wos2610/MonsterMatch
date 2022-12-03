#include "ESIdle.h"


ESIdle::ESIdle(IEnemy* player)
{
	m_player = player;
}


void ESIdle::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	sf::Texture* texture = new sf::Texture();
	texture = DATA->getTexture("IDLE/" + name);
	m_animation = new Animation(*texture, frameSheetSize, 0.1f);
	m_animation->setPosition(startPos);
	m_animation->setScale({ 3, 3 });

}

void ESIdle::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void ESIdle::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

void ESIdle::setScale(sf::Vector2f size)
{
	m_animation->setScale(size);
}

void ESIdle::setPosition(sf::Vector2f pos)
{
	m_animation->setPosition(pos);
}

sf::Vector2f ESIdle::getPosition()
{
	return m_animation->getPosition();
}
