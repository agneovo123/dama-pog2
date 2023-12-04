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
Checker& Board::GetCheckerAtPos(int x, int y) {
	for (int i = 0; i < 24; i++)
	{
		if (this->checkers[i].IsAlive() && this->checkers[i].GetX() == x && this->checkers[i].GetY() == y) {
			//cout << "[DEBUG] GetCheckerAtPos returning with i=" << i << "\n";
			return this->checkers[i];
		}
	}
	return this->checkers[24];
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

void Board::PrintBoard() {
	cout << "Board::PrintBoard()\n";
	bool useRealCoords = false;
	if (useRealCoords) { cout << "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   \n"; }
	else { cout << "   | a | b | c | d | e | f | g | h |   \n"; }
	cout << " --+---+---+---+---+---+---+---+---+-- \n";
	int bNum = 0;
	for (int i = 0; i < 8; i++)
	{
		if (useRealCoords) { bNum = i; }
		else { bNum = (8 - i); }
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
	if (useRealCoords) { cout << "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   \n"; }
	else { cout << "   | a | b | c | d | e | f | g | h |   \n"; }
}

void Board::ApplyMove(int startX, int startY, int endX, int endY) {
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
	Checker& start = GetCheckerAtPos(startX, startY);
	// start exists
	if (!start.IsValid()) { cout << "Játék >> A kezdőhelyen nincs bábu!\n"; return; }
	// bright to bright, dark to dark; IsBright and darkTurn are inverted
	if (start.IsBright() == this->darkTurn) { cout << "Játék >> Ellenfél bábuját nem mozgathatod!\n"; return; }
	// can't step on another checker
	Checker& end = GetCheckerAtPos(endX, endY);
	if (end.IsValid()) {
		if (end.IsBright() == this->darkTurn) {
			cout << "Játék >> Érvénytelen lépés: ellenségre nem léphetsz!\n";
			return;
		}
		cout << "Játék >> Érvénytelen lépés: Másik bábura nem léphetsz!\n";
		return;
	}
	// 'dáma' can step everyehere
	if (start.IsDama()) {
		bool moveAccepted = false;
		// 'dáma' can take with runup and runoff
		if (abs(endY - startY) == abs(endX - startX) && endX - startX > 1) {
			int xDir = endX > startX ? 1 : -1;
			int yDir = endY > startY ? 1 : -1;
			int checkY = startY + yDir;
			// runup, enemy checker 'line', runoff checking
			bool state = false;
			bool oldState = false;
			int stateCount = 0;
			for (int i = startX + xDir; i <= endX; i += xDir)
			{
				oldState = state;
				Checker& target = GetCheckerAtPos(i, checkY);
				checkY += yDir;
				if (target.IsValid()) { state = true; }
				else { state = false; }
				if (state != oldState) { stateCount++; }
				if (target.IsValid() && target.IsBright() != this->darkTurn) { cout << "Játék >> Érvénytelen lépés: saját bábut/bábukat nem üthetsz le.\n"; return; }
			}
			if (stateCount == 0 || stateCount == 1) { cout << "Játék >> Ezt hogy csináltad? Dámával léptél, és a stateCount kevesebb, mint 2.\nJáték >> ő... Érvénytelen lépés.\n"; return; }
			// taking is only valid, if stateCount is 2
			if (stateCount == 2) {
				checkY = startY + yDir;
				for (int i = startX + xDir; i <= endX; i += xDir)
				{
					Checker& target = GetCheckerAtPos(i, checkY);
					checkY += yDir;
					if (target.IsValid()) { target.Die(); }
				}
				// succesful takes --> move
				start.MoveTo(endX, endY);
			}
			else { cout << "Játék >> Érvénytelen lépés: több ellenséget csak úgy üthetsz le, ha azok közvetlenül egymás \'mellett\' vannak\n"; return; }
		}
		else if (endX - startX > 1 || endY - startY > 1) { cout << "Játék >> Csak átlósan tudsz ütni / lépni!\n"; return; }
		// 'dáma' steps one-by-one
		if (!moveAccepted) {
			// height check
			if (abs(endY - startY) != 1) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
			// widht check
			if (abs(endX - startX) != 1) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
			// successful step --> move
			start.MoveTo(endX, endY);
		}
	}
	// Normal
	else {
		bool moveAccepted = false;
		// take (2 step) check
		int updown = -2;
		if (start.IsBright()) { updown = 2; }
		if (endY - startY == updown && abs(endX - startX) == 2) {
			Checker& target = GetCheckerAtPos((startX + endX) / 2, (startY + endY) / 2);
			// there is no target --> invalid step
			if (!target.IsValid()) { cout << "Játék >> Túl nagy lépés!\n"; return; }
			// there is a target:
			else {
				// target was enemy --> it dies
				if (target.IsBright() == this->darkTurn) { target.Die(); }
				// target was friendly --> invalid step
				else { cout << "Játék >> Saját bábut nem tudsz leütni!\n"; return; }
			}
			// succesful take --> move
			start.MoveTo(endX, endY);
			moveAccepted = true;
		}
		// single step check
		// bright only step down (y+) start > end
		// dark only step up (y-) start < end
		if (!moveAccepted) {
			updown = -1;
			if (start.IsBright()) { updown = 1; }
			cout << "[DEBUG] (endY - startY)=" << (endY - startY) << " , updown=" << updown << " , start.IsBright()=" << start.IsBright() << "\n";
			// height check
			if (endY - startY != updown) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
			// widht check
			if (abs(endX - startX) != 1) { cout << "Játék >> Túl nagy, vagy túl kicsi lépés!\n"; return; }
			start.MoveTo(endX, endY);
			moveAccepted = true;
		}

		// upgrade to 'dáma' at the ends of the board
		if (moveAccepted) {
			if (start.IsBright() && updown > 0) {
				if (endY == 7) { start.Upgrade(); }
			}
			if (!start.IsBright() && updown < 0) {
				if (endY == 0) { start.Upgrade(); }
			}
		}
	}

	// check game end (no alive from enemy)
	bool allDead = true;
	for (int i = 0; i < 24; i++)
	{
		Checker& target = checkers[i];
		if (target.IsAlive() && target.IsBright() == this->darkTurn) { allDead = false; break; }
	}
	if (allDead) {
		this->gameEnd = true;
		cout << "Játék >> JÁTÉK VÉGE! " << (this->darkTurn ? "Sötét" : "Világos") << " nyert.\n";
	}

	// check ütéskényszer
	if (!TakeCheck()) {
		// flip turns
		toggleTurn();
		// check for enemy's turn aswell.
		if (TakeCheck()) { cout << "Játék >> ÜTÉSKÉNYSZER! " << (this->darkTurn ? "Sötétnek" : "Világosnak") << " ütnie kell!\n"; }
	}
	else { cout << "Játék >> ÜTÉSKÉNYSZER! " << (this->darkTurn ? "Sötétnek" : "Világosnak") << " ütnie kell!\n"; }
	return;
}

bool Board::TakeCheck() {
	// needs to check every checker
	for (int index = 0; index < 24; index++)
	{
		Checker& start = checkers[index];
		int startX = start.GetX();
		int startY = start.GetY();
		// don't check enemy's checkers
		if (start.IsBright() == this->darkTurn) { continue; }
		// brute force check
		if (start.IsDama()) {
			// case: + +
			int xDir = 1;
			int yDir = 1;
			int j = startY + yDir;
			bool state = false;
			bool oldState = false;
			int stateCount = 0;
			for (int i = startX + xDir; i < 8 && j < 8; i += xDir)
			{
				oldState = state;
				Checker& target = GetCheckerAtPos(i, j);
				j += yDir;
				if (target.IsValid()) { state = true; }
				else { state = false; }
				if (state != oldState) { stateCount++; }
				if (target.IsValid() && target.IsBright() != this->darkTurn) { break; }
				if (stateCount == 2) { return true; }
			}
			// case: + -
			xDir = 1;
			yDir = -1;
			j = startY + yDir;
			state = false;
			oldState = false;
			stateCount = 0;
			for (int i = startX + xDir; i < 8 && j >= 0; i += xDir)
			{
				oldState = state;
				Checker& target = GetCheckerAtPos(i, j);
				j += yDir;
				if (target.IsValid()) { state = true; }
				else { state = false; }
				if (state != oldState) { stateCount++; }
				if (target.IsValid() && target.IsBright() != this->darkTurn) { break; }
				if (stateCount == 2) { return true; }
			}
			// case: - +
			xDir = -1;
			yDir = 1;
			j = startY + yDir;
			state = false;
			oldState = false;
			stateCount = 0;
			for (int i = startX + xDir; i >= 0 && j < 8; i += xDir)
			{
				oldState = state;
				Checker& target = GetCheckerAtPos(i, j);
				j += yDir;
				if (target.IsValid()) { state = true; }
				else { state = false; }
				if (state != oldState) { stateCount++; }
				if (target.IsValid() && target.IsBright() != this->darkTurn) { break; }
				if (stateCount == 2) { return true; }
			}
			// case: - -
			xDir = -1;
			yDir = -1;
			j = startY + yDir;
			state = false;
			oldState = false;
			stateCount = 0;
			for (int i = startX + xDir; i >= 0 && j >= 0; i += xDir)
			{
				oldState = state;
				Checker& target = GetCheckerAtPos(i, j);
				j += yDir;
				if (target.IsValid()) { state = true; }
				else { state = false; }
				if (state != oldState) { stateCount++; }
				if (target.IsValid() && target.IsBright() != this->darkTurn) { break; }
				if (stateCount == 2) { return true; }
			}
		}
		else {
			// hard-coded check
			if (start.IsBright()) {
				// case: + +
				if (startX < 6 && startY < 6) {
					Checker& target = GetCheckerAtPos(startX + 1, startY + 1);
					Checker& end = GetCheckerAtPos(startX + 2, startY + 2);
					if (target.IsValid() && target.IsBright() == this->darkTurn && !end.IsValid()) { return true; }
				}
				// case: - +
				if (startX > 1 && startY < 6) {
					Checker& target = GetCheckerAtPos(startX - 1, startY + 1);
					Checker& end = GetCheckerAtPos(startX - 2, startY + 2);
					if (target.IsValid() && target.IsBright() == this->darkTurn && !end.IsValid()) { return true; }
				}
			}
			else {
				// case: + -
				if (startX < 6 && startY > 1) {
					Checker& target = GetCheckerAtPos(startX + 1, startY - 1);
					Checker& end = GetCheckerAtPos(startX + 2, startY - 2);
					if (target.IsValid() && target.IsBright() == this->darkTurn && !end.IsValid()) { return true; }
				}
				// case: - -
				if (startX > 1 && startY > 1) {
					Checker& target = GetCheckerAtPos(startX - 1, startY - 1);
					Checker& end = GetCheckerAtPos(startX - 2, startY - 2);
					if (target.IsValid() && target.IsBright() == this->darkTurn && !end.IsValid()) { return true; }
				}
			}
		}
	}
	return false;
}

const bool& Board::isDarkTurn() const { return this->darkTurn; }
const bool& Board::isGameEnd() const { return this->gameEnd; }
void Board::setTurn(bool turn) { this->darkTurn = turn; }
void Board::toggleTurn() { this->darkTurn = !this->darkTurn; }


