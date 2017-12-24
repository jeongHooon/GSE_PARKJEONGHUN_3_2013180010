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
#include <Windows.h>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Object.h"
#include "SceneMgr.h"
using namespace std;

SceneMgr* asd = NULL;
float posXbuf;
float posYbuf;
float timebuf=0;
DWORD startTime = timeGetTime();
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 1.0f, 1.0f, 1.0f);
	
	// Renderer Test
	DWORD endTime = timeGetTime();
	DWORD resultTime = endTime - startTime;
	startTime = endTime;
	
	timebuf += (float)resultTime;
	asd->updateObject((float)resultTime);
	asd->check();
	asd->draw();
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

bool CollisionFunc(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1) 
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		posXbuf = x;
		posYbuf = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && abs(posXbuf - x) < 5 && abs(posYbuf - y) < 5) {
		if (asd->choice == OBJECT_HELI && (MAP_HEIGHT / 2 -y) <=0 && asd->ert[0]->time/1000 >= 5) {
			asd->makeObject(x - MAP_WIDTH/2, MAP_HEIGHT/2 - y, OBJECT_HELI, TEAM_2);
			asd->ert[0]->time -= 5000;
		}
		else if (asd->choice == OBJECT_TOWER1 && (MAP_HEIGHT / 2 - y) <= 0 && asd->ert[0]->time / 1000 >= 7) {
			asd->makeObject(x - MAP_WIDTH / 2, MAP_HEIGHT / 2 - y, OBJECT_TOWER1, TEAM_2);
			asd->ert[0]->time -= 7000;
		}
		else if (asd->choice == OBJECT_TOWER2 && (MAP_HEIGHT / 2 - y) <= 0 && asd->ert[0]->time / 1000 >= 7) {
			asd->makeObject(x - MAP_WIDTH / 2, MAP_HEIGHT / 2 - y, OBJECT_TOWER2, TEAM_2);
			asd->ert[0]->time -= 7000;
		}
		if (CollisionFunc(posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, 176 - 15, -384 - 15, 176 + 15, -384 + 15)) {
			asd->choice = OBJECT_HELI;
		}
		else if (CollisionFunc(posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, 208 - 15, -384 - 15, 208 + 15, -384 + 15))
			asd->choice = OBJECT_TOWER1;
		else if (CollisionFunc(posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, posXbuf - MAP_WIDTH / 2, MAP_HEIGHT / 2 - posYbuf, 240 - 15, -384 - 15, 240 + 15, -384 + 15))
			asd->choice = OBJECT_TOWER2;
		else
			asd->choice = 0;
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
	glutInitWindowSize(MAP_WIDTH, MAP_HEIGHT);
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

    return 0;
}

