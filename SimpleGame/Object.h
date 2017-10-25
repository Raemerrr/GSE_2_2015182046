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
	float objLife;
	float lifeTime;

public:
	Object();
	~Object();

	Data getPosition();
	void setPosition(Data p);
	Data getRGB();
	void setRGB(Data p);
	Data getDirection();
	void setDirection(Data p);
	float getObjLife();
	void setObjLife(float a);
	float getObjLifeTime();
	void setObjLifeTime(float a);
	void Update(float elapsedTime);

};