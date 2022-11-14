#pragma once
#include "IEnemy.h"

class Enemy : public IEnemy {
public:
	Enemy();
	~Enemy();

	void changeNextState(IEState::STATE nextState);

	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);


private:

	IEState::STATE m_nextState;
	IEState* m_currentState;
	IEState* m_idleState;
	IEState* m_deathState;

	void performStateChange();
};