#include "Checker.h"

#include <iostream>
using namespace std;

void Checker::MoveTo(int newX, int newY) {
	cout << "[DEBUG] MoveTo()\n";
	cout << "[DEBUG] x=" << newX << ", y=" << newY << "\n";
	if (newX < 0) { newX = 0; }
	if (newX > 7) { newX = 7; }
	if (newY < 0) { newY = 0; }
	if (newY > 7) { newY = 7; }
	this->x = newX;
	this->y = newY;
}
bool Checker::IsDama() const { return this->dama; }
void Checker::Die() { this->alive = false; }
int Checker::GetX() const { return this->x; }
int Checker::GetY() const { return this->y; }
bool Checker::IsBright() const { return this->bright; }
bool Checker::IsAlive() const { return this->alive; }
bool Checker::IsValid() const { return this->valid; }
