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

public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int i);
	void setObject(Object p);
	void ObjectCreate(const int p, const int q);
	void ObjectDelete();
	void RendererCreate();
	void RendererDelete();
	Renderer* getRenderer();
	void setRenderer(Renderer p);
	void ObjectCollition(int i, int& MAX, int Size);
};