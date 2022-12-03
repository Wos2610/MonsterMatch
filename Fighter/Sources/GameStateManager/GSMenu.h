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

	void initButton();
	void initText();

	StateTypes getTypeState();

private:
	list<GameButton*> m_ListButton;
	sf::Sprite* m_sprite;
	sf::Sprite* m_frame;
	GameButton* button;
	
	sf::Text* m_title;
	vector<sf::Text*> m_vectorTitle;

	float m_currentTime;
	float m_clickTime;
};