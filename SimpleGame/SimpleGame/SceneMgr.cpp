#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr()
{
	default_random_engine dre;
	uniform_int_distribution<int> ui(-250, 250);
	uniform_int_distribution<int> ui2(-1,1);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		ert[i].setAll(ui(dre), ui(dre), ui(dre),20,1,1,1,1,ui2(dre),ui2(dre));

}


SceneMgr::~SceneMgr()
{
}
