#pragma once
class Checker
{
	int x;
	int y;
	bool dama;
	bool alive;
	bool bright;
	bool valid;
public:
	Checker(int x, int y, bool bright) {
		this->x = x;
		this->y = y;
		this->bright = bright;
		this->dama = false;
		this->alive = true;
		this->valid = true;
	}
	Checker() {
		this->x = -1;
		this->y = -1;
		this->valid = false;
		this->bright = false;
		this->dama = false;
		this->alive = false;
	}
	void MoveTo(int newX, int newY);
	void Die();
	int GetX() const;
	int GetY() const;
	bool IsDama() const;
	bool IsBright() const;
	bool IsAlive() const;
	bool IsValid() const;
};
///TODO: constructor