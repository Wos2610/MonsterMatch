#include "Match.h"
#include"../GameManager/ResourceManager.h"
#include"../Application.h"
#include<iostream>
using namespace std;

#define m_textY 10
Match::Match()
{
	m_board = new sf::RectangleShape();

	m_text = new sf::Text;

	m_clickTime = 0.f;
	m_currentTime = 0.f;
	m_drawTime = 0.f;
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

	mark = 0;

	boardCursor = new sf::Cursor();
	gameCursor = new sf::Cursor();
}

Match::~Match()
{
	if (m_board != nullptr) {
		delete m_board;
	}
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			if (m_grid[i][j] != nullptr) {
				delete m_grid[i][j];
			}
		}
	}
	if (m_text != nullptr) {
		delete m_text;
	}

	if (boardCursor != nullptr) {
		delete boardCursor;
	}

	if (gameCursor != nullptr) {
		delete gameCursor;
	}
}

sf::Vector2f Match::calGridSize(int row, int col)
{
	sf::Texture* texture = DATA->getTexture("chessboard_" + to_string(row) + to_string(col));
	sf::Vector2f textureSize = (sf::Vector2f)texture->getSize();
	textureSize.x /= (float)col;
	textureSize.y /= (float)row;
	cout << "Grid size : " << textureSize.x << " " << textureSize.y;
	return textureSize;

}

void Match::initBoard()
{
	sf::Texture* texture = DATA->getTexture("board_" + to_string(m_row) + to_string(m_col));
	sf::Vector2f textureSize = (sf::Vector2f)texture->getSize();
	m_matchSize = textureSize;

	m_board->setTexture(texture);
	m_board->setSize(textureSize);

	m_board->setPosition((float)(SCREENWIDTH - m_board->getSize().x)/2, (float)(SCREENHEIGHT - m_board->getSize().y));

	// Tinh size cua 1 grid trong board
	m_gridSize = calGridSize(m_row, m_col);

	// Tinh diem goc trai tren cung cua board
	m_rootBoard = m_board->getPosition();
	m_rootBoard.x += (float)(m_board->getSize().x - m_gridSize.x * m_col)/2;
	m_rootBoard.y += (float)(m_board->getSize().y - m_gridSize.y * m_row)/2;

	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_col; j++) {
			cout << i << " " << j << "\n";
			cout << (float)m_gridSize.x * j << " " << (float)m_gridSize.y * i << "\n";
			m_grid[i][j]->setX((float)m_gridSize.x * j);
			m_grid[i][j]->setY((float)m_gridSize.y * i);
			m_mark[{i, j}] = 0;
		}
	}

	// Init cap o can noi
	// (color, row1, col1, row2, col2)
	for (int i = 0; i < m_monsterNum; i++) {
		int row1 = -1, col1 = -1, row2 = -1, col2 = -1;
		for (int j = 0; j < m_row; j++) {
			for (int k = 0; k < m_col; k++) {
				if (m_currentMap[j][k] == i + 2) {
					if (row1 == -1) {
						row1 = j;
						col1 = k;
					}
					else {
						row2 = j;
						col2 = k;
						break;
					}
				}
			}
			if (row2 != -1) {
				break;
			}
		}
		initBlock(i, row1, col1, row2, col2);
	}

	m_text->setFont(*DATA->getFont("Vast_Shadow/VastShadow-Regular"));
	m_text->setCharacterSize(50);
	m_text->setFillColor(sf::Color::Black);
	m_text->setPosition(SCREENWIDTH/2 - 100, m_textY);
	m_text->setString("Ready!");
	
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
	DATA->playSound("start");
	cout << "Thu hoi\n";
	cout << m_isMatching << " ";
	m_text->setString("Revoke");
	m_text->setPosition({SCREENWIDTH/2 - 100, m_textY});
	// Thu hoi o can noi ma minh click vao
	for (int p = 0; p < m_row; p++) {
		for (int q = 0; q < m_col; q++) {
			if (m_grid[p][q]->getType().first == 1 && (m_mark[{p, q}] == m_isMatching || m_mark[{p, q}] == -m_isMatching)) {
				cout << m_isMatching << " ";
				m_mark[{p, q}] = 0;
			}
		}
	}

	if (m_drawPath.size() == 0) {
		m_grid[i][j]->setIsConnected(false);
		m_grid[i][j]->setTexture(DATA->getTexture("2/" + to_string(abs(m_isMatching) - 1) + "/block_" + to_string(abs(m_isMatching) - 1)));
	}

	if (m_drawPath.size() >= 1) {
		while (m_drawPath.size() > 1) {
			m_drawPath.pop_back();
		}
		m_grid[m_drawPath.back().first][m_drawPath.back().second]->setIsConnected(false);
		m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("2/" + to_string(abs(m_isMatching) - 1) + "/block_" + to_string(abs(m_isMatching) - 1)));

		if (m_drawPath.size() == 1) {
			m_drawPath.pop_back();
		}
	}


	// Thu hoi o can noi con lai
	for (int p = 0; p < m_row; p++) {
		for (int q = 0; q < m_col; q++) {
			cout << m_mark[{p, q}] << " ";
		}
		cout << "\n";
	}

	for (int p = 0; p < m_row; p++) {
		for (int q = 0; q < m_col; q++) {
			if (m_mark[{p, q}] == -m_isMatching) {
				m_grid[p][q]->setIsConnected(false);
				m_grid[p][q]->setTexture(DATA->getTexture("2/" + to_string(abs(m_isMatching) - 1) + "/block_" + to_string(abs(m_isMatching) - 1)));
				return;
			}
		}
	}
}

void Match::startDrawing(int i, int j)
{	
	DATA->playSound("start");
	mark = 0;
	m_startTurnMark = m_mark;
	m_isMatching = m_mark[{i, j}];
	m_currentBlockType = m_grid[i][j]->getType().second;
	m_startTurnBlock = { i, j };
	cout << "Begin next turn\n";
	m_text->setString("Begin Turn");
	m_text->setPosition({ SCREENWIDTH/2 - 140 , m_textY });
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

	string temp = "";
	cout << m_drawPath.back().first << " " << m_drawPath.back().second << "..........\n";
	
	if (i == m_drawPath.back().first && j != m_drawPath.back().second) {
		if (abs(mark) == 2) {
			if (j == m_drawPath.back().second - 1) {
				if (mark == 2) {
					temp = "goc3";
				}
				else if (mark == -2) {
					temp = "goc2";
				}
			}
			else if (j == m_drawPath.back().second + 1) {
				if (mark == 2) {
					temp = "goc4";
				}
				else if (mark == -2) {
					temp = "goc1";
				}
			}
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 1) {
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("1/" + to_string(m_currentBlockType + 1) + "/" + temp));
			}
		}
		else if (mark == 0) {
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 2) {
				if (j == m_drawPath.back().second - 1) {
					temp = "left";
				}
				else if (j == m_drawPath.back().second + 1) {
					temp = "right";
				}
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("2/" + to_string(m_currentBlockType + 1) + "/" + temp));
			}
		}
		temp = "ngang";
		if (j > m_drawPath.back().second) {
			mark = 1;
		}
		else if (j < m_drawPath.back().second) {
			mark = -1;
		}

	}
	else if (j == m_drawPath.back().second && i != m_drawPath.back().first) {
		if (abs(mark) == 1) {
			if (i == m_drawPath.back().first - 1) {
				if (mark == 1) {
					temp = "goc3";
				}
				else if (mark == -1) {
					temp = "goc4";
				}
			}
			else if (i == m_drawPath.back().first + 1) {
				if (mark == 1) {
					temp = "goc2";
				}
				else if (mark == -1) {
					temp = "goc1";
				}
			}
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 1) {
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("1/" + to_string(m_currentBlockType + 1) + "/" + temp));
			}
		}
		else if (mark == 0) {
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 2) {
				if (i == m_drawPath.back().first - 1) {
					temp = "top";
				}
				else if (i == m_drawPath.back().first + 1) {
					temp = "bottom";
				}
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("2/" + to_string(m_currentBlockType + 1) + "/" + temp));
			}
		}
		temp = "doc";
		if (i > m_drawPath.back().first) {
			mark = 2;

		}
		else if (i < m_drawPath.back().first) {
			mark = -2;
		}
	}
	m_grid[i][j]->setTexture(DATA->getTexture("1/" + to_string(m_currentBlockType + 1) + "/" + temp));

	cout << m_drawPath.size() << mark << "hhhhhhhhhhhhhhhhhhhh\n";

	m_text->setString("Drawing");
	m_text->setPosition({ SCREENWIDTH/2 - 120 , m_textY });
}

void Match::endDrawing(int i, int j)
{
	DATA->playSound("end");
	m_grid[i][j]->setIsConnected(true);
	m_grid[m_startTurnBlock.x][m_startTurnBlock.y]->setIsConnected(true);
	m_connectedBlockList.push_back(m_currentBlockType);
	m_blockSum--;
	m_text->setString("End Turn");
	m_text->setPosition({ SCREENWIDTH/2 - 120, m_textY });

	string temp = "";
	cout << m_drawPath.back().first << " " << m_drawPath.back().second << "..........\n";
	
	if (i == m_drawPath.back().first && j != m_drawPath.back().second) {
		if (abs(mark) == 2) {
			if (j == m_drawPath.back().second - 1) {
				if (mark == 2) {
					temp = "goc3";
				}
				else if (mark == -2) {
					temp = "goc2";
				}
			}
			else if (j == m_drawPath.back().second + 1) {
				if (mark == 2) {
					temp = "goc4";
				}
				else if (mark == -2) {
					temp = "goc1";
				}
			}
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 1) {
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("1/" + to_string(abs(m_isMatching) - 1) + "/" + temp));
			}
		}

	}
	else if (j == m_drawPath.back().second && i != m_drawPath.back().first) {
		if (abs(mark) == 1) {
			if (i == m_drawPath.back().first - 1) {
				if (mark == 1) {
					temp = "goc3";
				}
				else if (mark == -1) {
					temp = "goc4";
				}
			}
			else if (i == m_drawPath.back().first + 1) {
				if (mark == 1) {
					temp = "goc2";
				}
				else if (mark == -1) {
					temp = "goc1";
				}
			}
			if (m_grid[m_drawPath.back().first][m_drawPath.back().second]->getType().first == 1) {
				m_grid[m_drawPath.back().first][m_drawPath.back().second]->setTexture(DATA->getTexture("1/" + to_string(abs(m_isMatching) - 1) + "/" + temp));
			}
		}
	}

	if (i == m_drawPath.back().first && j != m_drawPath.back().second) {
		if (j == m_drawPath.back().second - 1) {
			temp = "right";
		}
		else if (j == m_drawPath.back().second + 1) {
			temp = "left";
		}
	}
	else if (j == m_drawPath.back().second && i != m_drawPath.back().first) {
		if (i == m_drawPath.back().first - 1) {
			temp = "bottom";
		}
		else if (i == m_drawPath.back().first + 1) {
			temp = "top";
		}
	}
	m_grid[i][j]->setTexture(DATA->getTexture("2/" + to_string(abs(m_isMatching) - 1) + "/" + temp));

	while (m_drawPath.size() != 0) {
		m_drawPath.pop_back();
	}
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
										/*if (m_isCanContinueDraw == false) {
											m_isCanContinueDraw = true;
										}*/
										startDrawing(i, j);
										m_isClick = true;
										m_isRevoke = false;
									}
									m_drawPath.push_back({ i, j });
									m_startTurnBlock = { i, j };
									m_isMatching = m_mark[{i, j}];
								}

								// need to connect and connected
								if (m_grid[i][j]->getType().first == 2 && m_grid[i][j]->getIsConnected() == true) {
									m_isMatching = m_mark[{i, j}];
									revokeDrawing(i, j);
									cout << "here.............................";
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

	m_currentTime += deltaTime;

	// Ve duong noi giua 2 o
	if (m_isCanContinueDraw == true ) {
		for (int i = 0; i < m_row; i++) {
			for (int j = 0; j < m_col; j++) {
				if (m_grid[i][j]->getX() < m_currentPos.x && m_currentPos.x < m_grid[i][j]->getX() + m_gridSize.x
					&& m_grid[i][j]->getY() < m_currentPos.y && m_currentPos.y < m_grid[i][j]->getY() + m_gridSize.y) {
					if (m_mark[{i, j}] == 0) {
						if ((i != m_drawPath.back().first + 1 && i != m_drawPath.back().first - 1 && i != m_drawPath.back().first) || (j != m_drawPath.back().second + 1 && j != m_drawPath.back().second - 1 && j != m_drawPath.back().second )) {
							cout << "Can't draw\n";
							m_isCanContinueDraw = false;
							m_text->setString("Can't draw");
						}
						else {
							m_mark[{i, j}] = m_isMatching;
							drawing(i, j);
							m_drawPath.push_back({ i, j });
							m_drawTime = m_currentTime;
						}
					}
					// Neu co duong da noi giua 2 o khac thi khong the ve qua duoc
					else if (m_mark[{i, j}] != m_isMatching && m_mark[{i, j}] != -m_isMatching) {
						cout << "Can't draw\n";
						m_isCanContinueDraw = false;
						m_text->setString("Can't draw");
					}
					else {
						if (m_currentTime > (m_drawTime + 1) && m_currentTime > m_clickTime + 1) {
							for (int k = 0; k < m_drawPath.size(); k++) {
								if (m_drawPath[k].first == i && m_drawPath[k].second == j) {
									cout << "Can't draw\n";
									m_isCanContinueDraw = false;
									m_text->setString("Can't draw");
								}
							}
						}
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
								if (m_isCanContinueDraw == false) {
									m_isCanContinueDraw = true;
								}
								revokeDrawing(i, j);
								m_isRevoke = true;
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
		if (m_isFinishTurn == false) {
			m_endTime = m_currentTime;
		}
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


void Match::Init(int row, int col, int monsterNum, vector<vector<int>> m_map)
{
	m_row = row;
	m_col = col;
	m_monsterNum = monsterNum;
	m_currentMap = m_map;
	for (int i = 0; i <= m_row; i++) {
		for (int j = 0; j <= m_col; j++) {
			m_grid[i][j] = new Block();
		}
	}
	this->initBoard();

	// Set boardCursor
	DATA->setCursor("cursor/target");
	sf::Vector2u cursorSize = DATA->getCursor()->getSize();
	boardCursor->loadFromPixels(DATA->getCursor()->getPixelsPtr(), cursorSize, sf::Vector2u(cursorSize.x / 2, cursorSize.y / 2));

	// Set gameCursor
	gameCursor->loadFromSystem(sf::Cursor::Arrow);
		

}


void Match::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (isFinishTurn() == false) {
		this->nextTurn(deltaTime);
	}
	else {
		if (m_currentTime > m_endTime + 1.5) {
			GSM->ChangeState(STATE_END);
		}
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
	window->draw(*m_text);
	if (m_board->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())) && m_isClick == true) {
		window->setMouseCursor(*boardCursor);
	}
	else {
		window->setMouseCursor(*gameCursor);
	}
}


