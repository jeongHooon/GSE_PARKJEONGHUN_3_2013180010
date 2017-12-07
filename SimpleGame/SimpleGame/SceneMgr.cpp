#include "stdafx.h"
#include "SceneMgr.h"
#include <random>
default_random_engine dre;
uniform_int_distribution<int> ui(-250, 250);
uniform_int_distribution<int> ui1(0, 400);
uniform_real_distribution<float> ui2(-1, 1);
int i = 0;
int sumTime = 0;
GLuint m_texCharacterP;
GLuint m_texCharacter;
GLuint m_texCharacter2;
GLuint m_texBackground;
GLuint m_particle;
GLuint soundCS;
GLuint soundBG;
SceneMgr::SceneMgr()
{
	m_Sound = new Sound();
	g_Renderer = new Renderer(500, 800);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) { ert[i] = NULL; }

	m_texCharacter = g_Renderer->CreatePngTexture("./Textures/PNGs/minion.png");
	m_texCharacter2 = g_Renderer->CreatePngTexture("./Textures/PNGs/animal.png");
	m_texBackground = g_Renderer->CreatePngTexture("./Textures/PNGs/man.png");
	m_texCharacterP = g_Renderer->CreatePngTexture("./Textures/PNGs/player1.png");
	m_particle = g_Renderer->CreatePngTexture("./Textures/PNGs/obtacle3.png");
	soundBG = m_Sound->CreateSound("./Dependencies/SoundSamples/star4.mp3");
	soundCS = m_Sound->CreateSound("./Dependencies/SoundSamples/explosion.wav");
	m_Sound->PlaySound(soundBG, true, 0.2f);
	makeObject(100, 0, OBJECT_BACKGROUND, TEAM_NONE);
	makeObject(0, 340, OBJECT_BUILDING, TEAM_1);
	makeObject(-150, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(150, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(0, -340, OBJECT_BUILDING, TEAM_2);
	makeObject(-150, -300, OBJECT_BUILDING, TEAM_2);
	makeObject(150, -300, OBJECT_BUILDING, TEAM_2);


}

void SceneMgr::makeObject(float x, float y, int type, int teamtype)
{
	ert[i] = new Object;
	if(type == OBJECT_BACKGROUND)
		ert[i]->setAll(x, y, 0, 800, 1, 1, 0, 1, 0, 0, 0, 500, 10000000, OBJECT_BACKGROUND, teamtype);
	else if (type == OBJECT_BUILDING)
		ert[i]->setAll(x, y, 0, 100, 1, 1, 0, 1, 0, 0, 0, 500, 10000000, OBJECT_BUILDING, teamtype);
	else if (type == OBJECT_CHARACTER) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 100, 1, 0, 0, 1, a, b, 300, 100, 10000000, OBJECT_CHARACTER, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 100, 0, 0, 1, 1, a, b, 300, 100, 10000000, OBJECT_CHARACTER, teamtype);
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
			ert[i]->setAll(x, y, 0, 2, 1, 0, 0, 1, a, b, 300, 15, 10000000, OBJECT_BULLET, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 2, 0, 0, 1, 1, a, b, 300, 15, 10000000, OBJECT_BULLET, teamtype);
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
		if (ert[i] != NULL) {
			if (ert[i]->getType() == OBJECT_BACKGROUND) {
				 g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texBackground, 0.9);
			}
			else if (ert[i]->getType() == OBJECT_BUILDING) {
				if (ert[i]->getTeamtype() == TEAM_1) {
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter, 0.1);
					g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 50, ert[i]->getZ(), 50, 5, 1, 0, 0, ert[i]->getA(), ert[i]->getLife() / 500, 0.1);
					//cout << ert[i]->getLife() << endl;
				}
				else if (ert[i]->getTeamtype() == TEAM_2) {
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter2, 0.1);
					g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 50, ert[i]->getZ(), 50, 5, 0, 0, 1, ert[i]->getA(), ert[i]->getLife() / 500, 0.1);
				}
			}
			else if (ert[i]->getType() == OBJECT_CHARACTER) {
				if (ert[i]->getTeamtype() == TEAM_1) 
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacterP, ert[i]->time / 50, 0, 10, 10, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2) 
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacterP, ert[i]->time / 50, 2, 10, 10, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLife() / 100, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_BULLET) {
				g_Renderer->DrawParticle(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), -ert[i]->getDirX(), -ert[i]->getDirY(), m_particle, ert[i]->time);
			}
			else
				g_Renderer->DrawSolidRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), 0.2);
		}
	}
	char yy[] = "Game Start";
	g_Renderer->DrawText(0,0, GLUT_BITMAP_TIMES_ROMAN_24,1,0,0,yy);

}

void SceneMgr::check() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (ert[j] != NULL && ert[i] != NULL)
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
								if (ert[i]->getTeamtype() != TEAM_NONE && ert[j]->getTeamtype() != TEAM_NONE) {
									float temp = ert[i]->getLife();
									ert[i]->setLife(temp - ert[j]->getLife());
									ert[j]->setLife(ert[j]->getLife() - temp);
									cout << ert[i]->getLife() << " ! " << ert[j]->getLife() << endl;
									m_Sound->PlaySound(soundCS, false, 0.2f);
								}
							}
							if (ert[i]->getLife() <= 0) {
								delete ert[i];
								ert[i] = NULL;
								
							}
							if (ert[j]->getLife() <= 0) {
								delete ert[j];
								ert[j] = NULL;
							}
						}
					}
				}
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
