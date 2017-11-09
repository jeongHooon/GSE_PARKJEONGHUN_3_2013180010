#pragma once

#include "Object.h"
#include "Renderer.h"
#define OBJECT_BUILDING 01
#define OBJECT_CHARACTER 02
#define OBJECT_BULLET 03
#define OBJECT_ARROW 04
#define MAX_OBJECTS_COUNT 1000

class SceneMgr
{
	Renderer *g_Renderer = NULL;
public:
	Object* ert[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	void makeObject(float x, float y, int type, int arrow);
	void updateObject(float eTime);
	void draw();
	void check();
	void normalize(float* a, float* b);
	~SceneMgr();
};

