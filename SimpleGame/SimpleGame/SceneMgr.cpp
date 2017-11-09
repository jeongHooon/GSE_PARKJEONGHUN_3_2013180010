#include "stdafx.h"
#include "SceneMgr.h"
#include <random>
default_random_engine dre;
uniform_int_distribution<int> ui(-250, 250);
uniform_real_distribution<float> ui2(-1, 1);
int i = 0;
int sumTime = 0;
GLuint m_texCharacter;
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
	m_texCharacter = g_Renderer->CreatePngTexture("./Textures/PNGs/minion.png");
	
	makeObject(0, 0, OBJECT_BUILDING, -1);
	
}

void SceneMgr::makeObject(float x, float y, int type, int arrow)
{
	ert[i] = new Object;
	if (type == OBJECT_BUILDING)
		ert[i]->setAll(x, y, 0, 50, 1, 1, 0, 1, 0, 0, 0, 500, 10000000, OBJECT_BUILDING, arrow);
	else if (type == OBJECT_CHARACTER) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		ert[i]->setAll(x, y, 0, 10, 1, 1, 1, 1, a, b, 600, 10, 10000000, OBJECT_CHARACTER, arrow);
	}
	else if (type == OBJECT_ARROW) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		ert[i]->setAll(x, y, 0, 2, 0, 0, 1, 1, a, b, 100, 10, 10000000, OBJECT_ARROW, arrow);
	}
	else if (type == OBJECT_BULLET) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		ert[i]->setAll(x, y, 0, 2, 1, 0, 0, 1, a, b, 300, 20, 10000000, OBJECT_BULLET, arrow);
	}
	else
		;
	++i;
}

void SceneMgr::updateObject(float eTime) {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL) {
			ert[i]->Update(eTime);
			
		}
	sumTime += eTime;
	if (sumTime >= 500) {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if (ert[i] != NULL) {
				if (ert[i]->getType() == OBJECT_CHARACTER)
				{
					makeObject(ert[i]->getX(), ert[i]->getY(), OBJECT_ARROW, i);
				}
			}
		}
		makeObject(0, 0, OBJECT_BULLET, -1);
		sumTime -= 500;
	}
}

void SceneMgr::draw() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (ert[i] != NULL)
			if(ert[i]->getType() == OBJECT_BUILDING)
				g_Renderer->DrawTexturedRect(0, 0, 0, 50, 0, 0, 0, 1, m_texCharacter);
			else
				g_Renderer->DrawSolidRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA());
	}
}

void SceneMgr::check() {
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		if (ert[i] == NULL)
			continue;
		else if (ert[i]->getType() == OBJECT_BUILDING) {
			ert[i]->setR(1); ert[i]->setG(1); ert[i]->setB(0);
		}
		else if (ert[i]->getType() == OBJECT_CHARACTER) {
			ert[i]->setR(1); ert[i]->setG(1); ert[i]->setB(1);
		}
	}*/
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (ert[j] != NULL)
				{
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
							if (ert[i]->getType() == OBJECT_BUILDING && ert[j]->getType() == OBJECT_CHARACTER) {
								ert[i]->setLife(ert[i]->getLife() - ert[j]->getLife());
								delete ert[j];
								ert[j] = NULL;
							}
							else if (ert[i]->getType() == OBJECT_BUILDING && ert[j]->getType() == OBJECT_ARROW)
							{
								ert[i]->setLife(ert[i]->getLife() - ert[j]->getLife());
								delete ert[j];
								ert[j] = NULL;
							}
							else if (ert[i]->getType() == OBJECT_CHARACTER && ert[j]->getType() == OBJECT_BULLET) {
								ert[i]->setLife(ert[i]->getLife() - ert[j]->getLife());
								delete ert[j];
								ert[j] = NULL;
							}
							else if (ert[i]->getType() == OBJECT_CHARACTER && ert[j]->getType() == OBJECT_ARROW) {
								if (i != ert[j]->getArrow()) {
									ert[i]->setLife(ert[i]->getLife() - ert[j]->getLife());
									delete ert[j];
									ert[j] = NULL;
								}
							}
							else if (ert[i]->getType() == OBJECT_CHARACTER && ert[j]->getType() == OBJECT_CHARACTER)
								;
						}
					}
				}
			}
		}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL)
		{
			if (ert[i]->getLife() <= 0) {
				delete ert[i];
				ert[i] = NULL;
			}
		}
}

void SceneMgr::normalize(float* a, float* b)
{
	float i = sqrt((*a)*(*a) + (*b)*(*b));
	(*a) /= i;
	(*b) /= i;
}


SceneMgr::~SceneMgr()
{
}
