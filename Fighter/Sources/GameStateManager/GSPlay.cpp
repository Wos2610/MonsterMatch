#include "GSPlay.h"

GSPlay::GSPlay()
{
	m_match = new Match();
	m_player = new Player();
	m_background = new sf::Sprite;
	m_pauseButton = new GameButton();
	m_backButton = new GameButton();
	m_row = 0;
	m_col = 0;
	m_monsterNum = 0;
	m_currentTime = 0;
	m_clickTime = 0;
	m_attackTime = 0.f;
}

GSPlay::~GSPlay()
{
	if (m_match != nullptr) {
		delete m_match;
	}
	if (m_player != nullptr) {
		delete m_player;
	}
	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		if (m_monsters[i] != nullptr) {
			delete m_monsters[i];
		}
	}
	if (m_background != nullptr) {
		delete m_background;
	}
	if (m_pauseButton != nullptr) {
		delete m_pauseButton;
	}
	if (m_backButton != nullptr) {
		delete m_backButton;
	}
}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::Restart()
{
	
}

void GSPlay::initButton()
{
	// Pause Button
	m_pauseButton->Init();
	m_pauseButton->setOnClick([]() {GSM->ChangeState(StateTypes::STATE_PAUSE);});
	m_pauseButton->setSize({ 203, 225 });
	m_pauseButton->setTexture(DATA->getTexture("Button/pause"));
	m_pauseButton->setPosition(SCREENWIDTH, (float)m_pauseButton->getSize().y/3);
	m_pauseButton->setOrigin(m_pauseButton->getSize());
	m_pauseButton->setScale({ (float)1 / 3, (float)1 / 3 });

	//Back Button
	m_backButton->Init();
	m_backButton->setOnClick([]() {GSM->PopState(); });
	m_backButton->setSize({ 203, 225 });
	m_backButton->setTexture(DATA->getTexture("Button/return"));
	m_backButton->setPosition(0, 0);
	m_backButton->setScale({ (float)1 / 3, (float)1 / 3 });

}

void GSPlay::Init()
{
	printf("GS Play\n");

	m_background->setTexture(*DATA->getTexture("bg18"));

	initButton();

	cout << "Play : " << DATA->getLevel() << "\n"; 

	ifstream input;
	input.open("../Data/Map/Level" + to_string(DATA->getLevel()) + ".txt");

	
	input >> m_row >> m_col >> m_monsterNum;
	cout << m_row << " " << m_col << " " << m_monsterNum << "\n";
	vector<vector<int>> m_map(m_row, vector<int>(m_col, 0));

	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			input >> m_map[i][j];
		}
	}
	
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			cout << m_map[i][j] << " ";
		}
		cout << '\n';
	}

	input.close();

	m_match->Init(m_row, m_col, m_monsterNum, m_map);
	m_player->Init({ m_match->getRootMatch().x + m_match->getMatchSize().x, m_match->getRootMatch().y - 100 }, "meow", { 1, 6 }, 6);

	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		Enemy* temp = new Enemy();
		m_monsters.push_back(temp);
	}

	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		string temp = "monster_";
		temp += (char)(i + '1');
		m_monsters[i]->Init({ m_match->getRootMatch().x - 75.f + i * 100, m_match->getRootMatch().y - 60.f }, temp, { 7, 1 }, 2);
	}

	/*m_background->setTexture(*DATA->getTexture("play_background"));*/

}

void GSPlay::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	m_match->Update(deltaTime);
	m_player->Update(deltaTime);

	DATA->pauseMusic("song");

	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		m_monsters[i]->Update(deltaTime);
	}
	if (m_currentTime >= (m_clickTime + ClickTime)) {
		if (m_match->getConnectedBlock() >= 0) {
			m_monsters[m_match->getConnectedBlock()]->changeNextState(IEState::DEATH);
			m_player->setAttackPos({ m_match->getRootMatch().x + 190 + m_match->getConnectedBlock() * 100,  m_match->getRootMatch().y - 140});
			m_player->changeNextState(IPState::ATTACK);
			m_match->setConnectedBlock(-1);
			m_clickTime = m_currentTime;
			m_attackTime = m_currentTime;
		}
		if (m_match->getRevokedBlock() >= 0) {
			m_monsters[m_match->getRevokedBlock()]->changeNextState(IEState::IDLE);
			m_match->setRevokedBlock(-1);
			m_clickTime = m_currentTime;
		}
	}

	if (m_currentTime >= m_attackTime + 0.5) {
		m_player->changeNextState(IPState::IDLE);
	}

	if (m_currentTime > m_clickTime + 0.1) {
		m_backButton->Update(deltaTime);
	}
	if (m_currentTime > m_clickTime + 0.07) {
		m_pauseButton->Update(deltaTime);
	}
	
}

void GSPlay::Render(sf::RenderWindow* window)
{

	window->draw(*m_background);
	m_pauseButton->Render(window);
	m_backButton->Render(window);


	m_match->Render(window);
	m_player->Render(window);
	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		m_monsters[i]->Render(window);
	}
}

StateTypes GSPlay::getTypeState()
{
	return STATE_PLAY;
}

