#pragma once
#pragma once
#include"SFML/Graphics.hpp"

class Animation : public sf::Sprite {
public:
	Animation(sf::Texture& texture, sf::Vector2i frameNum, float frameTime);
	void CalRectSize();
	void CalRectPos();
	void ApplyRect();
	void Update(float deltaTime);
private:
	//So frame theo chieu rong, chieu cao
	sf::Vector2i m_frameNum;
	//Chi so rong va cao theo o cua fram hien tai
	sf::Vector2i m_currentFrame;

	//Thoi gian cua moi frame
	float m_frameTime;
	float m_currentTime;

	//Toa do cua diem tren cung ben trai cua frame
	sf::Vector2i m_rectPos;
	//Size cua 1 frame
	sf::Vector2i m_rectSize;
	// = m_rectPos + m_rectSize
	sf::IntRect m_rect;
};