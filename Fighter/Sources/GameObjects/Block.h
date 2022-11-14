#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

enum BlockTypes {
	NONE = 0,
	YELLOW,
	ORANGE,
	GREEN,
	BLUE,
	PINK,
	PURPLE
};


class Block : public sf::RectangleShape {
private:
	sf::FloatRect m_block;
	sf::Vector2f m_root;
	sf::Vector2f m_size;
	float m_x, m_y; 
	int m_r, m_c;

	// (type, color) 
	// type : 0 - none, 1 - drawn, 2 - needConnected
	pair<int,int> m_type;

	bool m_isConnected;

public:
	Block();
	~Block();

	pair<int,int> getType();
	void setType(int type);

	void setX(float x);
	float getX();

	void setY(float y);
	float getY();

	void setR(int r);
	int getR();

	void setC(int c);
	int getC();

	void setIsConnected(bool isConnected);
	bool getIsConnected();

	void Init(int type, int color, int row, int col, sf::Vector2f root, sf::Vector2f size);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	/*void CalBlockSize();*/

};