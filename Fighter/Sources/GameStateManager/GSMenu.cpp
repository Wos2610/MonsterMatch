#include "GSMenu.h"

GSMenu::GSMenu()
{
	m_sprite = new sf::Sprite;
	m_frame = new sf::Sprite;

	m_title = new sf::Text;

	m_currentTime = 0.f;
	m_clickTime = 0.f;

	button = new GameButton();
}

GSMenu::~GSMenu()
{
	if (m_sprite != nullptr) {
		delete m_sprite;
	}
	if (m_frame != nullptr) {
		delete m_frame;
	}
	if (m_title != nullptr) {
		delete m_title;
	}
}

void GSMenu::Exit()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::initButton()
{
	//Exit Button
	button = new GameButton();
	button->Init();
	button->setSize({ 203, 225 });
	button->setTexture(DATA->getTexture("Button/power"));
	button->setPosition(SCREENWIDTH - 10, (float) button->getSize().y/3 + 10);
	button->setOrigin(button->getSize());
	button->setScale({ (float)1/3, (float)1/3 });
	button->setOnClick([]() {WConnect->getWindow()->close(); });
	m_ListButton.push_back(button);

	//Play Button
	button = new GameButton();
	button->Init();
	button->setOnClick([]() {GSM->ChangeState(StateTypes::STATE_LEVEL); });
	button->setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	button->setTexture(DATA->getTexture("Button/play"));
	button->setOrigin(button->getSize() / 2.f);
	m_ListButton.push_back(button);

	//Setting Button
	button = new GameButton();
	button->Init();
	button->setOnClick([]() {GSM->ChangeState(StateTypes::STATE_SETTING); });
	button->setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2 + 130);
	button->setTexture(DATA->getTexture("Button/setting"));
	button->setOrigin(button->getSize() / 2.f);
	m_ListButton.push_back(button);

	//About Button
	button = new GameButton();
	button->Init();
	button->setOnClick([]() {GSM->ChangeState(StateTypes::STATE_ABOUT); });
	button->setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2 + 255);
	button->setTexture(DATA->getTexture("Button/about"));
	button->setOrigin(button->getSize() / 2.f);
	m_ListButton.push_back(button);
}

void GSMenu::initText()
{

	// Title Game
	m_title = new sf::Text;
	m_title->setFont(*DATA->getFont("Black_Ops_One/BlackOpsOne-Regular"));
	m_title->setCharacterSize(120);
	m_title->setString("MONSTER MATCH");
	m_title->setOutlineColor({ 0,180,216 });
	m_title->setFillColor({ 233,237,201 });
	m_title->setOutlineThickness(9);
	m_title->setPosition({ SCREENWIDTH / 2  - 530, SCREENHEIGHT / 4 - 100});
	m_vectorTitle.push_back(m_title);

	// Play
	m_title = new sf::Text;
	m_title->setFont(*DATA->getFont("Nova_Flat/NovaFlat-Regular"));
	m_title->setCharacterSize(60);
	m_title->setString("PLAY");
	m_title->setFillColor(sf::Color::White);
	m_title->setPosition({ SCREENWIDTH / 3 + 200 , SCREENHEIGHT / 3 + 112 });
	m_vectorTitle.push_back(m_title);

	// Setting
	m_title = new sf::Text;
	m_title->setFont(*DATA->getFont("Nova_Flat/NovaFlat-Regular"));
	m_title->setCharacterSize(60);
	m_title->setString("SETTING");
	m_title->setFillColor(sf::Color::White);
	m_title->setPosition({ SCREENWIDTH / 3 + 165 , SCREENHEIGHT / 3 + 237 });
	m_vectorTitle.push_back(m_title);

	// About
	m_title = new sf::Text;
	m_title->setFont(*DATA->getFont("Nova_Flat/NovaFlat-Regular"));
	m_title->setCharacterSize(60);
	m_title->setString("ABOUT");
	m_title->setFillColor(sf::Color::White);
	m_title->setPosition({ SCREENWIDTH / 3 + 185 , SCREENHEIGHT / 3 + 365 });
	m_vectorTitle.push_back(m_title);

}

StateTypes GSMenu::getTypeState()
{
	return STATE_MENU;
}

void GSMenu::Init()
{
	printf("GSMenu\n");

	DATA->playMusic("song");

	m_sprite->setTexture(*DATA->getTexture("bg16"));
	m_sprite->setScale(1, 1);

	m_frame->setTexture(*DATA->getTexture("Button/3"));
	m_frame->setPosition(SCREENWIDTH / 2 - 270, SCREENHEIGHT / 2 - 130);
	m_frame->setScale((float)0.6, (float)0.6);
	
	initButton();
	initText();
	

}

void GSMenu::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	
	DATA->updateMusic();

	for (auto button : m_ListButton) {
		button->Update(deltaTime);
	}
}

void GSMenu::Render(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
	window->draw(*m_frame);
	
	for (auto button : m_ListButton) {
		button->Render(window);
	}

	for (auto title : m_vectorTitle) {
		window->draw(*title);
	}
	
}



