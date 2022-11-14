#pragma once

#include "IPState.h"

class IPlayer {
public:
	virtual void changeNextState(IPState::STATE nextState) = 0;
};