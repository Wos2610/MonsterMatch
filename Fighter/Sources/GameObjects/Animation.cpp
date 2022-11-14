#include "Animation.h"


Animation::Animation(sf::Texture& texture, sf::Vector2i frameNum, float frameTime)
{
	m_frameNum = frameNum;
	m_frameTime = frameTime;
	this->setTexture(texture);
	m_currentFrame = sf::Vector2i(0, 0);
	m_currentTime = 0.f;
	CalRectSize();
	CalRectPos();
	ApplyRect();
}

void Animation::CalRectSize()
{
	m_rectSize = sf::Vector2i(this->getTexture()->getSize().x / m_frameNum.x, this->getTexture()->getSize().y / m_frameNum.y);
}

void Animation::CalRectPos()
{
	m_rectPos.x = m_currentFrame.x * m_rectSize.x;
	m_rectPos.y = m_currentFrame.y * m_rectSize.y;
}

void Animation::ApplyRect()
{
	m_rect = sf::IntRect(m_rectPos, m_rectSize);
	this->setTextureRect(m_rect);
}

void Animation::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameTime) {
		if (m_frameNum.x == 1) {
			m_currentFrame.y++;
			if (m_currentFrame.y == m_frameNum.y) {
				m_currentFrame.y = 0;
			}
		}
		else {
			m_currentFrame.x++;
			if (m_currentFrame.x == m_frameNum.x) {
				m_currentFrame.x = 0;
			}
		}
		CalRectPos();
		ApplyRect();
		m_currentTime -= m_frameTime;
	}
}
