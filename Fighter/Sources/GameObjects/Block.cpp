#include "Block.h"
#include"../GameManager/ResourceManager.h"

Block::Block()
{
	m_type = { 0, 0 };
	m_x = 0.f;
	m_y = 0.f;
	m_r = 0;
	m_c = 0;
	m_isConnected = false;
}

Block::~Block()
{

}

//int Block::getType()
//{
//	switch (m_type) {
//	case BlockTypes::YELLOW:
//		return 0;
//	case BlockTypes::ORANGE:
//		return 1;
//	case BlockTypes::GREEN:
//		return 2;
//	case BlockTypes::BLUE:
//		return 3;
//	case BlockTypes::PINK:
//		return 4;
//	case BlockTypes::PURPLE:
//		return 5;
//	}
//	return 0;
//}

pair<int, int> Block::getType() {
	return m_type;
}

void Block::setType(int type) {
	m_type.first = type;
}

void Block::setX(float x)
{
	m_x = x;
}

float Block::getX()
{
	return m_x;
}

void Block::setY(float y)
{
	m_y = y;
}

float Block::getY()
{
	return m_y;
}



void Block::setR(int r)
{
	m_r = r;
}

int Block::getR()
{
	return m_r;
}

void Block::setC(int c)
{
	m_c = c;
}

int Block::getC()
{
	return m_c;
}

void Block::setIsConnected(bool isConnected)
{
	m_isConnected = isConnected;
}


bool Block::getIsConnected()
{
	return m_isConnected;
}

void Block::Init(int type, int color, int row, int col, sf::Vector2f root, sf::Vector2f size)
{
	//Size cua block = 0.8 * size cua grid
	this->setSize((float)0.8 * size);

	m_type = { type, color };
	string tp = "";
	tp.push_back((char)m_type.second + '1');
	this->setTexture(ResourceManager::GetInstance()->getTexture("block_" + tp));

	m_root = root ;
	m_size = (float)0.8 * size;
	m_r = row;
	m_c = col;
	m_x = size.x * (float)m_c;
	m_y = size.y * (float)m_r;
	m_root = root;
	/*this->setPosition(m_root.x + m_x, m_root.y + m_y);*/
	this->setPosition(m_root.x + m_x + (size.x - m_size.x)/2.f, m_root.y + m_y + (size.y - m_size.y) / 2.f);
}

void Block::Update(float deltaTime)
{

}


void Block::Render(sf::RenderWindow* window)
{
	window->draw(*this);
}

