#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	Position.x = 0.0;
	Position.y = 0.0;
	Position.z = 0.0;
	Position.s = 0.0;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 1.0;
	vX = 0.0; //X의 방향
	vY = 0.0; //Y의 방향
	
	Direction.x = 0.0;
	Direction.y = 0.0;
	Direction.z = 0.0;//삭제 유무
	Direction.s = 0.0;//삭제 유무
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

Data Object::getDirection()
{
	return Direction;
}

void Object::setDirection(Data p)
{
	vX = p.x;
	vY = p.y;
}

void Object::Update()
{
	
	float elapsedTime = 0.05;
	Position.x = Position.x + vX * elapsedTime;
	Position.y = Position.y + vY * elapsedTime;
	if (Position.x > 250) {
		vX = -vX;
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
