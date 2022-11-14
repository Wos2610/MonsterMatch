#include "PSIdle.h"


PSIdle::PSIdle(IPlayer* player)
{
	m_player = player;
}


void PSIdle::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	sf::Texture* texture = new sf::Texture();
	texture = DATA->getTexture("IDLE/" + name);
	m_animation = new Animation(*texture, frameSheetSize , 0.1f);
	m_animation->setPosition(startPos);
	m_animation->setScale({-(float)frameNum, (float)frameNum});
	
}

void PSIdle::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void PSIdle::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

void PSIdle::setPosition(sf::Vector2f pos)
{
}
