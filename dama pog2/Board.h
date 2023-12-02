#pragma once
#include "Checker.h"
class Board
{
	Checker checkers[24];
	Checker GetCheckerAtPos(int x, int y) const;
	bool gameEnd;
	bool darkTurn;
public:
	Board() {
		this->gameEnd = false;
		this->darkTurn = true;
		// light
		int x = 1;
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
		// light dark
		x = 0;
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
	}
	void DisplayChecker(Checker checker) const;
	void setTurn(bool turn);
	void toggleTurn(bool turn);
	void ApplyMove(int startX, int startY, int endX, int endY);
	void PrintBoard() const;
	bool isDarkTurn() const;
	bool isGameEnd() const;
};

