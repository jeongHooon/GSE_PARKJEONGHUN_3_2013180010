#pragma once
#include "Object.h"
#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
public:
	Object ert[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	void updateObject() {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			ert[i].Update();
	}
	/*void drawObject() {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			g_Renderer->DrawSolidRect(ert[i].getX(), ert[i].getY(), ert[i].getZ(), ert[i].getSize(), ert[i].getR(), ert[i].getG(), ert[i].getB(), ert[i].getA());
	}*/
	void check() {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (i != j) {
					ert[i].getX();
				}
			}
	}
	~SceneMgr();
};

