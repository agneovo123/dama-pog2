#include <iostream>
#include "Board.h"

using namespace std;

/// <summary>
/// checks if any of the checkers are in a specific position
/// </summary>
/// <param name="x">: x coordinate</param>
/// <param name="y">: y coordinate</param>
/// <returns>the found checker, if there aren't any in the specified position, it returns a checker with invalid positions</returns>
Checker Board::GetCheckerAtPos(int x, int y) const {
	for (int i = 0; i < 24; i++)
	{
		if (this->checkers[i].IsAlive() && this->checkers[i].GetX() == x && this->checkers[i].GetY() == y) { return this->checkers[i]; }
	}
	return Checker();
}

/// <summary>
/// displays a checker
/// (would be better to have this as the Checker's toString())
/// https://stackoverflow.com/questions/5171739/tostring-override-in-c
/// </summary>
/// <param name="checker">: which checker to display</param>
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
	cout << "Board::PrintBoard()\n";
	cout << "   | a | b | c | d | e | f | g | h |   \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	int bNum = 0;
	for (int i = 0; i < 8; i++)
	{
		bNum = (8 - i);
		cout << " " << bNum << " |";
		for (int j = 0; j < 8; j++)
		{
			cout << " ";
			Checker checker = GetCheckerAtPos(j, i);
			// check for valid checker
			if (checker.GetX() >= 0) { DisplayChecker(checker); }
			else { cout << " "; }
			cout << " |";
		}
		cout << " " << bNum << "\n";
		cout << " --+---+---+---+---+---+---+---+---+-- \n";
	}
	cout << "   | a | b | c | d | e | f | g | h |   \n";
}

void Board::ApplyMove(int startX, int startY, int endX, int endY) {
	// limit inputs
	if (startY < 0) { startY = 0; }
	if (startY > 7) { startY = 7; }
	if (endY < 0) { endY = 0; }
	if (endY > 7) { endY = 7; }
	// check for invalid col index
	if (startX == -1 || endX == -1) { cout << "Játék >> Érvénytelen oszlop érték! Az oszlop csak \'abcdefgh\' kisbetűk egyike lehet.\n"; return; }
	Checker start = GetCheckerAtPos(startX, startY);
	// start exists
	if (!start.IsValid()) { cout << "Játék >> A kezdőhelyen nincs bábu!\n"; return; }
	// bright to bright, dark to dark; IsBright and darkTurn are inverted
	if (start.IsBright() == this->darkTurn) { cout << "Játék >> Ellenfél bábuját nem mozgathatod!\n"; return; }
	// 'dáma' can step everyehere
	if (start.IsDama()) {

	}
	else {
		// light only step down (y+) start > end
		// dark only step up (y-) start < end
		int updown = 1;
		if (start.IsBright()) { updown = -1; }
		// height check
		if (endY - startY != updown) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
		// widht check
		if (endX - startX != -1 && endX - startX != 1) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
		// 
		Checker end = GetCheckerAtPos(endX, endY);
		if (end.IsValid()) {
			if (end.IsBright() == this->darkTurn)
			{
				cout << "Játék >> Érvénytelen lépés: ellenségre nem léphetsz!\n"; return;
			}
		}
	}
	return;
}

bool Board::isDarkTurn() const { return this->darkTurn; }
bool Board::isGameEnd() const { return this->gameEnd; }
void Board::setTurn(bool turn) { this->darkTurn = turn; }
void Board::toggleTurn(bool turn) { this->darkTurn = !this->darkTurn; }

