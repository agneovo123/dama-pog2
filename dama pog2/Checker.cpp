#include "Checker.h"

void Checker::MoveTo(int x, int y) {
	if (x < 0) { x = 0; }
	if (x > 7) { x = 7; }
	if (y < 0) { y = 0; }
	if (y > 7) { y = 7; }
	this->x = x;
	this->y = y;
}
bool Checker::IsDama() const { return this->isDama; }
void Checker::Die() { this->alive = false; }
int Checker::GetX() const { return this->x; }
int Checker::GetY() const { return this->y; }
bool Checker::IsBright() const { return this->isBright; }
bool Checker::IsAlive() const { return this->alive; }
bool Checker::IsValid() const { return this->valid; }
