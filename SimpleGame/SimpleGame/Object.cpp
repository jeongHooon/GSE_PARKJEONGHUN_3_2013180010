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
	velocityX = 1;
	velocityY = 1;
}

void Object::setAll(float x1, float y1, float z1, float size1, float r1, float g1, float b1, float a1, float velocityX1, float velocityY1)
{
	x = x1;
	y = y1;
	z = z1;
	size = size1;
	r = r1;
	g = g1;
	b = b1;
	a = a1;
	velocityX = velocityX1;
	velocityY = velocityY1;

}


Object::~Object()
{
}
