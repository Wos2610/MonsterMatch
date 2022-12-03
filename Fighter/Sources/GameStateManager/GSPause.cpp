#include "GSPause.h"

GSPause::GSPause()
{
	m_resumeButton = new GameButton();
	m_restartButton = new GameButton();
	m_menuButton = new GameButton();
	m_soundButton = new GameButton();

	m_frame = new sf::Sprite;
	m_background = new sf::Sprite;
	m_title = new sf::Text;

	m_monster = new Enemy();

	temp = 0;
	m_currentTime = 0.f;
	m_changeTime = 0.f;
	m_clickTime = 0.f;
}

GSPause::~GSPause()
{
	if (m_resumeButton != nullptr) {
		delete m_resumeButton;
	}
	if (m_restartButton != nullptr) {
		delete m_restartButton;
	}
	if (m_menuButton != nullptr) {
		delete m_menuButton;
	}
	if (m_soundButton != nullptr) {
		delete m_soundButton;
	}
	if (m_frame != nullptr) {
		delete m_frame;
	}
	if (m_background != nullptr) {
		delete m_background;
	}
	if (m_monster != nullptr) {
		delete m_monster;
	}

}

void GSPause::Exit()
{
}

void GSPause::Pause()
{
}

void GSPause::Resume()
{
}

void GSPause::initButton()
{

	m_frame->setTexture(*DATA->getTexture("Button/2"));
	m_frame->setPosition((float)(SCREENWIDTH - 0.8 * m_frame->getGlobalBounds().width)/2.f, (float)(SCREENHEIGHT - 0.6 * m_frame->getGlobalBounds().height - 50));
	/*m_frame->setOrigin((sf::Vector2f)m_frame->getTexture()->getSize() / 2.f);*/
	m_frame->setScale((float)0.8, (float)0.6);
	m_background->setTexture(*DATA->getTexture("pause"));
	m_background->setOrigin((sf::Vector2f) DATA->getTexture("pause")->getSize());
	m_background->setPosition(SCREENWIDTH + 30, SCREENHEIGHT);
	m_background->setScale((float)1.9, (float)1.9);

	// Menu 
	m_menuButton->Init();
	m_menuButton->setOnClick([]() {
		GSM->PopState();
		GSM->PopState();
		GSM->PopState();
		GSM->PopState();
		});
	m_menuButton->setSize({ 201, 219 });
	m_menuButton->setTexture(DATA->getTexture("Button/home"));
	m_menuButton->setPosition((float)SCREENWIDTH/2 - 380, (float)SCREENHEIGHT/2.f + 300);
	m_menuButton->setOrigin((sf::Vector2f)m_menuButton->getSize()/2.f);
	m_menuButton->setScale({ (float)(1 / 1.8), (float)(1 / 1.8) });

	// Restart
	m_restartButton->Init();
	m_restartButton->setOnClick([]() {
		GSM->PopState();
		GSM->PopState();
		GSM->ChangeState(STATE_PLAY);
		});
	m_restartButton->setSize({ 203, 225 });
	m_restartButton->setTexture(DATA->getTexture("Button/restart"));
	m_restartButton->setPosition((float)SCREENWIDTH / 2 - 130, (float)SCREENHEIGHT / 2.f + 300);
	m_restartButton->setOrigin((sf::Vector2f)m_restartButton->getSize()/2.f);
	m_restartButton->setScale({ (float)(1 / 1.8), (float)(1 / 1.8)});

	// Resume
	cout << "reeee";
	m_resumeButton->Init();
	m_resumeButton->setOnClick([]() {GSM->PopState(); });
	m_resumeButton->setSize({ 203, 225 });
	m_resumeButton->setTexture(DATA->getTexture("Button/resume"));
	m_resumeButton->setPosition((float)SCREENWIDTH / 2 + 120, (float)SCREENHEIGHT / 2.f + 300);
	m_resumeButton->setOrigin((sf::Vector2f)m_resumeButton->getSize() / 2.f);
	m_resumeButton->setScale({ (float)(1 / 1.9), (float)(1 / 1.9) });

	// Sound
	m_soundButton->Init();
	m_soundButton->setOnClick([]() {
		if (DATA->isAllowSound()) {
			DATA->setAllowSound(false);
		}
		else {
			DATA->setAllowSound(true);
		}
		});
	m_soundButton->setSize({ 203, 225 });
	if (DATA->isAllowSound()) {
		m_soundButton->setTexture(DATA->getTexture("Button/SoundOn"));
	}
	else {
		m_soundButton->setTexture(DATA->getTexture("Button/SoundOff"));
	}
	m_soundButton->setPosition((float)SCREENWIDTH / 2 + 370, (float)SCREENHEIGHT / 2.f + 300);
	m_soundButton->setOrigin((sf::Vector2f)m_soundButton->getSize() / 2.f);
	m_soundButton->setScale({ (float)(1 / 1.9), (float)(1 / 1.9) });

}

void GSPause::initText()
{
	m_title->setFont(*DATA->getFont("Toriko" ));
	m_title->setCharacterSize(100);
	m_title->setString("LEVEL : " + to_string(DATA->getLevel()));
	m_title->setFillColor(sf::Color::White);
	m_title->setOutlineColor({ 194,110,95 });
	m_title->setOutlineThickness(13);
	m_title->setPosition({ SCREENWIDTH / 3 + 150 , SCREENHEIGHT / 6 - 150});
}

void GSPause::initMonster()
{
	m_monster->Init({ SCREENWIDTH/2 - 350, SCREENHEIGHT/2 - 200}, "monster_1", {7, 1}, 2);
	m_monster->setScale({ 12, 12 });
	temp = 80;
}

StateTypes GSPause::getTypeState()
{
	return STATE_PAUSE;
}

void GSPause::Init()
{
	cout << "GSPause\n";

	initButton();
	initMonster();
	initText();
	
}

void GSPause::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	m_monster->Update(deltaTime);
	if (m_currentTime > (m_changeTime + 1.5)) {
		if (temp < (SCREENWIDTH - 950)) {
			temp += 200;
			m_changeTime = m_currentTime;
		}
		else {
			temp = 80;
			m_changeTime = m_currentTime;
		}	
	}


	if (m_currentTime > m_clickTime + 0.07) {
		m_menuButton->Update(deltaTime);
		m_resumeButton->Update(deltaTime);
		m_restartButton->Update(deltaTime);
		if (DATA->isAllowSound()) {
			m_soundButton->setTexture(DATA->getTexture("Button/SoundOn"));
		}
		else {
			m_soundButton->setTexture(DATA->getTexture("Button/SoundOff"));
		}
		m_soundButton->Update(deltaTime);
		m_clickTime = m_currentTime;
	}
	
	m_monster->setPosition({ (float)temp, (float)SCREENHEIGHT / 2 - 200 });
	
}

void GSPause::Render(sf::RenderWindow* window)
{
	window->draw(*m_background);
	window->draw(*m_frame);
	window->draw(*m_title);

	m_monster->Render(window);
	m_menuButton->Render(window);
	m_resumeButton->Render(window);
	m_restartButton->Render(window);
	m_soundButton->Render(window);
}


