#pragma once
#include<SFML/Graphics.hpp>
#include "GameConfig.h"
#include"GameStateManager/GameStateMachine.h"

class Application : public CSingleton<Application>{
public:
	void Run();
	~Application();
	sf::RenderWindow* getWindow();
private:
	void Init();
	void Update(float deltaTime);
	void Render();
	
	sf::RenderWindow* m_window;
	sf::Sprite m_sprite;
	
};