#include "IButton.h"
#pragma once
class MoveUp : public IButton
{
public:
	MoveUp();
	void execute(int &dx, int &dy);
	~MoveUp();
};

