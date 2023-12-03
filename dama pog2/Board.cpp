#include <iostream>
#include "Board.h"

using namespace std;
/// TODO:
/// -GetCheckerAtPos() needs to return reference
///  -invalid checker should also be a reference

/// <summary>
/// checks if any of the checkers are in a specific position
/// </summary>
/// <param name="x">: x coordinate</param>
/// <param name="y">: y coordinate</param>
/// <returns>the found checker, if there aren't any in the specified position, it returns a checker with invalid positions</returns>
Checker Board::GetCheckerAtPos(int x, int y) const {
	for (int i = 0; i < 24; i++)
	{
		if (this->checkers[i].IsAlive() && this->checkers[i].GetX() == x && this->checkers[i].GetY() == y) {
			cout << "[DEBUG] GetCheckerAtPos returning with i=" << i << "\n";
			return this->checkers[i];
		}
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
	//cout << "   | a | b | c | d | e | f | g | h |   \n";
	cout << "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   \n";
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	int bNum = 0;
	for (int i = 0; i < 8; i++)
	{
		//bNum = (8 - i);
		bNum = i;
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
	//cout << "   | a | b | c | d | e | f | g | h |   \n";
	cout << "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   \n";
}

void Board::ApplyMove(int startX, int startY, int endX, int endY) {
	cout << "[DEBUG] > all checkers before move\n";
	for (int i = 0; i < 24; i++) {
		cout << "i=" << i << ", X=" << checkers[i].GetX() << ", Y=" << checkers[i].GetY() << ", bright=" << checkers[i].IsBright() << "\n";
	}
	cout << "ApplyMove()\n";
	cout << "[DEBUG] > startX=" << startX << ", startY=" << startY << ", endX=" << endX << ", endY=" << endY << "\n";
	// limit inputs
	if (startY < 0) { cout << "Játék >> Nem léphetsz le a tábláról\n"; return; }
	if (startY > 7) { cout << "Játék >> Nem léphetsz le a tábláról\n"; return; }
	if (endY < 0) { cout << "Játék >> Nem léphetsz le a tábláról\n"; return; }
	if (endY > 7) { cout << "Játék >> Nem léphetsz le a tábláról\n"; return; }
	cout << "[DEBUG] > startX=" << startX << ", startY=" << startY << ", endX=" << endX << ", endY=" << endY << "\n";
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
		Checker end = GetCheckerAtPos(endX, endY);
		if (end.IsValid()) {
			if (end.IsBright() == this->darkTurn) {
				cout << "Játék >> Érvénytelen lépés: ellenségre nem léphetsz!\n"; return;
			}
			cout << "Játék >> Érvénytelen lépés: Másik bábura nem léphetsz!\n"; return;
		}
		// take (2 step) check
		int updown = -2;
		if (start.IsBright()) { updown = 2; }
		if (endY - startY == updown && abs(endX - startX) == 2) {
			Checker target = GetCheckerAtPos((startX + endX) / 2, (startY + endY) / 2);
			// there is no target --> invalid step
			if (!target.IsValid()) { cout << "Játék >> Túl nagy lépés!\n"; return; }
			// there is a target:
			else {
				// target was enemy --> it dies
				if (target.IsBright() == this->darkTurn) { target.Die(); }
				// target was friendly -> invalid step
				else { cout << "Játék >> Saját bábut nem tudsz leütni!\n"; return; }
			}
			start.MoveTo(endX, endY);
		}
		// single step check
		// light only step down (y+) start > end
		// dark only step up (y-) start < end
		updown = -1;
		if (start.IsBright()) { updown = 1; }
		cout << "[DEBUG] (endY - startY)=" << (endY - startY) << " , updown=" << updown << " , start.IsBright()=" << start.IsBright() << "\n";
		// height check
		if (endY - startY != updown) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
		// widht check
		if (abs(endX - startX) != 1) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
		start.MoveTo(endX, endY);
	}
	cout << "[DEBUG] > all checkers AFTER move\n";
	for (int i = 0; i < 24; i++) {
		cout << "i=" << i << ", X=" << checkers[i].GetX() << ", Y=" << checkers[i].GetY() << ", bright=" << checkers[i].IsBright() << "\n";
	}
	return;
}

bool Board::isDarkTurn() const { return this->darkTurn; }
bool Board::isGameEnd() const { return this->gameEnd; }
void Board::setTurn(bool turn) { this->darkTurn = turn; }
void Board::toggleTurn(bool turn) { this->darkTurn = !this->darkTurn; }

