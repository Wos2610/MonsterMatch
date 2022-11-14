#pragma once
#include "IPState.h"
#include "IPlayer.h"

class PSDeath : public IPState {
public:
	PSDeath(IPlayer* player);
	void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void setPosition(sf::Vector2f pos);

private:
	IPlayer* m_player;
	Animation* m_animation;
};