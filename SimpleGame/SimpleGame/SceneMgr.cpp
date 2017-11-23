#include "stdafx.h"
#include "SceneMgr.h"
#include <random>
default_random_engine dre;
uniform_int_distribution<int> ui(-250, 250);
uniform_int_distribution<int> ui1(0, 400);
uniform_real_distribution<float> ui2(-1, 1);
int i = 0;
int sumTime = 0;
GLuint m_texCharacter;
GLuint m_texCharacter2;
SceneMgr::SceneMgr()
{
	g_Renderer = new Renderer(500, 800);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) { ert[i] = NULL; }

	m_texCharacter = g_Renderer->CreatePngTexture("./Textures/PNGs/minion.png");
	m_texCharacter2 = g_Renderer->CreatePngTexture("./Textures/PNGs/animal.png");
	
	makeObject(0, 350, OBJECT_BUILDING, TEAM_1);
	makeObject(-150, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(150, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(0, -350, OBJECT_BUILDING, TEAM_2);
	makeObject(-150, -300, OBJECT_BUILDING, TEAM_2);
	makeObject(150, -300, OBJECT_BUILDING, TEAM_2);
	
}

void SceneMgr::makeObject(float x, float y, int type, int teamtype)
{
	ert[i] = new Object;
	if (type == OBJECT_BUILDING)
		ert[i]->setAll(x, y, 0, 100, 1, 1, 0, 1, 0, 0, 0, 500, 10000000, OBJECT_BUILDING, teamtype);
	else if (type == OBJECT_CHARACTER) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 10, 1, 0, 0, 1, a, b, 300, 10, 10000000, OBJECT_CHARACTER, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 10, 0, 0, 1, 1, a, b, 300, 10, 10000000, OBJECT_CHARACTER, teamtype);
	}
	else if (type == OBJECT_ARROW) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 2, 0.5, 0.2, 0.7, 1, a, b, 100, 10, 10000000, OBJECT_ARROW, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 2, 1, 1, 0, 1, a, b, 100, 10, 10000000, OBJECT_ARROW, teamtype);
	}
	else if (type == OBJECT_BULLET) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 2, 1, 0, 0, 1, a, b, 600, 20, 10000000, OBJECT_BULLET, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 2, 0, 0, 1, 1, a, b, 600, 20, 10000000, OBJECT_BULLET, teamtype);
	}
	else
		;
	++i;
}

void SceneMgr::updateObject(float eTime) {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL) {
			ert[i]->Update(eTime);
			if (ert[i]->time >= 3000 && ert[i]->getType() == OBJECT_CHARACTER) {
				makeObject(ert[i]->getX(), ert[i]->getY(), OBJECT_ARROW, ert[i]->getTeamtype());
				ert[i]->time -= 3000;
			}
			else if (ert[i]->time >= 10000 && ert[i]->getType() == OBJECT_BUILDING) {
				makeObject(ert[i]->getX(), ert[i]->getY(), OBJECT_BULLET, ert[i]->getTeamtype());
				ert[i]->time -= 10000;
			}
		}

	sumTime += eTime;
	if (sumTime >= 5000) {
		makeObject(ui(dre), ui1(dre), OBJECT_CHARACTER, TEAM_1);
		sumTime -= 5000;
	}
}

void SceneMgr::draw() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (ert[i] != NULL)
			if (ert[i]->getType() == OBJECT_BUILDING) {
				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter2);
			}
			else
				g_Renderer->DrawSolidRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA());
	}
}

void SceneMgr::check() {
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
							if (ert[i]->getTeamtype() != ert[j]->getTeamtype()) {
								float temp = ert[i]->getLife();
								ert[i]->setLife(temp - ert[j]->getLife());
								ert[j]->setLife(ert[j]->getLife() - temp);
							}
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
