#include "PSAttack.h"


PSAttack::PSAttack(IPlayer* player)
{
	m_player = player;
}

void PSAttack::setPosition(sf::Vector2f pos)
{
	m_animation->setPosition(pos);
}

sf::Vector2f PSAttack::getPosition()
{
	return m_animation->getPosition();
}

void PSAttack::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	sf::Texture* texture = new sf::Texture();
	texture = DATA->getTexture("ATTACK/" + name);
	m_animation = new Animation(*texture, frameSheetSize, 0.1f);
	m_animation->setPosition(startPos);
	m_animation->setScale({ -6, 6 });

}

void PSAttack::Update(float deltaTime)
{
	/*m_currentTime += deltaTime;
	if (m_currentTime <= 1.f) {
		m_animation->Update(deltaTime);
	}*/
	m_animation->Update(deltaTime);
}

void PSAttack::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}


