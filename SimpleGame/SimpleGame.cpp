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

int CheckObjectCount = (MAX_OBJECTS_COUNT/2); //오브젝트 갯수 확인
float CharSpawnTime = 0;
float BuildSpawnTime = 0;
float BulleltSpawnTime = 0;
float ArrowSpawnTime = 0;
int DrawObjCheck = 0; //그려져있는지 체크

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
	SceneManager->ObjectDraw(OBJECT_CHARACTER, CharSpawnTime);

	SceneManager->ObjectDraw(OBJECT_BUILDING, BuildSpawnTime);
	
	BulleltSpawnTime += (float)updateTime;
	//cout << BulleltSpawnTime << endl;
	SceneManager->ObjectDraw(OBJECT_BULLET, BulleltSpawnTime);	//현재 3번째 인자값 CheckObjectCount는 ArrowDraw 시만 이용됨
	//cout << "x값 : "<< SceneManager->getObject(0, OBJECT_BULLET)->getPosition().x << " y값 : " << SceneManager->getObject(0, OBJECT_BULLET)->getPosition().y << " s값 : " << SceneManager->getObject(0, OBJECT_BULLET)->getPosition().s <<endl;
	
	ArrowSpawnTime += (float)updateTime;
	//cout << ArrowSpawnTime << endl;
	SceneManager->ObjectDraw(OBJECT_ARROW, ArrowSpawnTime);	//현재 3번째 인자값 CheckObjectCount는 ArrowDraw 시만 이용됨
	//cout << "x값 : "<< SceneManager->getObject(0, OBJECT_ARROW)->getPosition().x << " y값 : " << SceneManager->getObject(0, OBJECT_ARROW)->getPosition().y << " s값 : " << SceneManager->getObject(0, OBJECT_ARROW)->getPosition().s <<endl;

	//충돌 체크 및 라이프, 라이프 타임 관리 //업데이트
	//SceneManager->ObjectCollition(CheckObjectCount, (float)updateTime);
	SceneManager->ObjectCollition2((float)updateTime);
	SceneManager->ObjectCollition1((float)updateTime);
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
	x = (x - (MAX_SCREEN_WIDTH/2));
	y = ((MAX_SCEEN_HEIGHT / 2) - y);
	Data TEAM2CharColor = { 0.f,0.f, 255,255 };
	Data Red = { 255.f,0.f, 0.f,1.f }; //빨강통일 
	//DrawObjCheck = 0; //그려져있는지 체크
	//int DrawArrCheck = 0; //화살 그려져있는지 체크
	//DrawObjCheck = CheckObjectCount;
	//DrawArrCheck = CheckArrowCount;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!g_LButtonDown)
		{
			//cout << "DrawObjCheck : " << DrawObjCheck << " CheckObjectCount : " << CheckObjectCount << endl;
			if (CheckObjectCount > MAX_OBJECTS_COUNT)
			{
				return;
			}
			DrawObjCheck = 0; //그려져있는지 체크
			for (int j = (MAX_OBJECTS_COUNT/2); j < MAX_OBJECTS_COUNT; ++j)
			{
				if (SceneManager->getObject(j, OBJECT_CHARACTER)->getPosition().s < 0.0f)
				{
					//cout << "SceneManager->getObject(" << j << ", OBJECT_CHARACTER)->getPosition().s < 0.0f 실행" << endl;
					DrawObjCheck = CheckObjectCount;
					//cout << CheckObjectCount << endl;
					CheckObjectCount = j;
					//cout << "DrawObjCheck : " << DrawObjCheck << " CheckObjectCount : " << CheckObjectCount << endl;
					break;
				}
			}
			//std::cout << "클릭되었습니다." << endl;
			//cout << "x : " << x << " y : " << y << " CheckObjCount : " << CheckObjectCount << " DrawObjCheck :" << DrawObjCheck << endl;
		}
		g_LButtonDown = true;
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
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->fixedObjLife(1.0f);
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setRGB(TEAM2CharColor);
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setTeamNum(2);
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

			if (DrawObjCheck != 0) 
			{
			CheckObjectCount = DrawObjCheck;
			}
			if (CheckObjectCount < (MAX_OBJECTS_COUNT-1) && DrawObjCheck == 0)
			{
				CheckObjectCount++;
			}
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
	//SceneManager->ObjectCreate(OBJECT_CHARACTER); //캐릭터 객체생성
	//SceneManager->ObjectCreate(OBJECT_BUILDING); //건물 객체생성
	//SceneManager->ObjectCreate(OBJECT_BULLET); //총알 객체생성
	//SceneManager->ObjectCreate(OBJECT_ARROW); //캐릭총알 객체생성
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

	//for (int i = 1; i <= 4; ++i) // ARROW 추가되면 4까지
	//{
	//	SceneManager->ObjectAllDelete(i);
	//}
	//SceneManager->RendererDelete();
	
	return 0;
}