#include "Player.h"
#include "PSIdle.h"
#include "PSAttack.h"
#include "PSDeath.h"

Player::Player()
{
	m_nextState = IPState::SNULL;
	m_idleState = new PSIdle(this);
	m_attackState = new PSAttack(this);
	m_deathState = new PSDeath(this);
	m_currentState = m_idleState;
}

Player::~Player()
{
	if (m_idleState != nullptr) {
		delete m_idleState;
	}
	if (m_attackState != nullptr) {
		delete m_attackState;
	}
	if (m_deathState != nullptr) {
		delete m_deathState;
	}
	m_currentState = nullptr;
}

void Player::changeNextState(IPState::STATE nextState)
{
	m_nextState = nextState;
}

void Player::setAttackPos(sf::Vector2f pos)
{
	m_attackState->setPosition(pos);
}

void Player::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	m_idleState->Init(startPos, name, frameSheetSize, frameNum);
	m_attackState->Init(startPos, name, {4, 1}, 4);
}

void Player::Update(float deltaTime)
{
	performStateChange();
	m_currentState->Update(deltaTime);
	
}

void Player::Render(sf::RenderWindow* window)
{
	m_currentState->Render(window);
}

void Player::performStateChange()
{
	if (m_nextState != IPState::SNULL) {
		switch (m_nextState)
		{
		case IPState::IDLE:
			m_currentState = m_idleState;
			break;
		case IPState::ATTACK:
			m_currentState = m_attackState;
			break;
		case IPState::DEATH:
			m_currentState = m_deathState;
			break;
		}
		m_nextState = IPState::SNULL;
	}
}
