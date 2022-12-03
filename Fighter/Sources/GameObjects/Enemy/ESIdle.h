#pragma once
#include "IEState.h"
#include "IEnemy.h"

class ESIdle : public IEState {
public:
	ESIdle(IEnemy* player);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	void setScale(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

private:
	IEnemy* m_player;
	Animation* m_animation;
};