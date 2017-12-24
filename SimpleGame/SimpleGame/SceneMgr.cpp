#include "stdafx.h"
#include "SceneMgr.h"
#include <random>
default_random_engine dre;
uniform_int_distribution<int> ui(-MAP_WIDTH / 2, MAP_WIDTH / 2);
uniform_int_distribution<int> ui1(0, MAP_HEIGHT / 2);
uniform_real_distribution<float> ui2(-1, 1);
uniform_int_distribution<int> ui3(0, 1);
uniform_int_distribution<int> ui4(-32, 32);
int i = 0;
int sumTime = 0;
int heliSpawn = 0;
int charSpawn = 0;
int tankSpawn = 0;
GLuint m_texCharacterP;
GLuint m_texCharacter;
GLuint m_texCharacter2;
GLuint m_texCharacter3;
GLuint m_texCharacter4;
GLuint m_texTank1;
GLuint m_texTank2;
GLuint m_texTower1;
GLuint m_texTower2;
GLuint m_texHeli;
GLuint m_texBackground;
GLuint m_particle;
GLuint m_particle1;
GLuint m_particle2;
GLuint soundCS;
GLuint soundBG;
GLuint soundBB;
GLuint soundEND;
bool GameStatus = true;
bool EndSound = false;
bool BGON = false;
SceneMgr::SceneMgr()
{
	m_Sound = new Sound();
	g_Renderer = new Renderer(MAP_WIDTH, MAP_HEIGHT);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) { ert[i] = NULL; }

	m_texCharacter = g_Renderer->CreatePngTexture("./Textures/PNGs/minion.png");
	m_texCharacter2 = g_Renderer->CreatePngTexture("./Textures/PNGs/animal.png");
	m_texCharacter3 = g_Renderer->CreatePngTexture("./Textures/PNGs/minionking.png");
	m_texCharacter4 = g_Renderer->CreatePngTexture("./Textures/PNGs/animalking.png");
	m_texTank1 = g_Renderer->CreatePngTexture("./Textures/PNGs/tanks1.png");
	m_texTank2 = g_Renderer->CreatePngTexture("./Textures/PNGs/tanks2.png");
	m_texTower1 = g_Renderer->CreatePngTexture("./Textures/PNGs/tower1.png");
	m_texTower2 = g_Renderer->CreatePngTexture("./Textures/PNGs/tower2.png");
	m_texHeli = g_Renderer->CreatePngTexture("./Textures/PNGs/heli.png");
	m_texBackground = g_Renderer->CreatePngTexture("./Textures/PNGs/untitled.png");
	m_texCharacterP = g_Renderer->CreatePngTexture("./Textures/PNGs/player1.png");
	m_particle = g_Renderer->CreatePngTexture("./Textures/PNGs/obtacle3.png");
	m_particle1 = g_Renderer->CreatePngTexture("./Textures/PNGs/plasmaball.png");

	m_particle2 = g_Renderer->CreatePngTexture("./Textures/PNGs/snow1.png");
	soundBG = m_Sound->CreateSound("./Dependencies/SoundSamples/star4.mp3");
	soundCS = m_Sound->CreateSound("./Dependencies/SoundSamples/explosion.wav");
	soundBB = m_Sound->CreateSound("./Dependencies/SoundSamples/bb.wav");
	soundEND = m_Sound->CreateSound("./Dependencies/SoundSamples/end.wav");
	m_Sound->PlaySound(soundBG, true, 0.2f);
	makeObject(0, 0, OBJECT_BACKGROUND, TEAM_NONE);
	makeObject(-130, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(0, 340, OBJECT_BUILDING, TEAM_1);
	makeObject(130, 300, OBJECT_BUILDING, TEAM_1);
	makeObject(-130, -300, OBJECT_BUILDING, TEAM_2);
	makeObject(0, -340, OBJECT_BUILDING, TEAM_2);
	makeObject(130, -300, OBJECT_BUILDING, TEAM_2);


}

void SceneMgr::makeObject(float x, float y, int type, int teamtype)
{
	ert[i] = new Object;
	if(type == OBJECT_BACKGROUND)
		ert[i]->setAll(x, y, 0, 800, 1, 1, 1, 1, 0, 0, 0, 500, 10000000, OBJECT_BACKGROUND, teamtype);
	else if (type == OBJECT_BUILDING)
		ert[i]->setAll(x, y, 0, 100, 1, 1, 1, 1, 0, 0, 0, 500, 10000000, OBJECT_BUILDING, teamtype);
	else if (type == OBJECT_CHARACTER) {
		float a = ui2(dre);
		float b = ui2(dre);
		normalize(&a, &b);
		if (teamtype == TEAM_1) {
			if (b > 0)
				b *= -1;
			ert[i]->setAll(x, y, 0, 50, 1, 0, 0, 1, a, b, 300, 100, 10000000, OBJECT_CHARACTER, teamtype);
		}
		else if (teamtype == TEAM_2) {
			if (b < 0)
				b *= -1;
			ert[i]->setAll(x, y, 0, 50, 0, 0, 1, 1, a, b, 300, 100, 10000000, OBJECT_CHARACTER, teamtype);
		}
	}
	else if (type == OBJECT_TANK) {
		
		if (teamtype == TEAM_1)
			ert[i]->setAll(128 + (ui3(dre) * -256) + ui4(dre), 250, 0, 32, 1, 0, 0, 1, 0, -1, 100, 100, 10000000, OBJECT_TANK, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(128 + (ui3(dre) * -256) + ui4(dre), -250, 0, 32, 0, 0, 1, 1, 0, 1, 100, 100, 10000000, OBJECT_TANK, teamtype);
	}
	else if (type == OBJECT_HELI) {

		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 50, 1, 0, 0, 1, 0, -1, 100, 100, 10000000, OBJECT_HELI, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 50, 0, 0, 1, 1, 0, 1, 100, 100, 10000000, OBJECT_HELI, teamtype);
	}
	else if (type == OBJECT_TOWER1) {

		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 100, 1, 0, 0, 1, 0, 0, 100, 100, 10000, OBJECT_TOWER1, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 100, 0, 0, 1, 1, 0, 0, 100, 100, 10000, OBJECT_TOWER1, teamtype);
	}
	else if (type == OBJECT_TOWER2) {

		if (teamtype == TEAM_1)
			ert[i]->setAll(x, y, 0, 100, 1, 0, 0, 1, 0, 0, 100, 100, 3000, OBJECT_TOWER2, teamtype);
		else if (teamtype == TEAM_2)
			ert[i]->setAll(x, y, 0, 100, 0, 0, 1, 1, 0, 0, 100, 100, 3000, OBJECT_TOWER2, teamtype);
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
		if (teamtype == TEAM_1) {
			if (b > 0)
				b *= -1;
			ert[i]->setAll(x, y, 0, 10, 1, 0, 0, 1, a, b, 300, 50, 1000000, OBJECT_BULLET, teamtype);
		}
		else if (teamtype == TEAM_2) {
			if (b < 0)
				b *= -1;
			ert[i]->setAll(x, y, 0, 10, 0, 0, 1, 1, a, b, 300, 50, 1000000, OBJECT_BULLET, teamtype);
		}
	}
	else
		if (!EndSound) {
			m_Sound->PlaySound(soundEND, false, 0.2f);
			EndSound = true;
		}
	++i;
}

void SceneMgr::makeB(float x, float y, float dirX, float dirY, int type, int teamtype)
{
	ert[i] = new Object;
	if (type == OBJECT_TOWER1B) {
		if (teamtype == TEAM_1) {

			ert[i]->setAll(x, y, 0, 20, 1, 0, 0, 1, dirX, dirY, 500, 30, 1000000, OBJECT_TOWER1B, teamtype);
		}
		else if (teamtype == TEAM_2) {
			ert[i]->setAll(x, y, 0, 20, 0, 0, 1, 1, dirX, dirY, 500, 30, 1000000, OBJECT_TOWER1B, teamtype);
		}
	}
	else if (type == OBJECT_TOWER2B) {
		if (teamtype == TEAM_1) {

			ert[i]->setAll(x, y, 0, 5, 1, 0, 0, 1, dirX, dirY, 700, 5, 1000000, OBJECT_TOWER2B, teamtype);
		}
		else if (teamtype == TEAM_2) {
			ert[i]->setAll(x, y, 0, 5, 0, 0, 1, 1, dirX, dirY, 700, 5, 1000000, OBJECT_TOWER2B, teamtype);
		}
	}
	++i;
}

void SceneMgr::updateObject(float eTime) {
	if (GameStatus) {
		BGON = false;
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			if (ert[i] != NULL) {
				ert[i]->Update(eTime);
				
				if (ert[i]->time >= 3000 && ert[i]->getType() == OBJECT_CHARACTER) {
					makeObject(ert[i]->getX(), ert[i]->getY(), OBJECT_ARROW, ert[i]->getTeamtype());
					ert[i]->time -= 3000;
				}
				else if (ert[i]->time >= 5000 && ert[i]->getType() == OBJECT_BUILDING) {
					makeObject(ert[i]->getX(), ert[i]->getY(), OBJECT_BULLET, ert[i]->getTeamtype());
					ert[i]->time -= 5000;
				}
				else if (ert[i]->time >= 50 && ert[i]->getType() == OBJECT_TOWER2) {
					float a = ui2(dre);
					float b = ui2(dre);
					normalize(&a, &b);
					makeB(ert[i]->getX(), ert[i]->getY(), a, b, OBJECT_TOWER1B, ert[i]->getTeamtype());
					ert[i]->time -= 50;
				}
				if (ert[i]->getType() == OBJECT_TANK || ert[i]->getType() == OBJECT_HELI) {
					
					float a = 0;
					float b = 0;
					if (ert[i]->getX() >= 0 && ert[i]->getTeamtype() == TEAM_1) {
						if (ert[6] == NULL && ert[i]->getY() < -250) {
							a = ert[5]->getX() - ert[i]->getX();
							b = ert[5]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
						else if (ert[6] != NULL) {
							a = ert[6]->getX() - ert[i]->getX();
							b = ert[6]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
						
					}
					else if (ert[i]->getX() >= 0 && ert[i]->getTeamtype() == TEAM_2)
					{
						if (ert[3] == NULL && ert[i]->getY() > 250) {
							a = ert[2]->getX() - ert[i]->getX();
							b = ert[2]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
						else if (ert[3] != NULL) {
							a = ert[3]->getX() - ert[i]->getX();
							b = ert[3]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
					}
					else if (ert[i]->getX() <= -0 && ert[i]->getTeamtype() == TEAM_1)
					{
						if (ert[4] == NULL && ert[i]->getY() < -250) {
							a = ert[5]->getX() - ert[i]->getX();
							b = ert[5]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
						else if (ert[4] != NULL) {
							a = ert[4]->getX() - ert[i]->getX();
							b = ert[4]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
					}
					else if (ert[i]->getX() <= -0 && ert[i]->getTeamtype() == TEAM_2)
					{
						if (ert[1] == NULL && ert[i]->getY() > 250) {
							a = ert[2]->getX() - ert[i]->getX();
							b = ert[2]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
						else if (ert[1] != NULL) {
							a = ert[1]->getX() - ert[i]->getX();
							b = ert[1]->getY() - ert[i]->getY();
							normalize(&a, &b);
							ert[i]->setDirX(a);
							ert[i]->setDirY(b);
						}
					}
				}
			}
		sumTime += eTime;
		heliSpawn += eTime;
		tankSpawn += eTime;
		charSpawn += eTime;
		if (heliSpawn >= 7000) {
			makeObject(ui(dre), ui1(dre), OBJECT_HELI, TEAM_1);
			heliSpawn -= 7000;
		}
		if (tankSpawn >= 1000) {
			makeObject(0, 0, OBJECT_TANK, TEAM_1);
			makeObject(0, 0, OBJECT_TANK, TEAM_2);
			tankSpawn -= 1000;
		}
		if (charSpawn >= 7000) {
			makeObject(ui(dre), ui1(dre), OBJECT_CHARACTER, TEAM_1);
			charSpawn -= 7000;
		}
		
	}
	else
		;
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
					if(i == 2)
						g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter3, 0.1);
					else
						g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter, 0.1);
					g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 50, ert[i]->getZ(), 50, 5, 1, 0, 0, ert[i]->getA(), ert[i]->getLife() / 500, 0.1);
					//cout << ert[i]->getLife() << endl;
				}
				else if (ert[i]->getTeamtype() == TEAM_2) {
					if (i == 5)
						g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter4, 0.1);
					else
						g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacter2, 0.1);
					g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 50, ert[i]->getZ(), 50, 5, 0, 0, 1, ert[i]->getA(), ert[i]->getLife() / 500, 0.1);
				}
			}
			else if (ert[i]->getType() == OBJECT_CHARACTER) {
				if (ert[i]->getTeamtype() == TEAM_1) 
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacterP, ert[i]->time / 50, 2, 10, 10, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2) 
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_texCharacterP, ert[i]->time / 50, 2, 10, 10, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLife() / 100, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_TANK) {

				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTank1, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTank2, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLife() / 100, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_HELI) {

				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texHeli, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texHeli, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLife() / 100, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_TOWER1) {
				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTower1, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTower1, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLifeTime() / 10000, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_TOWER2) {
				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTower2, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), 1, 1, 1, ert[i]->getA(), m_texTower2, 0.2);
				g_Renderer->DrawSolidRectGauge(ert[i]->getX(), ert[i]->getY() + 30, ert[i]->getZ(), 40, 5, ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), ert[i]->getLifeTime() / 3000, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_TOWER1B) {
				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_particle1, ert[i]->time / 4, 0, 4, 4, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_particle1, ert[i]->time / 4, 2, 4, 4, 0.2);
				
			}
			else if (ert[i]->getType() == OBJECT_TOWER2B) {
				if (ert[i]->getTeamtype() == TEAM_1)
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_particle1, ert[i]->time / 4, 0, 4, 4, 0.2);
				else if (ert[i]->getTeamtype() == TEAM_2)
					g_Renderer->DrawTexturedRectSeq(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), m_particle1, ert[i]->time / 4, 2, 4, 4, 0.2);
			}
			else if (ert[i]->getType() == OBJECT_BULLET)
				g_Renderer->DrawParticle(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), -ert[i]->getDirX(), -ert[i]->getDirY(), m_particle, ert[i]->time,0.1);
			else
				g_Renderer->DrawSolidRect(ert[i]->getX(), ert[i]->getY(), ert[i]->getZ(), ert[i]->getSize(), ert[i]->getR(), ert[i]->getG(), ert[i]->getB(), ert[i]->getA(), 0.2);
		}
	}
	g_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, m_particle2, sumTime/100, 0.01);
	/// ui
	if (!GameStatus) {
		g_Renderer->DrawSolidRectXY(0, 0, 0, 100, 50, 1, 1, 1, 1, 0.1);
		g_Renderer->DrawText(-25, 0, GLUT_BITMAP_TIMES_ROMAN_24, 1, 0, 0, "GAME END");
	}
	for (int i = 1; i <= ert[0]->time / 1000; ++i)
	g_Renderer->DrawTexturedRect(-80 + i*32 , -384, 0, 32, 1, 1, 1, 1, m_particle, 0.2);
	switch (choice) {
	case OBJECT_HELI: {
		g_Renderer->DrawSolidRectXY(176, -384, 0, 32, 32, 1, 0, 0, 1, 0.1);
		break;
	}
	case OBJECT_TOWER1: {
		g_Renderer->DrawSolidRectXY(208, -384, 0, 32, 32, 1, 0, 0, 1, 0.1);
		break;
	}
	case OBJECT_TOWER2: {
		g_Renderer->DrawSolidRectXY(240, -384, 0, 32, 32, 1, 0, 0, 1, 0.1);
		break;
	}
	}
	g_Renderer->DrawSolidRectXY(176, -384, 0, 30, 30, 1, 1, 1, 1, 0.1);
	g_Renderer->DrawSolidRectXY(208, -384, 0, 30, 30, 1, 1, 1, 1, 0.1);
	g_Renderer->DrawSolidRectXY(240, -384, 0, 30, 30, 1, 1, 1, 1, 0.1);

	if (ert[0]->time / 1000 >= 5)
		g_Renderer->DrawTexturedRect(176, -384, 0, 30, 1, 1, 1, 1, m_texHeli, 0.1);
	else
		g_Renderer->DrawTexturedRect(176, -384, 0, 30, 0, 0, 0, 1, m_texHeli, 0.1);
	if (ert[0]->time / 1000 >= 7) {
		g_Renderer->DrawTexturedRect(208, -384, 0, 30, 1, 1, 1, 1, m_texTower1, 0.1);
		g_Renderer->DrawTexturedRect(240, -384, 0, 30, 1, 1, 1, 1, m_texTower2, 0.1);
	}
	else {
		g_Renderer->DrawTexturedRect(208, -384, 0, 30, 0, 0, 0, 1, m_texTower1, 0.1);
		g_Renderer->DrawTexturedRect(240, -384, 0, 30, 0, 0, 0, 1, m_texTower2, 0.1);
	}

}

void SceneMgr::check() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL)
		{
			ert[i]->heliStop = false;
		}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (ert[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j) {
				if (ert[j] != NULL && ert[i] != NULL && i != j)
				{

					if (ert[i]->getType() == OBJECT_HELI)
						if (CollisionCircle(ert[i]->getX(), ert[i]->getY(), ert[j]->getX(), ert[j]->getY(), 100, ert[j]->getSize() / 2))
							if (ert[i]->getTeamtype() != ert[j]->getTeamtype())
								if (ert[i]->getTeamtype() != TEAM_NONE && ert[j]->getTeamtype() != TEAM_NONE && ert[j]->getType() != OBJECT_TOWER1 && ert[j]->getType() != OBJECT_TOWER2) {
									ert[i]->heliStop = true;
									ert[j]->setLife(ert[j]->getLife() - 0.1);
								}
					if (ert[i]->getType() == OBJECT_TOWER1 && ert[j]->getType() != OBJECT_BUILDING)
						if (CollisionCircle(ert[i]->getX(), ert[i]->getY(), ert[j]->getX(), ert[j]->getY(), 200, ert[j]->getSize() / 2))
							if (ert[i]->getTeamtype() != ert[j]->getTeamtype())
								if (ert[i]->getTeamtype() != TEAM_NONE && ert[j]->getTeamtype() != TEAM_NONE) {
									if (ert[i]->time >= 500)
									{
										float a = ert[j]->getX() - ert[i]->getX();
										float b = ert[j]->getY() - ert[i]->getY();
										normalize(&a, &b);
										makeB(ert[i]->getX(), ert[i]->getY(), a, b, OBJECT_TOWER1B, ert[i]->getTeamtype());
										ert[i]->time -= 500;
									}
								}

					///충돌 함수 호출
					if (CollisionFunc((ert[i]->getX() - ert[i]->getSize() / 2), (ert[i]->getY() - ert[i]->getSize() / 2), (ert[i]->getX() + ert[i]->getSize() / 2), (ert[i]->getY() + ert[i]->getSize() / 2)
						, (ert[j]->getX() - ert[j]->getSize() / 2), (ert[j]->getY() - ert[j]->getSize() / 2), (ert[j]->getX() + ert[j]->getSize() / 2), (ert[j]->getY() + ert[j]->getSize() / 2)))
					{
						if (ert[i]->getTeamtype() != ert[j]->getTeamtype()) {
							if (ert[i]->getTeamtype() != TEAM_NONE && ert[j]->getTeamtype() != TEAM_NONE) {
								if ((ert[i]->getType() == OBJECT_TANK && ert[j]->getType() == OBJECT_HELI))
									;
								else if ((ert[j]->getType() == OBJECT_TANK && ert[i]->getType() == OBJECT_HELI))
									;
								else if (ert[i]->getType() == OBJECT_TOWER1 || ert[i]->getType() == OBJECT_TOWER2 || ert[j]->getType() == OBJECT_TOWER1 || ert[j]->getType() == OBJECT_TOWER2)
									;
								else
								{
									float temp = ert[i]->getLife();
									ert[i]->setLife(temp - ert[j]->getLife());
									ert[j]->setLife(ert[j]->getLife() - temp);
									cout << ert[i]->getLife() << " ! " << ert[j]->getLife() << endl;
									m_Sound->PlaySound(soundCS, false, 0.2f);
								}
							}
						}
						if (ert[i]->getLife() <= 0 || ert[i]->getLifeTime() <= 0) {
							delete ert[i];
							ert[i] = NULL;

						}
						if (ert[j]->getLife() <= 0 || ert[j]->getLifeTime() <= 0) {
							delete ert[j];
							ert[j] = NULL;
						}
					}

				}
			}
		}
	if (ert[2] == NULL || ert[5] == NULL) {
		GameStatus = false;
	}
}

void SceneMgr::normalize(float* a, float* b)
{
	float i = sqrt((*a)*(*a) + (*b)*(*b));
	(*a) /= i;
	(*b) /= i;
}

bool SceneMgr::CollisionFunc(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}

bool SceneMgr::CollisionCircle(float X1, float Y1, float X2, float Y2, int Rad1, int Rad2)
{
	float X3 = X1 - X2;
	float Y3 = Y1 - Y2;
	float dis = sqrt(X3*X3 + Y3*Y3);
	if (dis <= Rad1 + Rad2)
		return true;
	return false;
}


SceneMgr::~SceneMgr()
{
}
