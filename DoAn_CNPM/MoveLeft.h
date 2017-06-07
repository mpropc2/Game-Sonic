#include "IButton.h"
#pragma once
class MoveLeft : public IButton
{
public:
	MoveLeft();
	virtual void execute(int &dx, int &dy);
	~MoveLeft();
};

