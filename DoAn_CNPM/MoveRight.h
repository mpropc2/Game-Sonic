#include "IButton.h"
#pragma once
class MoveRight : public IButton
{
public:
	MoveRight();
	void execute(int &dx, int &dy);
	~MoveRight();
};

