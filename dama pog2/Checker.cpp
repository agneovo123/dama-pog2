#include "Checker.h"

//#include <iostream>
//using namespace std;

void Checker::MoveTo(int newX, int newY) {
	//cout << "[DEBUG] MoveTo(" << newX << ", " << newY << ")\n";
	if (newX < 0) { newX = 0; }
	if (newX > 7) { newX = 7; }
	if (newY < 0) { newY = 0; }
	if (newY > 7) { newY = 7; }
	this->x = newX;
	this->y = newY;
}
void Checker::Die() { this->alive = false; this->valid = false; this->x = -1; this->y = -1; }
void Checker::Upgrade() { this->dama = true; }
const bool& Checker::IsDama() const { return this->dama; }
const int& Checker::GetX() const { return this->x; }
const int& Checker::GetY() const { return this->y; }
const bool& Checker::IsBright() const { return this->bright; }
const bool& Checker::IsAlive() const { return this->alive; }
const bool& Checker::IsValid() const { return this->valid; }

const void Checker::Print() const {
	//cout << "X=" << this->x << ", Y=" << this->y << ", bright=" << this->bright << ", adr=" << addressof(this->x) << "\n";
	return;
}
