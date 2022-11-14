#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSEnd.h"
//#include "GSSetting.h"
//#include "GSHighScore.h"
//#include "GSAbout.h"

GameStateBase* GameStateBase::CreateState(StateTypes st) {
	GameStateBase* gs = nullptr;
	switch (st)
	{
	case STATE_INVALID:
		break;
	case STATE_INTRO:
		gs = new GSIntro();
		break;
	case STATE_MENU:
		gs = new GSMenu();
		break;
	case STATE_PLAY:
		gs = new GSPlay();
		break;
	case STATE_SETTING:
		//gs = new GSSetting();
		break;
	case STATE_ABOUT:
		//gs = new GSAbout();
		break;
	case STATE_PAUSE:
		//gs = new GSHighScore();
		break;
	case STATE_END:
		gs = new GSEnd();
		break;
	default:
		break;
	}
	return gs;
}