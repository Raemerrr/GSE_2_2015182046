#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	Position.x = 0.0;
	vX = 1.0; //X의 방향
	Position.y = 0.0;
	vY = 0.0; //Y의 방향
	Position.z = 0.0;
	Position.s = 0.0;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 1.0;
}

Object::~Object()
{
}

Data Object::getPosition()
{
	return Position;
}

void Object::setPosition(Data pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
	Position.s = pos.s;
}

Data Object::getRGB()
{
	return Rgb;
}

void Object::setRGB(Data rgb)
{
	Rgb.x = rgb.x;
	Rgb.y = rgb.y;
	Rgb.z = rgb.z;
	Rgb.s = rgb.s;
}

void Object::Update()
{
	float elapsedTime = 0.2;
	Position.x = Position.x + vX *elapsedTime;
	Position.y = Position.y + vY * elapsedTime; //현재 0
	if (Position.x > 250) {
		vX = -vX;
		vY = 1; //첫 충돌시 1로 변환.
	}
	if (Position.x < -250) {
		vX = -vX;
	}
	if (Position.y > 250) {
		vY = -vY;
	}
	if (Position.y < -250) {
		vY = -vY;
	}
}
