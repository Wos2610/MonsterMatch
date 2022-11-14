#pragma once
#include "IPlayer.h"
#include "../Match.h"

class Player : public IPlayer {
public:
	Player();
	~Player();

	void changeNextState(IPState::STATE nextState);
	void setAttackPos(sf::Vector2f pos);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	

private:

	IPState::STATE m_nextState;
	IPState* m_currentState;
	IPState* m_idleState;
	IPState* m_attackState;
	IPState* m_deathState;

	void performStateChange();
};