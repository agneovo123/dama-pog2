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
	void Upgrade();
	const int& GetX() const;
	const int& GetY() const;
	const bool& IsDama() const;
	const bool& IsBright() const;
	const bool& IsAlive() const;
	const bool& IsValid() const;
	const void Print() const;
};
///TODO: constructor