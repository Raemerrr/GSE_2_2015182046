#pragma once
#include "stdafx.h"
#include "Object.h"

class SceneMgr
{
private:
	float vX;
	float vY;
	Object* obj;

public:
	SceneMgr();
	~SceneMgr();
	Object* getObject(int i);
	void setObject(Object p);
	void ObjectCreate(const int p);
	void ObjectDelete();
	void ObjectCollition(int i, int MAX, int Size);
};