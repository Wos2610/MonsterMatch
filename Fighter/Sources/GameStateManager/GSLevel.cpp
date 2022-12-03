#include "GSLevel.h"

GSLevel::GSLevel()
{
	m_sprite = new sf::Sprite;
	m_background = new sf::Sprite;
	m_currentTime = 0.f;
	m_clickTime = 0.f;
	m_title = new sf::Text;

	m_mapNum = 16;

	m_mapButtonVector.resize(m_mapNum + 1, nullptr);

	for (int i = 0; i < m_mapNum; i++) {
		m_mapButtonVector[i] = new GameButton();
	}

	m_backButton = new GameButton();
}

GSLevel::~GSLevel()
{
	if (m_sprite != nullptr) {
		delete m_sprite;
	}
	if (m_background != nullptr) {
		delete m_background;
	}
	if (m_title != nullptr) {
		delete m_title;
	}
	for (int i = 0; i < m_mapNum; i++) {
		if (m_mapButtonVector[i] != nullptr) {
			delete m_mapButtonVector[i];
		}
	}
	if (m_backButton != nullptr) {
		delete m_backButton;
	}
}

void GSLevel::Exit()
{
}

void GSLevel::Pause()
{
}

void GSLevel::Resume()
{
}

void GSLevel::initButton()
{
	for (int i = 0; i < m_mapNum; i++) {
		cout << i << " ";
		m_mapButtonVector[i]->Init();
		m_mapButtonVector[i]->setOnClick([]() {
			GSM->ChangeState(StateTypes::STATE_PLAY);

			});
		m_mapButtonVector[i]->setSize({ 188, 255 });
		m_mapButtonVector[i]->setTexture(DATA->getTexture("Button/ghost"));
		m_mapButtonVector[i]->setPosition( 230 + i % 4 * 400, 250 + i / 4 * 220);
		m_mapButtonVector[i]->setOrigin(m_mapButtonVector[i]->getSize());
		m_mapButtonVector[i]->setScale({ (float)1 / 1.5, (float)1 / 1.5 });
	}

	// Back Button
	m_backButton->Init();
	m_backButton->setOnClick([]() {GSM->PopState(); });
	m_backButton->setSize({ 203, 225 });
	m_backButton->setTexture(DATA->getTexture("Button/return"));
	m_backButton->setPosition(0, 0);
	m_backButton->setScale({ (float)1 / 3, (float)1 / 3 });
}

void GSLevel::initText()
{

	for (int i = 0; i < m_mapNum; i++) {
		cout << i << " ";
		m_title = new sf::Text;
		m_title->setFont(*DATA->getFont("Titan_One/TitanOne-Regular"));
		m_title->setCharacterSize(45);
		m_title->setString(to_string(i + 1));
		/*m_title->setOutlineColor({ 197,75,111 });
		m_title->setFillColor({ 225,154,172 });*/
		m_title->setOutlineColor({ 222, 226, 230 });
		m_title->setFillColor({ 108, 117, 125 });
		m_title->setOutlineThickness(5);
		if (i <= 8) {
			m_title->setPosition(m_mapButtonVector[i]->getPosition().x - m_mapButtonVector[i]->getSize().x/2 + 12, m_mapButtonVector[i]->getPosition().y - m_mapButtonVector[i]->getSize().y + 35);
		}
		else {
			m_title->setPosition(m_mapButtonVector[i]->getPosition().x - m_mapButtonVector[i]->getSize().x / 2 , m_mapButtonVector[i]->getPosition().y - m_mapButtonVector[i]->getSize().y + 35);
		}
		m_vectorTitle.push_back(m_title);
	}
}

StateTypes GSLevel::getTypeState()
{
	return STATE_LEVEL;
}

void GSLevel::Init()
{
	printf("GSLevel\n");

	DATA->playMusic("song");

	m_background->setTexture(*DATA->getTexture("bg13"));
	/*m_background->setPosition({300, 50});
	m_background->setScale(1.01, 1.01);*/
	
	initButton();
	initText();


}

void GSLevel::Update(float deltaTime)
{
	m_currentTime += deltaTime;

	DATA->updateMusic();

	if (DATA->getIsNextLevel() == true ) {
		DATA->setLevel(DATA->getLevel() + 1);
		m_listLevel.push_back(DATA->getLevel() + 1);
		DATA->setIsNextLevel(false);
		GSM->ChangeState(STATE_PLAY);
	}
	if (m_currentTime > m_clickTime + 0.1) {
		for (int i = 0; i < m_mapNum; i++) {
			m_mapButtonVector[i]->Update(deltaTime);
			if (m_mapButtonVector[i]->isHandle() == true) {
				DATA->setLevel(i + 1);
				m_clickTime = m_currentTime;
			}
		}
	}

	if (m_currentTime > m_clickTime + 0.15) {
		m_backButton->Update(deltaTime);
		m_clickTime = m_currentTime;
	}


	for (int i = 0; i < m_mapNum; i++) {
		if (DATA->getLevelCompleted(i + 1) == 1) {
			if (i % 4 == 0 || i % 4 == 1) {
				m_vectorTitle[i]->setOutlineColor({ 253, 183, 185 });
				m_vectorTitle[i]->setFillColor({ 248, 228, 219 });
				m_mapButtonVector[i]->setTexture(DATA->getTexture("Button/die1"));
			}
			else {
				m_vectorTitle[i]->setOutlineColor({ 97, 192, 194 });
				m_vectorTitle[i]->setFillColor({ 186, 223, 215 });
				m_mapButtonVector[i]->setTexture(DATA->getTexture("Button/die2"));
			}
		}
	}

	cout << "Level : " << DATA->getLevel() << "\n";
}

void GSLevel::Render(sf::RenderWindow* window)
{
	window->draw(*m_sprite);
	window->draw(*m_background);

	for (int i = 0; i < m_mapNum; i++) {
		m_mapButtonVector[i]->Render(window);
	} 

	for (auto title : m_vectorTitle) {
		window->draw(*title);
	}

	m_backButton->Render(window);

}



