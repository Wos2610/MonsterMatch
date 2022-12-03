#include "GSSetting.h"

GSSetting::GSSetting()
{
	
	m_backButton = new GameButton();
	m_soundButton = new GameButton();
	m_musicButton = new GameButton();

	m_frame = new sf::Sprite;
	m_background = new sf::Sprite;
	m_title = new sf::Text;

	m_monster = new Enemy();

	temp = 0;
	m_currentTime = 0.f;
	m_clickTime = 0.f;
}

GSSetting::~GSSetting()
{
	if (m_backButton != nullptr) {
		delete m_backButton;
	}
	if (m_soundButton != nullptr) {
		delete m_soundButton;
	}
	if (m_musicButton != nullptr) {
		delete m_musicButton;
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

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::initButton()
{

	m_background->setTexture(*DATA->getTexture("bg19"));

	// Back Button
	m_backButton->Init();
	m_backButton->setOnClick([]() {GSM->PopState(); });
	m_backButton->setSize({ 203, 225 });
	m_backButton->setTexture(DATA->getTexture("Button/return"));
	m_backButton->setPosition(0, 0);
	m_backButton->setScale({ (float)1 / 3, (float)1 / 3 });

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
	m_soundButton->setSize({ 210, 210 });
	if (DATA->isAllowSound()) {
		m_soundButton->setTexture(DATA->getTexture("Button/SoundOn"));
	}
	else {
		m_soundButton->setTexture(DATA->getTexture("Button/SoundOff"));
	}
	m_soundButton->setPosition((float)SCREENWIDTH / 2 - 120, (float)SCREENHEIGHT / 2.f - 20);
	m_soundButton->setOrigin((sf::Vector2f)m_soundButton->getSize() / 2.f);
	m_soundButton->setScale({ (float)(1 / 1.8), (float)(1 / 1.8) });

	// Music
	m_musicButton->Init();
	m_musicButton->setOnClick([]() {
		if (DATA->isAllowMusic()) {
			DATA->setAllowMusic(false);
		}
		else {
			DATA->setAllowMusic(true);
		}
		});
	m_musicButton->setSize({ 210, 210 });
	if (DATA->isAllowMusic()) {
		m_musicButton->setTexture(DATA->getTexture("Button/MusicOn"));
	}
	else {
		m_musicButton->setTexture(DATA->getTexture("Button/MusicOff"));
	}
	m_musicButton->setPosition((float)SCREENWIDTH / 2 + 120, (float)SCREENHEIGHT / 2.f - 20);
	m_musicButton->setOrigin((sf::Vector2f)m_musicButton->getSize() / 2.f);
	m_musicButton->setScale({ (float)(1 / 1.8), (float)(1 / 1.8) });

}

void GSSetting::initText()
{
	m_title->setFont(*DATA->getFont("Bungee/Bungee-Regular"));
	m_title->setCharacterSize(80);
	m_title->setString("SETTING" );
	m_title->setOutlineColor({ 255,159,159 });
	m_title->setOutlineThickness(6);
	m_title->setFillColor({ 248,228,219 });
	m_title->setPosition({ SCREENWIDTH / 3 + 70 , SCREENHEIGHT / 4 });
}

StateTypes GSSetting::getTypeState()
{
	return STATE_SETTING;
}

void GSSetting::Init()
{
	cout << "GSSetting\n";

	initButton();
	initText();

}

void GSSetting::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	
	DATA->updateMusic();

	m_backButton->Update(deltaTime);

	if (m_currentTime > m_clickTime + 0.07) {
		if (DATA->isAllowSound()) {
			m_soundButton->setTexture(DATA->getTexture("Button/SoundOn"));
		}
		else {
			m_soundButton->setTexture(DATA->getTexture("Button/SoundOff"));
		}
		if (DATA->isAllowMusic()) {
			m_musicButton->setTexture(DATA->getTexture("Button/MusicOn"));
		}
		else {
			m_musicButton->setTexture(DATA->getTexture("Button/MusicOff"));
		}
		m_soundButton->Update(deltaTime);
		m_musicButton->Update(deltaTime);
		m_clickTime = m_currentTime;
	}

	
}

void GSSetting::Render(sf::RenderWindow* window)
{
	window->draw(*m_background);
	window->draw(*m_frame);
	window->draw(*m_title);

	m_backButton->Render(window);
	m_soundButton->Render(window);
	m_musicButton->Render(window);
}


