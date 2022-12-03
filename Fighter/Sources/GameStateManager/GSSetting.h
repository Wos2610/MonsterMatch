#pragma once
#include "GameStateBase.h"
#include "../GameObjects/Enemy/Enemy.h"
#include<iostream>

using namespace std;

class GSSetting : public GameStateBase {
public:
	GSSetting();
	virtual ~GSSetting();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	void initButton();
	void initText();
	void initMonster();

	StateTypes getTypeState();

private:
	sf::Sprite* m_background;
	sf::Sprite* m_frame;

	GameButton* m_soundButton;
	GameButton* m_musicButton;
	GameButton* m_backButton;

	sf::Text* m_title;

	float m_currentTime;
	float m_clickTime;

	Enemy* m_monster;
	int temp;
};