#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	Position.x = 999.0;		//겹치지 않는 위치에서 시작하기 위함.(맵상에 존재 않하는 것 처럼)
	Position.y = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
	Position.z = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
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
	objLife = 1000.0; //라이프
	lifeTime = 1000.0; //라이프
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

float Object::getObjLife()
{
	return objLife;
}

void Object::setObjLife(float p)
{
	objLife += p;
}

float Object::getObjLifeTime()
{
	return lifeTime;
}

void Object::setObjLifeTime(float p)
{
	lifeTime = p;
}

void Object::Update(float elapsedTime)
{
	elapsedTime = elapsedTime / 1000.f;
	if (!(lifeTime <= 0.0f))
	{
		lifeTime -= 1.0;
	}
	float objSpeed = 100;
	Position.x = Position.x + vX * elapsedTime * objSpeed;
	Position.y = Position.y + vY * elapsedTime * objSpeed;
	if (Position.x > 250) {
		vX = -vX;
		vY = rand() % 2;
	}
	if (Position.x < -250) {
		vX = -vX;
		vY = rand() % 2;
	}
	if (Position.y > 250) {
		vY = -vY;
		vX = rand() % 2;
	}
	if (Position.y < -250) {
		vY = -vY;
		vX = rand() % 2;
	}
}
