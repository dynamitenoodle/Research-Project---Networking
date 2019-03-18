#include "Vector2.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}

void Vector2::Add(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Vector2::Add(Vector2 addVec)
{
	this->x += addVec.getX();
	this->y += addVec.getY();
}
