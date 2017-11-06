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
	int bulletCount;
	int emptyBullet;

public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int, int);
	void setObject(Object);
	void ObjectCreate(const int);
	void ObjectAllDelete(const int);
	void RendererCreate();
	void RendererDelete();
	Renderer* getRenderer();
	void setRenderer(Renderer);
	void ObjectCollition(int&, float);
	void ObjectDraw(const int,int&);
};