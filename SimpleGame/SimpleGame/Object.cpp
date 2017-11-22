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
	time += eTime;
	if (getX() + (getDirX() * eTimeInSecond) >= 250) {
		setX(250);
		setDirX(getDirX() * -1);
	}
	else if (getX() + (getDirX() * eTimeInSecond) <= -250) {
		setX(-250);
		setDirX(getDirX() * -1);
	}
	else if (getY() + (getDirY() * eTimeInSecond) >= 400) {
		setY(400);
		setDirY(getDirY() * -1);
	}
	else if (getY() + (getDirY() * eTimeInSecond) <= -400) {
		setY(-400);
		setDirY(getDirY() * -1);
	}
		setX(getX() + (getDirX() * getVelocity() * eTimeInSecond));

		setY(getY() + (getDirY() * getVelocity() * eTimeInSecond));

	
	lifetime -= eTimeInSecond;

	
}

Object::~Object()
{
	
}
