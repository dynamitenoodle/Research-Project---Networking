#include "Vector2.h"



Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}

void Vector2::Add(int x, int y)
{
	this->x += x;
	this->y += y;
}

void Vector2::Add(Vector2 addVec)
{
	this->x += addVec.getX();
	this->y += addVec.getY();
}
