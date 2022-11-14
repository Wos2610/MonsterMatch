#pragma once

#include "IEState.h"

class IEnemy {
public:
	virtual void changeNextState(IEState::STATE nextState) = 0;
};