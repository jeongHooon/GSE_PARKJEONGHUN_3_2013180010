#pragma once

#include "Object.h"
#include "Renderer.h"


class SceneMgr
{
	Renderer *g_Renderer = NULL;
public:
	Object* ert[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	void makeObject(float x, float y, int type, int teamtype);
	void updateObject(float eTime);
	void draw();
	void check();
	void normalize(float* a, float* b);
	~SceneMgr();
};

