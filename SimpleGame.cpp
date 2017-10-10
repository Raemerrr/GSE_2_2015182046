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
#define objectCount 10


Renderer *g_Renderer = NULL;
Object* obj = new Object[objectCount];
using namespace std; 

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	for (int i = 0; i < 50; ++i) {
		Data pos = obj[i].getPosition();
		Data rgb = obj[i].getRGB();
		// Renderer Test
		g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
	}

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
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

	default_random_engine dre;
	uniform_int_distribution<int> ui1(-300, 300);
	uniform_int_distribution<int> ui2(-300, 300);
	uniform_int_distribution<int> ui3(-300, 300);

	for (int i = 0; i < objectCount; ++i) {
		Data temp1 = { ui1(dre),ui2(dre) ,ui3(dre) ,rand() % 30 };
		Data temp2 = { (char)rand() % 256, (char)rand() % 256, (char)rand() % 256,1.0 };
		obj[i].setPosition(temp1);
		obj[i].setRGB(temp2);
	}


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

