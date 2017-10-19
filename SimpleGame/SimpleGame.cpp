/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)
This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"


#define MAX_OBJECTS_COUNT 50
Renderer *g_Renderer = NULL;
// Object* obj = new Object;

SceneMgr *SceneManager = new SceneMgr();


bool g_LButtonDown = false;

using namespace std;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		Data pos = SceneManager->getObject(i)->getPosition();
		Data rgb = SceneManager->getObject(i)->getRGB();
		g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
	}
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i)->Update();
	}*/

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i)->Update();
	}
}

void MouseInput(int button, int state, int x, int y)
{
	x = x - 250;
	y = 250 - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
		std::cout << "클릭되었습니다." << endl;
		std::cout << "x : " <<x<< " y : " <<y<< endl;
		Data temp1 = { (float)x,(float)y,0,10 };
		SceneManager->getObject(1)->setPosition(temp1);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			//범위 체크
			std::cout << "클릭 해제되었습니다." << endl;
		}
		g_LButtonDown = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	SceneManager->ObjectCreate(MAX_OBJECTS_COUNT); //객체생성
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		Data temp1 = { (int)((rand() % 250)-200),(int)(200-(rand() % 250)),0,10 };
		//Data temp2 = { (char)(rand() % 256), (char)(rand() % 256), (char)(rand() % 256),1.0 };
		Data temp2 = {255,255, 255,1.0 }; //흰색통일
		//obj->setPosition(temp1);
		default_random_engine dre;
		uniform_int_distribution<int> uid(-1, 1);
		Data temp3 = { ((rand() % 3)-1) , ((rand() % 3) - 1) ,0,0 };
		//Data temp3 = { uid(dre) ,uid(dre) ,0,0};

		SceneManager->getObject(i)->setDirection(temp3);
		SceneManager->getObject(i)->setPosition(temp1);
		SceneManager->getObject(i)->setRGB(temp2);
	}
	

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	SceneManager->ObjectDelete();
	//delete obj;
	return 0;
}