#pragma once
#include "Checker.h"
class Board
{
	Checker checkers[25];
	Checker& GetCheckerAtPos(int x, int y);
	bool gameEnd;
	bool darkTurn;
	bool mustTake;
public:
	Board() {
		this->gameEnd = false;
		this->darkTurn = true;
		this->mustTake = false;
		// light
		int x = 0;
		int y = 0;
		for (int i = 0; i < 12; i++)
		{
			this->checkers[i] = Checker(x, y, true);
			x += 2;
			if (x > 7)
			{
				if (x % 2 == 0) { x = 1; }
				else { x = 0; }
				y++;
			}
		}
		// dark
		x = 1;
		y = 5;
		for (int i = 12; i < 24; i++)
		{
			this->checkers[i] = Checker(x, y, false);
			x += 2;
			if (x > 7)
			{
				if (x % 2 == 0) { x = 1; }
				else { x = 0; }
				y++;
			}
		}
		// the 25th is the invalid one
		this->checkers[24] = Checker();
	}
	void DisplayChecker(Checker checker) const;
	void setTurn(bool turn);
	void toggleTurn();
	void ApplyMove(int startX, int startY, int endX, int endY);
	bool TakeCheck();
	void PrintBoard();
	const bool& isDarkTurn() const;
	const bool& isGameEnd() const;
	const bool& MustTake() const;
};

