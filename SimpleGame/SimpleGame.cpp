/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)
This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"

#define MAX_OBJECTS_SIZE 10
#define MAX_OBJECTS_COUNT 50
Renderer *g_Renderer = NULL;
// Object* obj = new Object;

SceneMgr *SceneManager = new SceneMgr();

bool g_LButtonDown = false; //마우스 클릭 확인

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
	for (int i = 0; i < MAX_OBJECTS_COUNT - 1; ++i) //충돌체크를 위해 -1까지만 한다.
	{
		int Size = MAX_OBJECTS_SIZE / 2;
		Data Red = { 255,0, 0,1.0 }; //빨강통일 
		Data White = { 255,255, 255,1.0 };
		Data Rect1 = SceneManager->getObject(i)->getPosition();
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i == j)
			{
				continue;
			}
			Data Rect2 = SceneManager->getObject(j)->getPosition();
			if ((Rect1.x - Size) < (Rect2.x + Size) && (Rect1.x + Size) > (Rect2.x - Size) && (Rect1.y - Size) < (Rect2.y + Size) && (Rect1.y + Size) > (Rect2.y - Size))
			{
				//std::cout << i  << " : 충돌함" << std::endl;
				SceneManager->getObject(i)->setRGB(Red);
				SceneManager->getObject(j)->setRGB(Red);
			}
			//SceneManager->getObject(i)->setRGB(White);
			//SceneManager->getObject(j)->setRGB(White);
		}
		//SceneManager->getObject(i)->setRGB(White);
		//SceneManager->ObjectCollition(i, MAX_OBJECTS_COUNT, MAX_OBJECTS_SIZE);
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i)->Update();
	}


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i)->Update();
	}*/
}

void MouseInput(int button, int state, int x, int y)
{
	x = x - 250;
	y = 250 - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
		Data Red = { 255,0, 0,1.0 }; //빨강통일 
		std::cout << "클릭되었습니다." << endl;
		std::cout << "x : " << x << " y : " << y << endl;
		Data temp1 = { (float)x,(float)y,0,10 };
		Data temp2 = { 0,0,0,10 };
		SceneManager->getObject(1)->setPosition(temp1);
		SceneManager->getObject(1)->setRGB(Red);
		SceneManager->getObject(1)->setDirection(temp2);

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			//범위 체크
			std::cout << "클릭 해제되었습니다." << endl;
		}
		Data temp2 = { rand() % 2,1,0,10 };
		SceneManager->getObject(1)->setDirection(temp2);
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
	srand((unsigned)time(NULL));  //한번만 설정할 것.
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
		Data temp1 = { (float)((rand() % 500) - 200),(float)(200 - (rand() % 500)),0,MAX_OBJECTS_SIZE };
		Data temp2 = { 255,255, 255,1.0 }; //흰색통일 
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