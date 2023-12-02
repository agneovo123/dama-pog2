#pragma once
class Checker
{
	int x;
	int y;
	bool isDama;
	bool alive;
	bool isBright;
	bool valid;
public:
	Checker(int x, int y, bool bright) {
		this->x = x;
		this->y = y;
		this->isBright = bright;
		this->isDama = false;
		this->alive = true;
		this->valid = true;
	}
	Checker() {
		this->x = -1;
		this->y = -1;
		this->valid = false;
		this->isBright = false;
		this->isDama = false;
		this->alive = false;
	}
	void MoveTo(int x, int y);
	void Die();
	int GetX() const;
	int GetY() const;
	bool IsDama() const;
	bool IsBright() const;
	bool IsAlive() const;
	bool IsValid() const;
};
///TODO: constructor