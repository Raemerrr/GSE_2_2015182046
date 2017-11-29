#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{
private:
	float vX;
	float vY;
	float CharMove;
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
	GLuint BackgroundImg;
	GLuint Charater1Img;
	GLuint Charater2Img;
public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int, int);
	void setObject(Object);
	void ObjectCreate(const int);
	void ObjectAllDelete(const int);
	void RendererCreate();
	void RendererDelete();
	void ObjectCollition1();
	void ObjectCollition2();
	//void ObjectCollition(int&, float);
	void ObjectDraw(const int, float&);
	void Update(float updateTime);
};