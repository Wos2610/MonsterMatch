#pragma once
#include "IEState.h"
#include "IEnemy.h"

class ESIdle : public IEState {
public:
	ESIdle(IEnemy* player);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

private:
	IEnemy* m_player;
	Animation* m_animation;
};