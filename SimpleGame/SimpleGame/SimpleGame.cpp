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
float timebuf=0;
chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 1.0f, 1.0f, 1.0f);
	
	// Renderer Test
	chrono::time_point<chrono::system_clock> endTime = chrono::system_clock::now();
	auto resultTime = endTime - startTime;
	startTime = endTime;
	chrono::milliseconds msec = chrono::duration_cast<chrono::milliseconds>(resultTime);
	
	cout << msec.count() << " " << timebuf << endl;
	timebuf += (float)msec.count();
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
		if (abs(posXbuf - x) < 5 && abs(posYbuf - y) < 5 && timebuf >= 7000 && (400-y) <=0 ) {
			asd->makeObject(x - 250, 400 - y,OBJECT_CHARACTER,TEAM_2);
			timebuf = 0;
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
	glutInitWindowSize(500, 800);
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

