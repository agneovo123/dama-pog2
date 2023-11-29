#pragma once
class Checker
{
	int x;
	int y;
	bool isDama;
	bool alive;
	bool isBright;
public:
	//void Checker();
	void MoveTo(int x, int y);
	void Die();
	int GetX() const;
	int GetY() const;
	bool IsDama() const;
	bool IsBright() const;
	bool IsAlive() const;
};
///TODO: constructor