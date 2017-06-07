#include "IButton.h"
#pragma once
class MoveDown : public IButton
{
public:
	MoveDown();
	void execute(int &dx, int &dy);
	~MoveDown();
};

