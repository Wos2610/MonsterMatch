#pragma once
#include "../GameManager/Singleton.h"
#include <list>


#define GSM GameStateMachine::GetInstance()

class GameStateBase;

enum StateTypes
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	STATE_SETTING,
	STATE_ABOUT,
	STATE_PAUSE,
	STATE_END,
	STATE_LEVEL
};

class GameStateMachine :public CSingleton<GameStateMachine> {
public:
	GameStateMachine();
	~GameStateMachine();

	GameStateBase* getCurrentState();
	void ChangeState(GameStateBase* state);
	void ChangeState(StateTypes st);
	void PushState(StateTypes st);
	void PopState();

	void PerformStateChange();

	GameStateBase* currentState() const;
	GameStateBase* nextState() const;
	bool NeedToChangeState();
	bool HasState();


private:
	std::list<GameStateBase*> m_StateStack;
	GameStateBase* m_ActivesState;
	GameStateBase* m_NextState;
};