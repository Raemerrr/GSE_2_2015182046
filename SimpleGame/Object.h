#pragma once
#include "stdafx.h"
typedef struct data {
	float x;
	float y;
	float z;
	float s;
}Data;

class Object
{
private:
	Data Position;
	Data Rgb;
	Data Direction;
	float vX;
	float vY;
public:
	Object();
	~Object();

	Data getPosition();
	void setPosition(Data p);
	Data getRGB();
	void setRGB(Data p);
	Data Object::getDirection();
	void Object::setDirection(Data p);

	void Update();

};