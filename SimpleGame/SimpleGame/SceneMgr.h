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
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			ert[i].setR(1); ert[i].setG(1); ert[i].setB(1);
		}
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (i != j) {
					if ((ert[i].getX() - ert[i].getSize() / 2) > (ert[j].getX() + ert[j].getSize() / 2))
						;
					else if ((ert[i].getX() + ert[i].getSize() / 2) < (ert[j].getX() - ert[j].getSize() / 2))
						;
					else if ((ert[i].getY() - ert[i].getSize() / 2) > (ert[j].getY() + ert[j].getSize() / 2))
						;
					else if ((ert[i].getY() + ert[i].getSize() / 2) < (ert[j].getY() - ert[j].getSize() / 2))
						;
					else {
						ert[i].setR(1); ert[i].setG(0); ert[i].setB(0);
						ert[j].setR(1); ert[j].setG(0); ert[j].setB(0);
					}
				}
			}
	}
	~SceneMgr();
};

