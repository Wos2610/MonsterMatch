#pragma once
#include "GameStateBase.h"
#include "../GameObjects/Enemy/Enemy.h"
#include<iostream>

using namespace std;

class GSPause : public GameStateBase {
public:
	GSPause();
	virtual ~GSPause();

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
	list<GameButton*> m_ListButton;
	sf::Sprite* m_background;
	sf::Sprite* m_frame;

	GameButton* m_resumeButton;
	GameButton* m_restartButton;
	GameButton* m_menuButton;
	GameButton* m_soundButton;

	sf::Text* m_title;

	float m_currentTime;
	float m_changeTime;
	float m_clickTime;

	Enemy* m_monster;
	int temp;
};