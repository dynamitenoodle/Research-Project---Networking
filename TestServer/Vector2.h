#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float getX() { return x; }
	float getY() { return y; }

	void Add(float x, float y);
	void Add(Vector2 addVec);

private:
	float x;
	float y;
};
