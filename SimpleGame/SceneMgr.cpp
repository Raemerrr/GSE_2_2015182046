#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	obj = NULL;
	g_Renderer = NULL;
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::ObjectCreate(const int NUM, const int SIZE)
{
	obj = new Object[NUM]();

	for (int i = 0; i < NUM; ++i)
	{
		Data temp1 = { (float)((rand() % 500) - 200),(float)(200 - (rand() % 500)),0,SIZE };
		Data temp2 = { 255,255, 255,1.0 }; //Èò»öÅëÀÏ 
		float checkX = 1;
		float checkY = 1;

		if (rand() % 2 == 1)
		{
			checkX *= -1;
		}if (rand() % 2 == 1)
		{
			checkY *= -1;
		}
		Data temp3 = { checkX, checkY ,0.0f,0.0f };
		obj[i].setPosition(temp1);
		obj[i].setRGB(temp2);
		obj[i].setDirection(temp3);
	}

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

void SceneMgr::RendererCreate() {
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

void SceneMgr::RendererDelete() {
	delete g_Renderer;
}

Renderer* SceneMgr::getRenderer() {
	return g_Renderer;
}

void SceneMgr::setRenderer(Renderer p) {
}

void SceneMgr::ObjectCollition(int i, int MAX, int objectSize)
{
	int Size = objectSize / 2;
	Data Red = { 255,0, 0,1.0 }; //»¡°­ÅëÀÏ 
	Data White = { 255,255, 255,1.0 };
	Data Rect1 = obj[i].getPosition();
	for (int j = 0; j < MAX; ++j)
	{
		if (i == j)
		{
			continue;
		}
		Data Rect2 = obj[j].getPosition();
		if ((Rect1.x - Size) < (Rect2.x + Size) && (Rect1.x + Size) > (Rect2.x - Size) && (Rect1.y - Size) < (Rect2.y + Size) && (Rect1.y + Size) > (Rect2.y - Size))
		{
			obj[i].setRGB(Red);
			obj[j].setRGB(Red);
		}
	}
}