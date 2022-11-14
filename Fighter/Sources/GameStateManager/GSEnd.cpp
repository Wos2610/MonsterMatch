#include "GSEnd.h"

GSEnd::GSEnd()
{
	m_complete = new sf::Text();
}

GSEnd::~GSEnd()
{
}

void GSEnd::Exit()
{
}

void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}



void GSEnd::initText()
{
	m_complete->setFont(*DATA->getFont("Texturina-ExtraBold"));
	m_complete->setString("Level Complete!\n");
}

void GSEnd::Init()
{
	this->initText();
}

void GSEnd::Update(float deltaTime)
{
}

void GSEnd::Render(sf::RenderWindow* window)
{
	window->draw(*m_complete);
}