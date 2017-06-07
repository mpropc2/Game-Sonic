#pragma once
class IButton
{
public:
	virtual void execute(int &dx, int &dy);
	IButton();
	~IButton();
};

