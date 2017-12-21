#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"

class SceneMgr
{
private:
	float ParticleClimateTime;
	float vX;
	float vY;
	Object* skyObj;
	Object* obj;
	Renderer* g_Renderer;
	Object* obj_BUILDING;
	Object* obj_BULLET;
	Object* obj_ARROW;
	int bulletCount;
	int arrowCount;
	int AICharCount;
	int SkyAiCharCount;
	GLuint team1BulidingImg;
	GLuint team2BulidingImg;
	GLuint BackgroundImg;
	GLuint Charater1Img;
	GLuint Charater2Img;
	GLuint SkyCharater1Img;
	GLuint SkyCharater2Img;
	GLuint BulletparticleImg;
	int teamBulingCount1;
	int teamBulingCount2;
	Sound* soundManager;
	int BackSound;
	int BulletSound;
	int BuildingSound;
	int skyCharDeathSound;
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