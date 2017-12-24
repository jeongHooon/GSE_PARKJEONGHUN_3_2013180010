#pragma once

#include "Object.h"
#include "Renderer.h"
#include "Sound.h"


class SceneMgr
{
	Renderer *g_Renderer = NULL;
	Sound *m_Sound = NULL;
public:
	Object* ert[MAX_OBJECTS_COUNT];
	int choice;
public:
	SceneMgr();
	void makeObject(float x, float y, int type, int teamtype);
	void makeB(float x, float y, float dirX, float dirY, int type, int teamtype);
	void updateObject(float eTime);
	void draw();
	void check();
	void normalize(float* a, float* b);
	bool CollisionFunc(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	bool CollisionCircle(float X1, float Y1, float X2, float Y2, int Rad1, int Rad2);
	~SceneMgr();
};

