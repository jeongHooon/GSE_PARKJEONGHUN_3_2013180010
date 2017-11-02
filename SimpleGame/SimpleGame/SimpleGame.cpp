/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)
This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <random>
#include <math.h>
#include <chrono>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Object.h"
#include "SceneMgr.h"
using namespace std;

SceneMgr* asd = NULL;
float posXbuf;
float posYbuf;
auto startTime = chrono::system_clock::now();
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	
	// Renderer Test
	auto endTime = chrono::system_clock::now();
	auto resultTime = endTime - startTime;
	startTime = endTime;
	auto msec = chrono::duration_cast<chrono::milliseconds>(resultTime);
	cout << "경과시간 - " << msec.count() << "mSec" << endl;
	asd->updateObject((float)msec.count());
	asd->check();
	asd->draw();
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		posXbuf = x;
		posYbuf = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (abs(posXbuf - x) < 5 && abs(posYbuf - y) < 5) {
			asd->makeObject(x - 250, 250 - y,OBJECT_CHARACTER);
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
	asd = new SceneMgr;
	/*g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}*/

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//delete g_Renderer;

    return 0;
}

