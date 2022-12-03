#include "Enemy.h"
#include "ESIdle.h"
#include "ESDeath.h"

Enemy::Enemy()
{
	m_nextState = IEState::SNULL;
	m_idleState = new ESIdle(this);
	m_deathState = new ESDeath(this);
	m_currentState = m_idleState;
}

Enemy::~Enemy()
{
	if (m_idleState != nullptr) {
		delete m_idleState;
	}
	if (m_deathState != nullptr) {
		delete m_deathState;
	}
	m_currentState = nullptr;
}

void Enemy::changeNextState(IEState::STATE nextState)
{
	m_nextState = nextState;
}

void Enemy::setScale(sf::Vector2f size)
{
	m_currentState->setScale(size);
}

void Enemy::setPosition(sf::Vector2f pos)
{
	m_currentState->setPosition(pos);
}

void Enemy::Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum)
{
	m_idleState->Init(startPos, name, frameSheetSize, frameNum);
	m_deathState->Init(startPos, name, {11, 1}, 11);

}

void Enemy::Update(float deltaTime)
{
	performStateChange();
	m_currentState->Update(deltaTime);
}

void Enemy::Render(sf::RenderWindow* window)
{
	m_currentState->Render(window);
}

void Enemy::performStateChange()
{
	if (m_nextState != IEState::SNULL) {
		switch (m_nextState)
		{
		case IEState::IDLE:
			m_currentState = m_idleState;
			break;
		case IEState::DEATH:
			m_currentState = m_deathState;
			break;
		}
		m_nextState = IEState::SNULL;
	}
}
