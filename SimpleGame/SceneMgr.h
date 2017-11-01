#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{
private:
	float vX;
	float vY;
	Object* obj;
	Renderer *g_Renderer;
	Object* obj_BUILDING;
	Object* obj_BULLET;
	Object* obj_ARROW;

public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int i, int Object_Type);
	void setObject(Object p);
	void ObjectCreate(const int q);
	void ObjectAllDelete(const int p);
	void RendererCreate();
	void RendererDelete();
	Renderer* getRenderer();
	void setRenderer(Renderer p);
	void ObjectCollition(int& MAX, float updateTime);
	void ObjectDraw(const int Object_Type);
};