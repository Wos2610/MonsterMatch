#include "GSPlay.h"

GSPlay::GSPlay()
{
	m_match = new Match();
	m_player = new Player();

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

void GSPlay::Init()
{
	printf("GS Play\n");
	m_match->Init(5, 5, 2);
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

}

void GSPlay::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	m_match->Update(deltaTime);
	m_player->Update(deltaTime);
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
		}
		if (m_match->getRevokedBlock() >= 0) {
			m_monsters[m_match->getRevokedBlock()]->changeNextState(IEState::IDLE);
			m_match->setRevokedBlock(-1);
			m_clickTime = m_currentTime;
		}

	}
	
}

void GSPlay::Render(sf::RenderWindow* window)
{
	window->draw(m_sprite);
	m_match->Render(window);
	m_player->Render(window);
	for (int i = 0; i < m_match->getMonsterNum(); i++) {
		m_monsters[i]->Render(window);
	}
}
