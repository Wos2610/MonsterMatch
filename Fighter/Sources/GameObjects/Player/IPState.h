#pragma once
#include "../../GameManager/ResourceManager.h"
#include<iostream>

using namespace std;

class IPState {
public:
	enum STATE {
		IDLE,
		ATTACK,
		DEATH,
		SNULL
	};

	virtual void Init(sf::Vector2f startPos, string name, sf::Vector2i frameSheetSize, int frameNum) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void setPosition(sf::Vector2f pos) = 0;
};