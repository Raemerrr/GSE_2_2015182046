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
	Renderer* g_Renderer;
	Object* obj_BUILDING;
	Object* obj_BULLET;
	Object* obj_ARROW;
	int bulletCount;
	int arrowCount;
	int AICharCount;
	GLuint team1BulidingImg;
	GLuint team2BulidingImg;

public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int, int);
	void setObject(Object);
	void ObjectCreate(const int);
	void ObjectAllDelete(const int);
	void RendererCreate();
	void RendererDelete();
	void ObjectCollition1(float);
	void ObjectCollition2(float);
	//void ObjectCollition(int&, float);
	void ObjectDraw(const int, float&);
};