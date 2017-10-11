#include "stdafx.h"
#include "Object.h"

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

void Object::Update(Data pos)
{
	float elapsedTime = 1.5;
	Position.x += pos.x*elapsedTime;
	Position.y += pos.y*elapsedTime;
	Position.z = pos.z*elapsedTime;
}
