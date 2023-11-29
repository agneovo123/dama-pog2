#pragma once
#include "Checker.h"
class Board
{
	Checker checkers[32];
	Checker GetCheckerAtPos(int x, int y) const;
public:
	void Setup();
	void DisplayChecker(Checker checker) const;
	void PrintEmpty() const;
	void PrintBoard() const;
};

