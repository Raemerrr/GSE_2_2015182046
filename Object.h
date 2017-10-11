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

public:
	Object();
	~Object();

	Data getPosition();
	void setPosition(Data p);
	Data getRGB();
	void setRGB(Data p);
	void Update(Data p);


private:
	Data Position;
	Data Rgb;
};