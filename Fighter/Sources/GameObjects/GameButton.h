#pragma once
#include <SFML/Graphics.hpp>
#include"../GameManager/WindowConnector.h"
#include"../GameConfig.h"

class GameButton : public sf::RectangleShape{
public:
	GameButton();
	~GameButton();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	// Khi an vao nut xay ra hien tuong gi
	void HandleTouchEvent();
	// Co dang an hay khong ?
	bool isHandle();

	void setOnClick(void(*Func)());

private:
	//Chuc nang cua cac button
	void (*m_buttonClickFunction)();
	bool m_isHandling;
	float m_currentTime;

};