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