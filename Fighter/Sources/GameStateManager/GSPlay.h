#pragma once
#include "GameStateBase.h"
#include"../GameObjects/Match.h"
#include"../GameObjects//Player/Player.h"
#include"../GameObjects//Enemy/Enemy.h"
#include"../GameConfig.h"


class GSPlay : public GameStateBase {
public:
	GSPlay();
	virtual ~GSPlay();

	void Exit();
	void Pause();
	void Resume();
	void Restart();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	StateTypes getTypeState();

private:
	sf::Sprite m_sprite;
	Match* m_match;
	Player* m_player;
	vector<Enemy*> m_monsters;
	
	float m_currentTime;
	float m_clickTime;
	float m_attackTime;

	int m_row;
	int m_col;
	int m_monsterNum;
	

	sf::Sprite* m_background;
	GameButton* m_pauseButton;
	GameButton* m_backButton;

	void initButton();
};