#pragma once
#include "GameStateBase.h"

class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

private:
	list<GameButton*> m_ListButton;
	sf::Sprite* m_sprite;
	float m_currentTime;
};