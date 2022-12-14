#pragma once
#include "IEState.h"
#include "IEnemy.h"

class ESDeath : public IEState {
public:
	ESDeath(IEnemy* player);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void setScale(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);
private:
	IEnemy* m_player;
	Animation* m_animation;
	float m_currentTime;
};