#include <iostream>
#include "Board.h"

using namespace std;

void Board::Setup() {
	cout << "Board::Setup()\n";
}

void Board::PrintEmpty() const
{
	cout << "Board::PrintEmpty() was called\n";
	cout << "   | a | b | c | d | e | f | g | h |   \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 8 |   |   |   |   |   |   |   |   | 8 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 7 |   |   |   |   |   |   |   |   | 7 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 6 |   |   |   |   |   |   |   |   | 6 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 5 |   |   |   |   |   |   |   |   | 5 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 4 |   |   |   |   |   |   |   |   | 4 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 3 |   |   |   |   |   |   |   |   | 3 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 2 |   |   |   |   |   |   |   |   | 2 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << " 1 |   |   |   |   |   |   |   |   | 1 \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	cout << "   | a | b | c | d | e | f | g | h |   \n";
}

Checker Board::GetCheckerAtPos(int x, int y) const {
	for (int i = 0; i < 32; i++)
	{
		if (this->checkers[i].IsAlive() && this->checkers[i].GetX() == x && this->checkers[i].GetY() == y) { return this->checkers[i]; }
	}
	return Checker();
	//return Checker(-1, -1, false);
}
void Board::DisplayChecker(Checker checker) const {
	if (checker.IsBright()) {
		if (checker.IsDama()) { cout << "@"; }
		else { cout << "O"; }
	}
	else {
		if (checker.IsDama()) { cout << "#"; }
		else { cout << "X"; }
	}
}

void Board::PrintBoard() const {
	cout << "Board::PrintBoard() was called\n";
	cout << "   | a | b | c | d | e | f | g | h |   \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	int bNum = 0;
	for (int i = 0; i < 8; i++)
	{
		bNum = (8 - i);
		cout << " " << bNum << " |";
		for (int j = 0; j < 8; j++)
		{
			// check for valid checker
			cout << " ";
			Checker checker = GetCheckerAtPos(i, j);
			if (checker.GetX() >= 0) { DisplayChecker(checker); }
			else { cout << " "; }
			cout << " |";
		}
		cout << " " << bNum << "\n";
		cout << " --+---+---+---+---+---+---+---+---+-- \n";
	}
	cout << "   | a | b | c | d | e | f | g | h |   \n";
}