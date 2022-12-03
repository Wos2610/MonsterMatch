#pragma once
#include "GameStateBase.h"


using namespace std;

class GSLevel : public GameStateBase {
public:
	GSLevel();
	virtual ~GSLevel();

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
	GameButton* m_backButton;

	list<int> m_listLevel;

	sf::Sprite* m_sprite;
	sf::Sprite* m_background;

	sf::Text* m_title;
	vector<sf::Text*> m_vectorTitle;
	float m_currentTime;
	float m_clickTime;

	int m_mapNum;

	// Luu cac ma tran tu file input
	map<string, vector<vector<int>>> m_mapStorage;
	// Luu cac button cua cac level
	vector<GameButton*> m_mapButtonVector;
};