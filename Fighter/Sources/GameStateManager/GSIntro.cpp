#include "GSIntro.h"

GSIntro::GSIntro()
{
	m_currentTime = 0.f;
	alpha = 10;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Exit()
{
}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Init()
{
	printf("Init GSIntro\n");
	sf::Texture* texture = new sf::Texture;
	texture = DATA->getTexture("LogoProPTIT");
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin((sf::Vector2f)texture->getSize() / 2.f);
	m_sprite.setScale(0.5, 0.5);
	m_sprite.setPosition({ SCREENWIDTH / 2, SCREENHEIGHT / 2 });
	/*m_sprite.setColor({ 255, 255, 255, 255 });*/
	/*sf::Image *image = new sf::Image;
	image = DATA->getTexture("LogoProPTIT");*/
}

void GSIntro::Update(float deltaTime)
{	
	m_sprite.setColor({ 255, 255, 255, alpha });
	m_currentTime += deltaTime;
	if (alpha <= 255) {
		alpha += 1;
	}
	// 3.f
	if (m_currentTime >= 3.5f) {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_MENU);
	}
}

void GSIntro::Render(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}


StateTypes GSIntro::getTypeState()
{
	return STATE_INTRO;
}
