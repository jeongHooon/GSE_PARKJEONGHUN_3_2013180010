#include "stdafx.h"
#include "SceneMgr.h"
#include <random>
default_random_engine dre;
uniform_int_distribution<int> ui(-250, 250);
uniform_int_distribution<int> ui2(-1, 1);
int i = 0;
SceneMgr::SceneMgr()
{
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		ert[i] = NULL;
		//ert[i]->setAll(ui(dre), ui(dre), ui(dre), 20, 1, 1, 1, 1, ui2(dre), ui2(dre));
	}
}

void SceneMgr::makeObject(float x, float y)
{

	ert[i] = new Object;
	ert[i]->setAll(x, y, 0, 20, 1, 1, 1, 1, ui2(dre), ui2(dre));
	++i;
}

void SceneMgr::updateObject(float eTime) {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] == NULL)
			continue;
		else
			ert[i]->Update(eTime);
}

void SceneMgr::draw() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (ert[i] == NULL)
			continue;
		else
			g_Renderer->DrawSolidRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA());
	}
}

void SceneMgr::check() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (ert[i] == NULL)
			continue;
		else
			ert[i]->setR(1); ert[i]->setG(1); ert[i]->setB(1);
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] == NULL)
			continue;
		else
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (ert[j] == NULL)
					continue;
				else {
					if (i != j) {
						if ((ert[i]->getX() - ert[i]->getSize() / 2) > (ert[j]->getX() + ert[j]->getSize() / 2))
							;
						else if ((ert[i]->getX() + ert[i]->getSize() / 2) < (ert[j]->getX() - ert[j]->getSize() / 2))
							;
						else if ((ert[i]->getY() - ert[i]->getSize() / 2) > (ert[j]->getY() + ert[j]->getSize() / 2))
							;
						else if ((ert[i]->getY() + ert[i]->getSize() / 2) < (ert[j]->getY() - ert[j]->getSize() / 2))
							;
						else {
							ert[i]->setR(1); ert[i]->setG(0); ert[i]->setB(0);
							ert[j]->setR(1); ert[j]->setG(0); ert[j]->setB(0);
						}
					}
				}
			}
		}
}


SceneMgr::~SceneMgr()
{
}
