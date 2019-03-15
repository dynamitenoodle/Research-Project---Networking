#pragma once
class Vector2
{
public:
	Vector2(int x, int y);
	~Vector2();

	int getX() { return x; }
	int getY() { return y; }

	void Add(int x, int y);
	void Add(Vector2 addVec);

private:
	int x;
	int y;
};

