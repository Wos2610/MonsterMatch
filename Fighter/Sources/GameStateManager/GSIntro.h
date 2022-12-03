#pragma once
#include "GameStateBase.h"

class GSIntro : public GameStateBase {
public:
	GSIntro();
	virtual ~GSIntro();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	

	StateTypes getTypeState();
private:
	sf::Sprite m_sprite;
	float m_currentTime;
	sf::Uint8 alpha;
};