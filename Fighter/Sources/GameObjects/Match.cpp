#include "Match.h"
#include"../GameManager/ResourceManager.h"
#include"../Application.h"
#include<iostream>
using namespace std;

Match::Match()
{
	m_board = new sf::RectangleShape();
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			m_grid[i][j] = new Block();
		}
	}
	m_clickTime = 0.f;
	m_currentBlockType = 0;
	m_isMatching = 0;
	m_blockSum = 0;

	m_isFinishTurn = false;
	m_isNextTurn = false;
	m_isClick = false;
	m_isCanContinueDraw = true;
	m_isRevoke = false;
	m_isConnectedBlock = -1;
	m_isRevokedtedBlock = -1;

}

Match::~Match()
{
	if (m_board != nullptr) {
		delete m_board;
	}
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			if (m_grid[i][j] != nullptr) {
				delete m_grid[i][j];
			}
		}
	}
}




sf::Vector2f Match::calGridSize(int row, int col)
{
	sf::Texture* texture = DATA->getTexture("chessboard_4");
	sf::Vector2f textureSize = (sf::Vector2f)texture->getSize();
	textureSize.x /= (float)row;
	textureSize.y /= (float)col;
	return textureSize;

}

void Match::initBoard()
{
	sf::Texture* texture = DATA->getTexture("board_1");
	sf::Vector2f textureSize = (sf::Vector2f)texture->getSize();
	m_matchSize = textureSize;

	m_board->setTexture(texture);
	m_board->setSize(textureSize);

	m_board->setPosition((float)1 / 4.2 * SCREENWIDTH, (float)1 / 4.4 * SCREENHEIGHT);

	// Tinh diem goc trai tren cung cua board
	m_rootBoard = m_board->getPosition();
	m_rootBoard.x += 212;
	m_rootBoard.y += 108;

	// Tinh size cua 1 grid trong board
	m_gridSize = calGridSize(m_row, m_col);

	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			m_grid[i][j]->setX((float)m_gridSize.x * j);
			m_grid[i][j]->setY((float)m_gridSize.y * i);
			m_mark[{i, j}] = 0;
		}
	}

	// Init cap o can noi
	// (color, row1, col1, row2, col2)
	initBlock(0, 2, 0, 2, 4);
	initBlock(1, 1, 2, 3, 2);

}


void Match::initBlock(int color, int row1, int col1, int row2, int col2)
{

	//Init(type, color, row, col, root, size)
	m_grid[row1][col1]->Init(2, color, row1, col1, m_rootBoard, m_gridSize);
	m_mark[{row1, col1}] = color + 2;

	m_grid[row2][col2]->Init(2, color, row2, col2, m_rootBoard, m_gridSize);
	m_mark[{row2, col2}] = -(color + 2);

	m_blockSum++;

}


void Match::revokeDrawing(int i, int j)
{
	cout << "Thu hoi\n";
	cout << m_isMatching << " ";
	// Thu hoi o can noi ma minh click vao
	for (int p = 0; p < m_row; p++) {
		for (int q = 0; q < m_col; q++) {
			if (m_grid[p][q]->getType().first == 1 && (m_mark[{p, q}] == m_isMatching || m_mark[{p, q}] == -m_isMatching)) {
				cout << m_isMatching << " ";
				m_mark[{p, q}] = 0;
			}
		}
	}
	m_grid[i][j]->setIsConnected(false);
	// Thu hoi o can noi con lai
	for (int p = 0; p < m_row; p++) {
		for (int q = 0; q < m_col; q++) {
			if (m_mark[{p, q}] == -m_mark[{i, j}]) {
				m_grid[p][q]->setIsConnected(false);
				return;
			}
		}
	}
}

void Match::startDrawing(int i, int j)
{
	m_startTurnMark = m_mark;
	m_isMatching = m_mark[{i, j}];
	m_currentBlockType = m_grid[i][j]->getType().second;
	m_startTurnBlock = { i, j };
	cout << "Begin next turn\n";
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << m_grid[i][j]->getIsConnected() << " ";
		}
		cout << "\n";
	}*/
}

void Match::drawing(int i, int j)
{
	m_grid[i][j]->Init(1, m_currentBlockType, i, j, m_rootBoard, m_gridSize);
	m_grid[i][j]->setType(1);
}

void Match::endDrawing(int i, int j)
{
	m_grid[i][j]->setIsConnected(true);
	m_grid[m_startTurnBlock.x][m_startTurnBlock.y]->setIsConnected(true);
	m_connectedBlockList.push_back(m_currentBlockType);
	m_blockSum--;
}



void Match::nextTurn(float deltaTime)
{

	if (m_isClick == true) {
		this->runTurn(deltaTime);
	}
	else {
		if (m_isFinishTurn == false) {
			sf::Vector2f m_currentPos = { 0, 0 };
			// Neu click chuot trai lan thu nhat tai o can noi
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (m_currentTime > (m_clickTime + ClickTime)) {
					m_currentPos = (sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow());
					m_currentPos.x -= m_rootBoard.x;
					m_currentPos.y -= m_rootBoard.y;
					for (int i = 0; i < m_row; i++) {
						for (int j = 0; j < m_col; j++) {
							if (m_grid[i][j]->getX() < m_currentPos.x && m_currentPos.x < m_grid[i][j]->getX() + m_gridSize.x
								&& m_grid[i][j]->getY() < m_currentPos.y && m_currentPos.y < m_grid[i][j]->getY() + m_gridSize.y) {
								/*if (abs(m_mark[{i, j}]) > 1 && m_mark[{i, j}] != -m_isMatching) {*/

								// need to connect and not connected
								if (m_grid[i][j]->getType().first == 2 && m_grid[i][j]->getIsConnected() == false) {
									if (m_isRevoke == false && m_mark[{i, j}] != -m_isMatching) {
										startDrawing(i, j);
										m_isClick = true;
									}
									if (m_isRevoke == true ) {
										startDrawing(i, j);
										m_isClick = true;
										m_isRevoke = false;
									}
									m_isMatching = m_mark[{i, j}];
								}

								// need to connect and connected
								if (m_grid[i][j]->getType().first == 2 && m_grid[i][j]->getIsConnected() == true) {
									m_isMatching = m_mark[{i, j}];
									revokeDrawing(i, j);
									m_blockSum++;
									m_isClick = false;
									m_isRevoke = true;
									m_isRevokedtedBlock = abs(m_isMatching) - 2;
								}

							}
						}
					}
					m_clickTime = m_currentTime;
				}
				m_clickNum++;
			}
			cout << "Click : " << m_clickNum << "\n";
		}

	}
	cout << m_clickTime << " " << m_currentTime << "\n";
	/*cout << "Click : " << m_clickNum << "\n";*/
}


void Match::runTurn(float deltaTime)
{
	cout << "Run Turn" << "\n";

	sf::Vector2f m_currentPos = (sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow());
	m_currentPos.x -= m_rootBoard.x;
	m_currentPos.y -= m_rootBoard.y;
	cout << "Mouse: " << m_currentPos.x << " " << m_currentPos.y << "\n";

	// Ve duong noi giua 2 o
	if (m_isCanContinueDraw == true) {
		for (int i = 0; i < m_row; i++) {
			for (int j = 0; j < m_col; j++) {
				if (m_grid[i][j]->getX() < m_currentPos.x && m_currentPos.x < m_grid[i][j]->getX() + m_gridSize.x
					&& m_grid[i][j]->getY() < m_currentPos.y && m_currentPos.y < m_grid[i][j]->getY() + m_gridSize.y) {
					if (m_mark[{i, j}] == 0) {
						drawing(i, j);
						m_mark[{i, j}] = m_isMatching;
					}
					// Neu co duong da noi giua 2 o khac thi khong the ve qua duoc
					else if (m_mark[{i, j}] != m_isMatching && m_mark[{i, j}] != -m_isMatching) {
						cout << "Can't draw\n";
						m_isCanContinueDraw = false;
					}
				}
			}
		}
	}

	// Neu click lan thu 2 thi dung ve
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		m_clickNum++;
		if (m_currentTime > (m_clickTime + ClickTime)) {
			for (int i = 0; i < m_row; i++) {
				for (int j = 0; j < m_col; j++) {
					if (m_grid[i][j]->getX() < m_currentPos.x && m_currentPos.x < m_grid[i][j]->getX() + m_gridSize.x
						&& m_grid[i][j]->getY() < m_currentPos.y && m_currentPos.y < m_grid[i][j]->getY() + m_gridSize.y) {
						if (m_isClick == true) {
							if (m_grid[i][j]->getType().first == 2) {
								if (m_isCanContinueDraw == false) {
									revokeDrawing(i, j);
									m_isCanContinueDraw = true;
									m_isRevoke = true;
								}
								else {
									if (m_mark[{i, j}] == -m_isMatching) {
										m_isConnectedBlock = m_currentBlockType;
										endDrawing(i, j);
										cout << "End turn\n\n";
									}
								}
							}
							else {
								m_mark = m_startTurnMark;
							}
							m_isClick = false;
						}
						else {
							startDrawing(i, j);
							m_isClick = true;
						}
					}
				}
			}
			m_clickTime = m_currentTime;
		}
	}
	cout << m_clickTime << " " << m_currentTime << "\n";

	cout << "Click : " << m_clickNum << "\n";
}




bool Match::isFinishTurn()
{
	if (m_blockSum == 0) {
		m_isFinishTurn = true;
	}
	return m_isFinishTurn;
}

bool Match::isContinueNextTurn()
{
	return m_isNextTurn;
}

sf::Vector2f Match::getRootMatch()
{
	return m_board->getPosition();
}

sf::Vector2f Match::getMatchSize()
{
	return m_matchSize;
}

int Match::getMonsterNum()
{
	return m_monsterNum;
}

int Match::getConnectedBlock()
{
	return m_isConnectedBlock;
}

void Match::setConnectedBlock(int color)
{
	m_isConnectedBlock = color;
}

int Match::getRevokedBlock()
{
	return m_isRevokedtedBlock;
}

void Match::setRevokedBlock(int color)
{
	m_isRevokedtedBlock = color;
}


void Match::Init(int row, int col, int monsterNum)
{
	m_row = row;
	m_col = col;
	m_monsterNum = monsterNum;
	this->initBoard();
	
}


void Match::Update(float deltaTime)
{
	if (isFinishTurn() == false) {
		m_currentTime += deltaTime;
		this->nextTurn(deltaTime);
	}

}

void Match::Render(sf::RenderWindow* window)
{
	window->draw(*m_board);
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			if (m_mark[{i, j}] != 0) {
				m_grid[i][j]->Render(window);
			}
		}
	}
}

