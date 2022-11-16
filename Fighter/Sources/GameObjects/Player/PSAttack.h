#pragma once
#include "IPState.h"
#include "IPlayer.h"

class PSAttack : public IPState {
public:
	PSAttack(IPlayer* player);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
private:
	IPlayer* m_player;
	Animation* m_animation;

	float m_currentTime;
};