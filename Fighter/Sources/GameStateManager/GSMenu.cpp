#include "GSMenu.h"

GSMenu::GSMenu()
{
	m_sprite = new sf::Sprite;
	m_currentTime = 0.f;
}

GSMenu::~GSMenu()
{
	if (m_sprite != nullptr) {
		delete m_sprite;
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

void GSMenu::Init()
{
	printf("GSMenu\n");
	

	m_sprite->setTexture(*DATA->getTexture("background"));
	m_sprite->setScale(3, 1.8);

	GameButton* button;
	//Exit Button
	button = new GameButton();
	button->Init();
	button->setOnClick([]() {WConnect->getWindow()->close(); });
	/*button->setTexture(*DATA->getTexture("Icon/Iem3"));*/
	m_ListButton.push_back(button);

	//Play Button
	button = new GameButton();
	button->Init();
	button->setOnClick([]() {GSM->ChangeState(StateTypes::STATE_PLAY); });
	button->setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	button->setFillColor(sf::Color::Red);
	button->setOrigin(button->getSize() / 2.f);
	m_ListButton.push_back(button);


}

void GSMenu::Update(float deltaTime)
{
	for (auto button : m_ListButton) {
		button->Update(deltaTime);
	}
}

void GSMenu::Render(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
	for (auto button : m_ListButton) {
		button->Render(window);
	}
}

