#pragma once
#include "GameStateBase.h"
#include "../GameObjects/Enemy/Enemy.h"
#include<iostream>

using namespace std;

class GSEnd : public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

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
	sf::Sprite* m_banner;

	GameButton* m_nextLevelButton;
	GameButton* m_menuButton;
	GameButton* m_restartButton;

	sf::Text* m_title;
	vector<sf::Text*> m_vectorTitle;

	float m_currentTime;
	float m_clickTime;

	Enemy* m_monster;
	int temp;
};