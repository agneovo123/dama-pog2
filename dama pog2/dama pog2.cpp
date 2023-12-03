// dama pog2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>

#include "Checker.h"
#include "Board.h"

using namespace std;

int getIntForX(string a) {
	if (a == "a") { return 0; }
	if (a == "b") { return 1; }
	if (a == "c") { return 2; }
	if (a == "d") { return 3; }
	if (a == "e") { return 4; }
	if (a == "f") { return 5; }
	if (a == "g") { return 6; }
	if (a == "h") { return 7; }
	return -1;
}
int getIntForY(string a) { return 8 - stoi(a); }

int main()
{
	// description
	cout << "Kér leírást?\n";
	cout << "1: igen\n";
	cout << "2: nem\n>>";
	string choice = "";
	cin >> choice;
	while (choice != "1" && choice != "2") { cout << "Érvénytelen válasz, add meg újra!\n>"; cin >> choice; }
	if (choice == "1") {
		cout << "- O = világos\n";
		cout << "- @ = világos dáma\n";
		cout << "- X = sötét\n";
		cout << "- # = sötét dáma\n\n";
		cout << "- Sötét kezd\n";
		cout << "- Ütéskényszer van(ütéssorozatot muszáj végrehajtani)\n";
		cout << "- Sima bábu csak előre léphet, egyesével, és lépésenként 1 - et üthet\n";
		cout << "- Szemközti sor elérésekor a bábú dámává változik\n";
		cout << "- Dáma hátrafele is léphet és üthet\n";
		cout << "- Dáma nekifutásból, egybefüggőleg bármennyi elenséges bábut üthet, túlfuthat\n\n";
		cout << "Leírás vége.\n";
		cout << "1: játék kezdése\n";
		cout << "2: kilépés\n>>";
		cin >> choice;
		while (choice != "1" && choice != "2") { cout << "Érvénytelen válasz, add meg újra!\n>"; cin >> choice; }
		if (choice == "2") { return 0; }
	}
	// board
	Board board = Board();
	board.PrintBoard();
	// gameloop 
	string a, b, c, d;
	int startX, startY, endX, endY;
	string who = "";
	do {
		if (board.isDarkTurn()) { who = "Sötét"; }
		else { who = "Világos"; }
		cout << who << " lépése.\nAdd meg a lépést (pl: \'>>b 3 a 4\')\n>>";
		cin >> a >> b >> c >> d;
		if (a == "quit") { break; }
		startX = getIntForX(a);
		startY = getIntForY(b);
		endX = getIntForX(c);
		endY = getIntForY(d);
		board.ApplyMove(startX, startY, endX, endY);
		board.PrintBoard();
	} while (!board.isGameEnd());
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
