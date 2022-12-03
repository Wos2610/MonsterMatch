#include "GSEnd.h"

GSEnd::GSEnd()
{
	m_nextLevelButton = new GameButton();
	m_menuButton = new GameButton();
	m_restartButton = new GameButton();

	m_frame = new sf::Sprite;
	m_banner = new sf::Sprite;
	m_background = new sf::Sprite;
	m_title = new sf::Text;

	m_monster = new Enemy();

	temp = 0;
	m_currentTime = 0.f;
	m_clickTime = 0.f;
}

GSEnd::~GSEnd()
{
	if (m_nextLevelButton != nullptr) {
		delete m_nextLevelButton;
	}
	if (m_menuButton != nullptr) {
		delete m_menuButton;
	}
	if (m_restartButton != nullptr) {
		delete m_restartButton;
	}

	if (m_frame != nullptr) {
		delete m_frame;
	}
	if (m_banner != nullptr) {
		delete m_banner;
	}
	if (m_background != nullptr) {
		delete m_background;
	}
	if (m_monster != nullptr) {
		delete m_monster;
	}

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

void GSEnd::initButton()
{


	m_frame->setTexture(*DATA->getTexture("cat1"));
	m_frame->setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2 - 180);
	m_frame->setOrigin((sf::Vector2f)m_frame->getTexture()->getSize() / 2.f);
	m_frame->setScale((float)0.7, (float)0.7);

	m_background->setTexture(*DATA->getTexture("bg9"));
	m_background->setScale(1, 1);

	// Menu 
	m_menuButton->Init();
	m_menuButton->setOnClick([]() {
		GSM->PopState();
		GSM->PopState();
		});
	m_menuButton->setSize({ 201, 219 });
	m_menuButton->setTexture(DATA->getTexture("Button/menu"));
	m_menuButton->setPosition((float)SCREENWIDTH / 2 - 150, (float)SCREENHEIGHT / 2.f + 70);
	m_menuButton->setOrigin((sf::Vector2f)m_menuButton->getSize() / 2.f);
	m_menuButton->setScale({ (float)(1 / 2.2), (float)(1 / 2.2) });

	// Restart
	m_restartButton->Init();
	m_restartButton->setOnClick([]() {
		GSM->PopState();
		GSM->PopState();
		GSM->ChangeState(STATE_PLAY);
		});
	m_restartButton->setSize({ 203, 225 });
	m_restartButton->setTexture(DATA->getTexture("Button/restart"));
	m_restartButton->setPosition((float)SCREENWIDTH / 2 , (float)SCREENHEIGHT / 2.f + 60);
	m_restartButton->setOrigin((sf::Vector2f)m_restartButton->getSize() / 2.f);
	m_restartButton->setScale({ (float)(1 / 2.5), (float)(1 / 2.5) });

	// Next level
	m_nextLevelButton->Init();
	m_nextLevelButton->setOnClick([]() {
		if (DATA->getLevel() != 16) {
			DATA->setIsNextLevel(true);
			GSM->PopState();
			GSM->PopState();
		}
		});
	m_nextLevelButton->setSize({ 203, 225 });
	if (DATA->getLevel() == 16) {
		m_nextLevelButton->setTexture(DATA->getTexture("Button/end"));
	}
	else {
		m_nextLevelButton->setTexture(DATA->getTexture("Button/next"));
	}
	m_nextLevelButton->setPosition((float)SCREENWIDTH / 2 + 150, (float)SCREENHEIGHT / 2.f + 60);
	m_nextLevelButton->setOrigin((sf::Vector2f)m_nextLevelButton->getSize() / 2.f);
	m_nextLevelButton->setScale({ (float)(1 / 2.5), (float)(1 / 2.5) });


}

void GSEnd::initText()
{
	m_title->setFont(*DATA->getFont("Toriko"));
	m_title->setCharacterSize(90);
	m_title->setString("LEVEL COMPLETED");
	m_title->setFillColor({ 253,247,240 });
	m_title->setOutlineColor({ 65,34,32 });
	m_title->setOutlineThickness(8);
	m_title->setOrigin(m_title->getGlobalBounds().width / 2, m_title->getGlobalBounds().height /2);
	m_title->setPosition({ SCREENWIDTH / 2 + 10, SCREENHEIGHT / 2 - 140 });
}

void GSEnd::initMonster()
{
	m_monster->Init({ SCREENWIDTH / 2 - 400, SCREENHEIGHT / 2 - 200 }, "monster_1", { 7, 1 }, 2);
	m_monster->setScale({ 12, 12 });
}

StateTypes GSEnd::getTypeState()
{
	return STATE_PAUSE;
}

void GSEnd::Init()
{
	cout << "GSEnd\n";

	initButton();
	initMonster();
	initText();
	
	DATA->setLevelCompleted(DATA->getLevel());

}

void GSEnd::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_clickTime + 0.07) {
		m_menuButton->Update(deltaTime);
		m_nextLevelButton->Update(deltaTime);
		m_restartButton->Update(deltaTime);
		m_clickTime = m_currentTime;
	}
}

void GSEnd::Render(sf::RenderWindow* window)
{
	window->draw(*m_background);
	window->draw(*m_frame);
	window->draw(*m_title);

	/*m_monster->Render(window);*/
	m_menuButton->Render(window);
	m_nextLevelButton->Render(window);
	m_restartButton->Render(window);
	
}


