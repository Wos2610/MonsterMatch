#pragma once
#include<SFML/Graphics.hpp>
#include"Block.h"
#include<iostream>
#include<map>
#include"../GameConfig.h"

using namespace std;

class Match {
public:
	Match();
	~Match();
	// Board : row, col
	// monsterNum : so cap o can noi
	void Init(int row, int col, int monsterNum);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	sf::Vector2f getRootMatch();
	sf::Vector2f getMatchSize();
	int getMonsterNum();

	// Neu o connected thi monster se death
	int getConnectedBlock();
	void setConnectedBlock(int color);
	// Neu o revoked thi monster se idle 
	int getRevokedBlock();
	void setRevokedBlock(int color);

private:
	// So row & col cua board
	int m_row;
	int m_col;
	// So cap o can noi = so monster can tieu diet
	int m_monsterNum;

	float m_clickTime;
	float m_currentTime;

	// So cap o can noi o thoi diem hien tai
	int m_blockSum;

	// Color cua o nhung chi khi start turn
	int m_currentBlockType;
	// Luu mark cua o da chon
	int m_isMatching;
	// So lan click
	int m_clickNum;

	// Luu ma tran danh dau
	map<pair<int, int>, int> m_mark;
	
	vector<int> m_notConnectedBlockList;
	vector<int> m_connectedBlockList;
	map<pair<int, int>, int> m_startTurnMark;
	map<map<pair<int, int>, int>, int> m_startTurnMarkMap;

	sf::RectangleShape* m_frame;

	// Board
	sf::RectangleShape* m_board;
	// Grid
	Block* m_grid[10][10];

	// O ben trai tren cung cua board
	sf::Vector2f m_rootBoard;
	// Kich thuoc cua 1 grid
	sf::Vector2f m_gridSize;
	// Kich thuoc cua match
	sf::Vector2f m_matchSize;
	// Vi tri xuat phat khi start turn
	sf::Vector2i m_startTurnBlock;

	// Check da noi het cac o chua 
	bool m_isFinishTurn;
	bool m_isNextTurn;
	// Check bat dau turn moi : true thi dang ve
	bool m_isClick;
	// Check co duong noi o giua duong dang dinh ve thi khong the ve tiep
	bool m_isCanContinueDraw;
	// Check xem co vua chay qua ham revoke khong
	bool m_isRevoke;
	// O noi thanh cong
	int m_isConnectedBlock;
	int m_isRevokedtedBlock;

	
	sf::Vector2f calGridSize(int row, int col);

	void initBoard();
	void initBlock(int color, int row1, int col1, int row2, int col2);
	
	void revokeDrawing(int i, int j);
	void startDrawing(int i, int j);
	void drawing(int i, int j);
	void endDrawing(int i, int j);

	void nextTurn(float deltaTime);
	void runTurn(float deltaTime);
	void currentTurn(float deltaTime);

	bool isFinishTurn();
	bool isContinueNextTurn();
	


};
