#include "GSAbout.h"

GSAbout::GSAbout()
{

	m_frame = new sf::Sprite;
	m_background = new sf::Sprite;
	m_title = new sf::Text;

	m_backButton = new GameButton();

	m_currentTime = 0.f;
	m_changeTime = 0.f;
}

GSAbout::~GSAbout()
{
	if (m_frame != nullptr) {
		delete m_frame;
	}
	if (m_background != nullptr) {
		delete m_background;
	}
	if (m_backButton != nullptr) {
		delete m_backButton;
	}
}

void GSAbout::Exit()
{
}

void GSAbout::Pause()
{
}

void GSAbout::Resume()
{
}

void GSAbout::initButton()
{
	m_background->setTexture(*DATA->getTexture("info"));
	
	// Back Button
	m_backButton->Init();
	m_backButton->setOnClick([]() {GSM->PopState(); });
	m_backButton->setSize({ 203, 225 });
	m_backButton->setTexture(DATA->getTexture("Button/return"));
	m_backButton->setPosition(0, 0);
	m_backButton->setScale({ (float)1 / 3, (float)1 / 3 });

}

void GSAbout::initText()
{
	m_title->setFont(*DATA->getFont("Bungee/Bungee-Regular"));
	m_title->setCharacterSize(80);
	m_title->setString("HOW TO PLAY");
	m_title->setOutlineColor({ 255,159,159 });
	m_title->setOutlineThickness(6);
	m_title->setFillColor({ 248,228,219 });
	m_title->setPosition({ SCREENWIDTH / 3 - 20 , SCREENHEIGHT / 23 });
}

StateTypes GSAbout::getTypeState()
{
	return STATE_ABOUT;
}

void GSAbout::Init()
{
	cout << "GSAbout\n";

	initButton();
	initText();

}

void GSAbout::Update(float deltaTime)
{
	m_backButton->Update(deltaTime);
}

void GSAbout::Render(sf::RenderWindow* window)
{
	window->draw(*m_background);
	window->draw(*m_title);

	m_backButton->Render(window);
}


