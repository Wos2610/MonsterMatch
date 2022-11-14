#include "GameButton.h"


GameButton::GameButton()
{
	// Khi bat dau game
	m_isHandling = false;
}

GameButton::~GameButton()
{
}

void GameButton::Init()
{
	this->setSize(sf::Vector2f(100, 100));
	this->setFillColor(sf::Color::Green);
}

void GameButton::Update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		HandleTouchEvent();
	}
}

void GameButton::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

void GameButton::HandleTouchEvent()
{
	m_isHandling = false;
	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow()))) {
		m_buttonClickFunction();
		m_isHandling = true;
	}
}

bool GameButton::isHandle()
{
	return m_isHandling;
}

void GameButton::setOnClick(void(*Func)())
{
	m_buttonClickFunction = Func;
}