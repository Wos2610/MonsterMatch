#include "ESDeath.h"


ESDeath::ESDeath(IEnemy* player)
{
	m_player = player;
}


void ESDeath::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	sf::Texture* texture = new sf::Texture();
	texture = DATA->getTexture("DEATH/" + name);
	m_animation = new Animation(*texture, frameSheetSize, 0.1f);
	m_animation->setPosition(startPos);
	m_animation->setScale({ 3, 3 });

}

void ESDeath::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime <= 1.f) {
		m_animation->Update(deltaTime);
	}
	/*m_animation->Update(deltaTime);*/
}

void ESDeath::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}
