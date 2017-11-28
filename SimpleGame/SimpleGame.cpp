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
#include "SceneMgr.h"

SceneMgr *SceneManager = new SceneMgr();

bool g_LButtonDown = false; //마우스 클릭 확인
DWORD g_prevTime = 0;	//이전 시간 확인 변수

int CheckObjectCount = (MAX_OBJECTS_COUNT / 2); //오브젝트 갯수 확인
int DrawObjCheck = 0; //그려져있는지 체크

//오브젝트 리스폰 관리
float CharSpawnTime = 0;
float AICharSpawnTime = 0;
float BuildSpawnTime = 0;	//유일하게 아직 사용하지 않는 함수
float BulleltSpawnTime = 0;
float ArrowSpawnTime = 0;

using namespace std;

void RenderScene(void)
{

	DWORD currentTime = timeGetTime();
	DWORD updateTime = currentTime - g_prevTime;
	g_prevTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.f);

	// Renderer Test
	//그리기함수
	CharSpawnTime += (float)updateTime;
	AICharSpawnTime += (float)updateTime;
	SceneManager->ObjectDraw(OBJECT_CHARACTER, AICharSpawnTime);

	SceneManager->ObjectDraw(OBJECT_BUILDING, BuildSpawnTime);

	BulleltSpawnTime += (float)updateTime;
	SceneManager->ObjectDraw(OBJECT_BULLET, BulleltSpawnTime);

	ArrowSpawnTime += (float)updateTime;
	SceneManager->ObjectDraw(OBJECT_ARROW, ArrowSpawnTime);

	//충돌 체크 및 라이프, 라이프 타임 관리 //업데이트
	SceneManager->Update((float)updateTime);
	SceneManager->ObjectCollition2();
	SceneManager->ObjectCollition1();	//1에서 life < 0.f체크를 하기 떄문에 2보다 나중에 실행
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i, OBJECT_CHARACTER)->Update((float)updateTime);
	}*/
}

void MouseInput(int button, int state, int x, int y)
{
	x = (x - (MAX_SCREEN_WIDTH / 2));
	y = ((MAX_SCEEN_HEIGHT / 2) - y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!g_LButtonDown && CharSpawnTime > 3000)
		{
			//cout << "DrawObjCheck : " << DrawObjCheck << " CheckObjectCount : " << CheckObjectCount << endl;
			if (CheckObjectCount > MAX_OBJECTS_COUNT)
			{
				return;
			}
			DrawObjCheck = 0; //그려져있는지 체크
			for (int j = (MAX_OBJECTS_COUNT / 2); j < MAX_OBJECTS_COUNT; ++j)
			{
				//cout << "CharSpawnTime : " << CharSpawnTime << " CheckObjectCount : " << CheckObjectCount << " DrawObjCheck : " << DrawObjCheck << endl;
				if (SceneManager->getObject(j, OBJECT_CHARACTER)->getObjLife() < 0.0f)
				{
					//cout << "SceneManager->getObject(" << j << ", OBJECT_CHARACTER)->getPosition().s < 0.0f 실행" << endl;
					DrawObjCheck = CheckObjectCount;
					//cout << CheckObjectCount << endl;
					CheckObjectCount = j;
					break;
				}
			}
			//std::cout << "클릭되었습니다." << endl;
			//cout << "x : " << x << " y : " << y << " CheckObjCount : " << CheckObjectCount << " DrawObjCheck :" << DrawObjCheck << endl;
			g_LButtonDown = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			//범위 체크
			//cout << "클릭 해제되었습니다." << endl;
			Data temp1 = { (float)x,(float)y,0,MAX_OBJECTS_SIZE };
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setPosition(temp1);
			/*SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setObjLifeTime(100000.0f);*/
			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data temp2 = { checkX,checkY,0.0f,0.0f };
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setDirection(temp2);
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setObjLife(100.f);

			if (DrawObjCheck != 0)
			{
				CheckObjectCount = DrawObjCheck;
			}
			if (CheckObjectCount < (MAX_OBJECTS_COUNT - 1) && DrawObjCheck == 0)
			{
				CheckObjectCount++;
			}
			CharSpawnTime = 0;
			g_LButtonDown = false;
		}
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
	glutInitWindowSize(MAX_SCREEN_WIDTH, MAX_SCEEN_HEIGHT);			//화면 크기 처리
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

	SceneManager->RendererCreate();

	for (int i = 1; i <= 4; ++i) // ARROW 추가되면 4까지
	{
		SceneManager->ObjectCreate(i);
	}
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_prevTime = timeGetTime();

	glutMainLoop();

	return 0;
}