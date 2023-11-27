#pragma once
#include "Checker.h"
class Board
{
	Checker bright[16];
	Checker dark[16];
public:
	void PrintEmpty() const;
};

