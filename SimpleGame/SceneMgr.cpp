#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"
SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::ObjectCreate(const int NUM)
{
	obj = new Object[NUM]();
}

void SceneMgr::ObjectDelete()
{
	delete[] obj;
}

Object* SceneMgr::getObject(int i)
{
	return &obj[i];
}

void SceneMgr::setObject(Object pos)
{
}

void SceneMgr::ObjectCollition(int i, int MAX, int objectSize)
{
	Data Red = { 255,0, 0,1.0 }; //빨강통일 
	Data White = { 255,255, 255,1.0 };
	Data Rect1 = obj[i].getPosition();
	int Size = objectSize / 2;

	
	for (int j = 0; j < MAX; ++j)
	{
		Data Rect2 = obj[j].getPosition();
		if ((Rect1.x - Size) < (Rect2.x + Size) && (Rect1.y - Size) > (Rect2.y + Size) && (Rect1.x + Size) >(Rect2.x - Size) && (Rect1.y + Size) < (Rect2.y - Size))
		{
			std::cout << "충돌함" << std::endl;
			obj[i].setRGB(Red);
		}
		obj[i].setRGB(White);
		break;
	}
}