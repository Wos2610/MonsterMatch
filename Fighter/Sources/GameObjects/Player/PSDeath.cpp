#include "PSDeath.h"


PSDeath::PSDeath(IPlayer* player)
{
	m_player = player;
}


void PSDeath::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	sf::Texture* texture = new sf::Texture();
	texture = DATA->getTexture("IDLE/" + name);
	m_animation = new Animation(*DATA->getTexture(name), frameSheetSize, 0.1f);
	m_animation->setPosition(startPos);
	m_animation->setScale({ -6.f, 6.f });

}

void PSDeath::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void PSDeath::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

void PSDeath::setPosition(sf::Vector2f pos)
{
}
