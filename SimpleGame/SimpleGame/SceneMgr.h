#pragma once

#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
	Renderer *g_Renderer = NULL;
public:
	Object* ert[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	void makeObject(float x, float y);
	void updateObject(float eTime);
	void draw();
	void check();
	~SceneMgr();
};

