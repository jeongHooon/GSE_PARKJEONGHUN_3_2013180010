#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	x = 0;
	y = 0;
	z = 0;
	size = 20;
	r = 0;
	g = 0;
	b = 0;
	a = 1;
	dirX = 1;
	dirY = 1;
	time = 0;
}

void Object::setAll(float x1, float y1, float z1, float size1, float r1, float g1, float b1, float a1, float dirX1, float dirY1, float velocity1, float life1, float lifetime1,int type1, int teamtype1)
{
	x = x1;
	y = y1;
	z = z1;
	size = size1;
	r = r1;
	g = g1;
	b = b1;
	a = a1;
	dirX = dirX1;
	dirY = dirY1;
	velocity = velocity1;
	life = life1;
	lifetime = lifetime1;
	type = type1;
	teamtype = teamtype1;
}


void Object::Update(float eTime) {
	float eTimeInSecond = eTime / 1000.f;

	setLifeTime(getLifeTime() - eTime);
	if (getType() == OBJECT_BULLET) {
		time += eTimeInSecond * 7 / 10;
		if (time > 100)
			time = 0;
	}
	else if (getType() == OBJECT_BACKGROUND)
		if (time >= 7000)
			;
		else
			time += eTime;
	else
		time += eTime;
	if (getType() == OBJECT_CHARACTER) {
		if (getX() + (getDirX() * eTimeInSecond) >= MAP_WIDTH / 2) {
			setX(250);
			setDirX(getDirX() * -1);
		}
		else if (getX() + (getDirX() * eTimeInSecond) <= -MAP_WIDTH / 2) {
			setX(-250);
			setDirX(getDirX() * -1);
		}
		else if (getY() + (getDirY() * eTimeInSecond) >= MAP_HEIGHT / 2) {
			setY(400);
			setDirY(getDirY() * -1);
		}
		else if (getY() + (getDirY() * eTimeInSecond) <= -MAP_HEIGHT / 2) {
			setY(-400);
			setDirY(getDirY() * -1);
		}
	}

	if (getType() == OBJECT_ARROW || getType() == OBJECT_BULLET)
	{
		if (getX() > MAP_WIDTH / 2 || getX() < -MAP_WIDTH / 2 || getY() > MAP_HEIGHT / 2 || getY() < -MAP_HEIGHT / 2) {
			setLife(0);
		}
	}
	if (getType() == OBJECT_HELI && heliStop)
		;
		/*m_Sound->PlaySound(soundBB, false, 0.2f);*/
	else if (getType() == OBJECT_TOWER1 || getType() == OBJECT_TOWER2)
		;
	else {
		setX(getX() + (getDirX() * getVelocity() * eTimeInSecond));
		setY(getY() + (getDirY() * getVelocity() * eTimeInSecond));
	}

	
	lifetime -= eTimeInSecond;

	
}

Object::~Object()
{
	
}
