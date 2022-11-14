#pragma once
#include "GameStateBase.h"
#include"../GameManager/ResourceManager.h"
class GSEnd: public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

private:
	sf::Sprite m_Logo;
	float m_currentTime;
	sf::Text* m_complete;

	void initText();
};